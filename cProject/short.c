#include <stdio.h>      // 标准输入输出库（printf/scanf/fopen等）
#include <stdlib.h>     // 标准库（rand/srand/exit等）
#include <string.h>     // 字符串处理库（strcpy/strcmp/strncpy等）
#include <time.h>       // 时间处理库（time/localtime/strftime等）
#include <stdbool.h>    // 布尔类型库（true/false）

// ====================== 配置常量（可按需调整） ======================
#define MAX_URL_COUNT 1000    // 系统最大可存储的短网址数量
#define MAX_URL_LEN 2048      // 原始长URL的最大长度限制
#define MAX_SHORT_CODE_LEN 7  // 短码长度（6位字符 + 1位字符串结束符'\0'）
#define DATA_FILE "url_data.txt" // 短网址数据持久化存储的文件路径
const char CHARSET[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 短码生成的字符集（数字+大小写字母）
const int CHARSET_LEN = 62;   // 字符集总长度（10数字+26小写+26大写）

// ====================== 结构体/枚举定义（数据模型） ======================
// 有效期类型枚举：定义短网址的有效期规则
typedef enum {
    EXPIRE_1DAY,      // 有效期1天
    EXPIRE_CUSTOM,    // 自定义有效期天数
    EXPIRE_PERMANENT  // 永久有效
} ExpireType;

// 短网址核心结构体：存储单个短网址的所有信息
typedef struct {
    char original_url[MAX_URL_LEN]; // 原始长URL
    char short_code[MAX_SHORT_CODE_LEN]; // 6位短码（唯一标识）
    ExpireType expire_type;         // 有效期类型（关联上面的枚举）
    int expire_days;                // 有效期天数（自定义类型时生效）
    time_t create_time;             // 创建时间戳（秒级，从1970-01-01开始）
    int visit_count;                // 该短网址的访问次数
    bool is_valid;                  // 是否有效（未过期/未被禁用）
} ShortUrl;

// ====================== 全局变量（存储所有短网址数据） ======================
ShortUrl url_list[MAX_URL_COUNT]; // 短网址数组（存储所有生成的短网址）
int url_count = 0;                // 当前已存储的短网址数量

// ====================== 工具函数（辅助功能） ======================
/**
 * 格式化时间戳为可读字符串
 * @param t 时间戳（time_t类型）
 * @param time_str 输出的时间字符串缓冲区
 * @param max_len 缓冲区最大长度
 */
void format_time(time_t t, char *time_str, int max_len) {
    struct tm *tm_info = localtime(&t); // 转换为本地时间结构体
    // 格式化为 "年-月-日 时:分:秒" 字符串
    strftime(time_str, max_len, "%Y-%m-%d %H:%M:%S", tm_info);
}

/**
 * 检查短码是否已存在（保证短码唯一性）
 * @param short_code 待检查的短码
 * @return 存在返回true，不存在返回false
 */
bool is_short_code_exist(const char *short_code) {
    // 遍历所有已存储的短网址，对比短码
    for (int i = 0; i < url_count; i++) {
        if (strcmp(url_list[i].short_code, short_code) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * 生成随机短码（指定长度）
 * @param short_code 输出短码的缓冲区
 * @param code_len 短码长度（不含结束符）
 */
void generate_random_short_code(char *short_code, int code_len) {
    // 仅初始化一次随机数种子（避免多次调用导致随机数重复）
    static bool seed_init = false;
    if (!seed_init) {
        srand((unsigned int)time(NULL)); // 以当前时间为种子
        seed_init = true;
    }

    memset(short_code, 0, code_len + 1); // 清空缓冲区（避免脏数据）
    // 逐位生成随机字符（从字符集选取）
    for (int i = 0; i < code_len; i++) {
        int rand_idx = rand() % CHARSET_LEN; // 生成0-61的随机索引
        short_code[i] = CHARSET[rand_idx];  // 从字符集取对应字符
    }
}

/**
 * 生成唯一的随机短码（循环生成+查重，直到生成唯一值）
 * @param short_code 输出唯一短码的缓冲区
 */
void create_unique_short_code(char *short_code) {
    do {
        // 生成6位随机短码（MAX_SHORT_CODE_LEN-1 = 6）
        generate_random_short_code(short_code, MAX_SHORT_CODE_LEN - 1);
    } while (is_short_code_exist(short_code)); // 重复生成直到短码唯一
}

/**
 * 检查短网址是否过期
 * @param url 待检查的短网址结构体指针
 * @return 过期返回true，未过期返回false
 */
bool is_url_expired(ShortUrl *url) {
    // 永久有效则直接返回未过期
    if (url->expire_type == EXPIRE_PERMANENT) {
        return false;
    }

    time_t now = time(NULL); // 获取当前时间戳
    int expire_seconds;      // 有效期总秒数
    if (url->expire_type == EXPIRE_1DAY) {
        expire_seconds = 24 * 60 * 60; // 1天 = 86400秒
    } else {
        // 自定义天数：天数 * 每天秒数
        expire_seconds = url->expire_days * 24 * 60 * 60;
    }

    // 当前时间 - 创建时间 > 有效期秒数 → 过期
    return (now - url->create_time) > expire_seconds;
}

// ====================== 持久化函数（数据落地到文件/从文件加载） ======================
/**
 * 从文件加载短网址数据（程序启动时调用）
 */
void load_data_from_file() {
    // 以只读模式打开数据文件
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) { // 文件不存在（首次运行）
        printf("📂 首次运行，未检测到数据文件，将创建新文件\n");
        return;
    }

    url_count = 0; // 重置计数，重新加载
    // 循环读取文件内容，按格式解析到结构体数组
    // 格式：短码 有效期类型 有效期天数 创建时间戳 访问次数 是否有效 原始URL
    while (fscanf(fp, "%s %d %d %lld %d %d %[^\n]", 
           url_list[url_count].short_code,
           &url_list[url_count].expire_type,
           &url_list[url_count].expire_days,
           &url_list[url_count].create_time,
           &url_list[url_count].visit_count,
           &url_list[url_count].is_valid,
           url_list[url_count].original_url) != EOF) {
        url_count++; // 计数+1
        // 达到上限则停止加载
        if (url_count >= MAX_URL_COUNT) {
            printf("⚠️  数据文件条目已达上限，停止加载\n");
            break;
        }
    }

    fclose(fp); // 关闭文件
    printf("✅ 成功加载 %d 条短网址数据\n", url_count);
}

/**
 * 将所有短网址数据保存到文件（新增/修改后调用）
 */
void save_data_to_file() {
    // 以写入模式打开文件（覆盖原有内容）
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) { // 文件打开失败
        printf("❌ 数据文件保存失败！\n");
        return;
    }

    // 遍历所有短网址，按格式写入文件
    for (int i = 0; i < url_count; i++) {
        fprintf(fp, "%s %d %d %lld %d %d %s\n",
                url_list[i].short_code,
                url_list[i].expire_type,
                url_list[i].expire_days,
                url_list[i].create_time,
                url_list[i].visit_count,
                url_list[i].is_valid,
                url_list[i].original_url);
    }

    fclose(fp); // 关闭文件
    printf("✅ 数据已保存到文件：%s\n", DATA_FILE);
}

// ====================== 核心功能函数（业务逻辑） ======================
/**
 * 生成短网址（核心功能1）：接收用户输入→生成唯一短码→存储数据→保存到文件
 */
void create_short_url() {
    // 检查是否达到存储上限
    if (url_count >= MAX_URL_COUNT) {
        printf("❌ 短网址数量已达上限（%d条），无法新增！\n", MAX_URL_COUNT);
        return;
    }

    ShortUrl new_url = {0}; // 初始化新短网址结构体（所有字段置0）

    // 输入原始长URL（处理换行符）
    printf("请输入原始长URL：");
    fgets(new_url.original_url, MAX_URL_LEN, stdin); // 读取整行输入
    // 去除换行符（fgets会把回车\n读入，需手动剔除）
    new_url.original_url[strcspn(new_url.original_url, "\n")] = '\0';
    // 校验URL非空
    if (strlen(new_url.original_url) == 0) {
        printf("❌ 原始URL不能为空！\n");
        return;
    }

    // 选择有效期类型
    printf("请选择有效期类型：\n");
    printf("1 - 1天有效期\n");
    printf("2 - 自定义天数\n");
    printf("3 - 永久有效\n");
    int expire_choice;
    scanf("%d", &expire_choice);
    getchar(); // 吸收scanf后的换行符（避免后续fgets读取空行）

    // 根据选择设置有效期
    switch (expire_choice) {
        case 1: // 1天有效期
            new_url.expire_type = EXPIRE_1DAY;
            new_url.expire_days = 1;
            break;
        case 2: // 自定义天数
            new_url.expire_type = EXPIRE_CUSTOM;
            printf("请输入有效期天数：");
            scanf("%d", &new_url.expire_days);
            getchar(); // 吸收换行符
            // 容错：天数≤0则设为1天
            new_url.expire_days = (new_url.expire_days <= 0) ? 1 : new_url.expire_days;
            break;
        case 3: // 永久有效
            new_url.expire_type = EXPIRE_PERMANENT;
            new_url.expire_days = 0; // 永久有效时天数无意义，置0
            break;
        default: // 输入无效，默认永久有效
            printf("❌ 选择无效，默认设为永久有效！\n");
            new_url.expire_type = EXPIRE_PERMANENT;
            new_url.expire_days = 0;
            break;
    }

    // 生成唯一短码
    create_unique_short_code(new_url.short_code);

    // 初始化其他字段
    new_url.create_time = time(NULL); // 创建时间为当前时间戳
    new_url.visit_count = 0;          // 初始访问次数为0
    new_url.is_valid = true;          // 初始状态为有效

    // 将新短网址存入数组
    url_list[url_count++] = new_url;

    // 保存数据到文件（持久化）
    save_data_to_file();

    // 格式化输出结果
    char create_time_str[50];
    format_time(new_url.create_time, create_time_str, 50);
    printf("\n✅ 短网址生成成功！\n");
    printf("短地址：http://t.cn/%s\n", new_url.short_code); // 模拟短域名前缀
    printf("原始URL：%s\n", new_url.original_url);
    printf("创建时间：%s\n", create_time_str);
    if (new_url.expire_type == EXPIRE_PERMANENT) {
        printf("有效期：永久有效\n");
    } else {
        printf("有效期：%d天\n", new_url.expire_days);
    }
}

/**
 * 查看所有短网址（核心功能2）：遍历数组→检查过期状态→格式化输出所有数据
 */
void list_all_short_urls() {
    if (url_count == 0) { // 无数据时提示
        printf("📄 暂无短网址数据！\n");
        return;
    }

    // 打印表头
    printf("\n==================================== 所有短网址 ====================================\n");
    printf("%-8s %-40s %-20s %-10s %-10s %-8s\n", 
           "短码", "原始URL", "创建时间", "有效期", "访问次数", "状态");
    printf("-----------------------------------------------------------------------------------\n");

    // 遍历所有短网址
    for (int i = 0; i < url_count; i++) {
        ShortUrl *url = &url_list[i];
        // 实时检查并更新过期状态（即使文件中标记有效，过期后也置为失效）
        if (url->is_valid && is_url_expired(url)) {
            url->is_valid = false;
        }

        // 格式化创建时间
        char create_time_str[50];
        format_time(url->create_time, create_time_str, 50);

        // 生成有效期描述字符串
        char expire_desc[20];
        if (url->expire_type == EXPIRE_PERMANENT) {
            strcpy(expire_desc, "永久");
        } else {
            sprintf(expire_desc, "%d天", url->expire_days);
        }

        // 生成状态描述字符串
        char status[10];
        strcpy(status, url->is_valid ? "有效" : "失效");

        // 截断过长的URL（保证表格格式整齐，最多显示40个字符）
        char truncated_url[41];
        strncpy(truncated_url, url->original_url, 40);
        truncated_url[40] = '\0'; // 手动加结束符（strncpy可能不自动加）

        // 打印一行数据（对齐格式）
        printf("%-8s %-40s %-20s %-10s %-10d %-8s\n",
               url->short_code,
               truncated_url,
               create_time_str,
               expire_desc,
               url->visit_count,
               status);
    }
    printf("===================================================================================\n");
}

/**
 * 解析短网址（核心功能3）：输入短码→查询原始URL→更新访问次数
 */
void parse_short_url() {
    printf("请输入短网址的短码（6位）：");
    char input_code[MAX_SHORT_CODE_LEN];
    fgets(input_code, MAX_SHORT_CODE_LEN, stdin);
    // 去除换行符
    input_code[strcspn(input_code, "\n")] = '\0';

    // 遍历数组查询短码
    for (int i = 0; i < url_count; i++) {
        ShortUrl *url = &url_list[i];
        if (strcmp(url->short_code, input_code) == 0) {
            // 实时更新过期状态
            if (url->is_valid && is_url_expired(url)) {
                url->is_valid = false;
            }

            // 输出解析结果
            printf("\n📌 短码解析结果：\n");
            printf("短地址：http://t.cn/%s\n", url->short_code);
            printf("原始URL：%s\n", url->original_url);
            printf("创建时间：");
            char create_time_str[50];
            format_time(url->create_time, create_time_str, 50);
            printf("%s\n", create_time_str);
            
            if (url->is_valid) {
                url->visit_count++; // 有效则访问次数+1
                printf("状态：有效\n");
                printf("访问次数：%d\n", url->visit_count);
                save_data_to_file(); // 保存更新后的访问次数
            } else {
                printf("状态：已失效\n");
                printf("访问次数：%d\n", url->visit_count);
            }
            return; // 找到后直接返回，无需继续遍历
        }
    }
    // 遍历结束未找到
    printf("❌ 未找到该短码对应的短网址！\n");
}

/**
 * 显示主菜单（交互界面）
 */
void show_menu() {
    printf("\n==================== 短网址服务 ====================\n");
    printf("1. 生成短网址\n");
    printf("2. 查看所有短网址\n");
    printf("3. 解析短网址\n");
    printf("0. 退出程序\n");
    printf("====================================================\n");
    printf("请选择功能（0-3）：");
}

// ====================== 主函数（程序入口） ======================
int main() {
    // 程序启动时从文件加载历史数据
    load_data_from_file();

    int choice; // 存储用户菜单选择
    while (true) { // 无限循环，直到用户选择退出
        show_menu(); // 显示菜单
        scanf("%d", &choice);
        getchar(); // 吸收换行符，避免干扰后续输入

        // 根据用户选择执行对应功能
        switch (choice) {
            case 1: // 生成短网址
                create_short_url();
                break;
            case 2: // 查看所有短网址
                list_all_short_urls();
                break;
            case 3: // 解析短网址
                parse_short_url();
                break;
            case 0: // 退出程序
                printf("👋 程序退出，正在保存数据...\n");
                save_data_to_file(); // 退出前保存最新数据
                printf("✅ 数据保存完成，感谢使用！\n");
                exit(0); // 正常退出程序
            default: // 输入无效
                printf("❌ 输入无效，请选择0-3的选项！\n");
                break;
        }

        // 执行完功能后，等待用户按回车返回主菜单
        printf("\n按回车键返回主菜单...");
        getchar();
    }

    return 0;
}