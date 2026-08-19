#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// ====================== 配置常量 ======================
#define MAX_URL_COUNT 1000    // 最大存储数量
#define MAX_URL_LEN 2048      // 长URL最大长度
#define MAX_SHORT_CODE_LEN 7  // 短码长度（6位+结束符）
#define DATA_FILE "url_data.txt" // 数据持久化文件
const char CHARSET[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int CHARSET_LEN = 62;

// ====================== 结构体定义 ======================
// 有效期类型
typedef enum {
    EXPIRE_1DAY,
    EXPIRE_CUSTOM,
    EXPIRE_PERMANENT
} ExpireType;

// 短网址结构体
typedef struct {
    char original_url[MAX_URL_LEN];
    char short_code[MAX_SHORT_CODE_LEN];
    ExpireType expire_type;
    int expire_days;
    time_t create_time;
    int visit_count;
    bool is_valid;
} ShortUrl;

// ====================== 全局变量 ======================
ShortUrl url_list[MAX_URL_COUNT];
int url_count = 0;

// ====================== 工具函数 ======================
// 格式化时间戳为字符串
void format_time(time_t t, char *time_str, int max_len) {
    struct tm *tm_info = localtime(&t);
    strftime(time_str, max_len, "%Y-%m-%d %H:%M:%S", tm_info);
}

// 检查短码是否已存在
bool is_short_code_exist(const char *short_code) {
    for (int i = 0; i < url_count; i++) {
        if (strcmp(url_list[i].short_code, short_code) == 0) {
            return true;
        }
    }
    return false;
}

// 生成随机短码（指定长度）
void generate_random_short_code(char *short_code, int code_len) {
    static bool seed_init = false;
    if (!seed_init) {
        srand((unsigned int)time(NULL));
        seed_init = true;
    }

    memset(short_code, 0, code_len + 1);
    for (int i = 0; i < code_len; i++) {
        int rand_idx = rand() % CHARSET_LEN;
        short_code[i] = CHARSET[rand_idx];
    }
}

// 生成唯一的随机短码（查重保证唯一）
void create_unique_short_code(char *short_code) {
    do {
        generate_random_short_code(short_code, MAX_SHORT_CODE_LEN - 1);
    } while (is_short_code_exist(short_code));
}

// 检查短网址是否过期
bool is_url_expired(ShortUrl *url) {
    if (url->expire_type == EXPIRE_PERMANENT) {
        return false;
    }

    time_t now = time(NULL);
    int expire_seconds;
    if (url->expire_type == EXPIRE_1DAY) {
        expire_seconds = 24 * 60 * 60;
    } else {
        expire_seconds = url->expire_days * 24 * 60 * 60;
    }

    return (now - url->create_time) > expire_seconds;
}

// ====================== 持久化函数 ======================
// 从文件加载数据
void load_data_from_file() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("📂 首次运行，未检测到数据文件，将创建新文件\n");
        return;
    }

    url_count = 0;
    while (fscanf(fp, "%s %d %d %lld %d %d %[^\n]", 
           url_list[url_count].short_code,
           &url_list[url_count].expire_type,
           &url_list[url_count].expire_days,
           &url_list[url_count].create_time,
           &url_list[url_count].visit_count,
           &url_list[url_count].is_valid,
           url_list[url_count].original_url) != EOF) {
        url_count++;
        if (url_count >= MAX_URL_COUNT) {
            printf("⚠️  数据文件条目已达上限，停止加载\n");
            break;
        }
    }

    fclose(fp);
    printf("✅ 成功加载 %d 条短网址数据\n", url_count);
}

// 保存数据到文件
void save_data_to_file() {
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) {
        printf("❌ 数据文件保存失败！\n");
        return;
    }

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

    fclose(fp);
    printf("✅ 数据已保存到文件：%s\n", DATA_FILE);
}

// ====================== 核心功能函数 ======================
// 生成短网址
void create_short_url() {
    if (url_count >= MAX_URL_COUNT) {
        printf("❌ 短网址数量已达上限（%d条），无法新增！\n", MAX_URL_COUNT);
        return;
    }

    ShortUrl new_url = {0}; // 初始化结构体

    // 输入原始URL（处理换行符）
    printf("请输入原始长URL：");
    fgets(new_url.original_url, MAX_URL_LEN, stdin);
    new_url.original_url[strcspn(new_url.original_url, "\n")] = '\0';
    if (strlen(new_url.original_url) == 0) {
        printf("❌ 原始URL不能为空！\n");
        return;
    }

    // 选择有效期
    printf("请选择有效期类型：\n");
    printf("1 - 1天有效期\n");
    printf("2 - 自定义天数\n");
    printf("3 - 永久有效\n");
    int expire_choice;
    scanf("%d", &expire_choice);
    getchar(); // 吸收换行符

    switch (expire_choice) {
        case 1:
            new_url.expire_type = EXPIRE_1DAY;
            new_url.expire_days = 1;
            break;
        case 2:
            new_url.expire_type = EXPIRE_CUSTOM;
            printf("请输入有效期天数：");
            scanf("%d", &new_url.expire_days);
            getchar();
            new_url.expire_days = (new_url.expire_days <= 0) ? 1 : new_url.expire_days;
            break;
        case 3:
            new_url.expire_type = EXPIRE_PERMANENT;
            new_url.expire_days = 0;
            break;
        default:
            printf("❌ 选择无效，默认设为永久有效！\n");
            new_url.expire_type = EXPIRE_PERMANENT;
            new_url.expire_days = 0;
            break;
    }

    // 生成唯一短码
    create_unique_short_code(new_url.short_code);

    // 初始化其他字段
    new_url.create_time = time(NULL);
    new_url.visit_count = 0;
    new_url.is_valid = true;

    // 存入数组
    url_list[url_count++] = new_url;

    // 保存到文件
    save_data_to_file();

    // 输出结果
    char create_time_str[50];
    format_time(new_url.create_time, create_time_str, 50);
    printf("\n✅ 短网址生成成功！\n");
    printf("短地址：http://t.cn/%s\n", new_url.short_code);
    printf("原始URL：%s\n", new_url.original_url);
    printf("创建时间：%s\n", create_time_str);
    if (new_url.expire_type == EXPIRE_PERMANENT) {
        printf("有效期：永久有效\n");
    } else {
        printf("有效期：%d天\n", new_url.expire_days);
    }
}

// 查看所有短网址
void list_all_short_urls() {
    if (url_count == 0) {
        printf("📄 暂无短网址数据！\n");
        return;
    }

    printf("\n==================================== 所有短网址 ====================================\n");
    printf("%-8s %-40s %-20s %-10s %-10s %-8s\n", 
           "短码", "原始URL", "创建时间", "有效期", "访问次数", "状态");
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < url_count; i++) {
        ShortUrl *url = &url_list[i];
        // 检查并更新过期状态
        if (url->is_valid && is_url_expired(url)) {
            url->is_valid = false;
        }

        // 格式化时间
        char create_time_str[50];
        format_time(url->create_time, create_time_str, 50);

        // 有效期描述
        char expire_desc[20];
        if (url->expire_type == EXPIRE_PERMANENT) {
            strcpy(expire_desc, "永久");
        } else {
            sprintf(expire_desc, "%d天", url->expire_days);
        }

        // 状态描述
        char status[10];
        strcpy(status, url->is_valid ? "有效" : "失效");

        // 输出（URL过长时截断，保证格式整齐）
        char truncated_url[41];
        strncpy(truncated_url, url->original_url, 40);
        truncated_url[40] = '\0';

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

// 解析短网址
void parse_short_url() {
    printf("请输入短网址的短码（6位）：");
    char input_code[MAX_SHORT_CODE_LEN];
    fgets(input_code, MAX_SHORT_CODE_LEN, stdin);
    input_code[strcspn(input_code, "\n")] = '\0';

    for (int i = 0; i < url_count; i++) {
        ShortUrl *url = &url_list[i];
        if (strcmp(url->short_code, input_code) == 0) {
            // 更新过期状态
            if (url->is_valid && is_url_expired(url)) {
                url->is_valid = false;
            }

            // 输出结果
            printf("\n📌 短码解析结果：\n");
            printf("短地址：http://t.cn/%s\n", url->short_code);
            printf("原始URL：%s\n", url->original_url);
            printf("创建时间：");
            char create_time_str[50];
            format_time(url->create_time, create_time_str, 50);
            printf("%s\n", create_time_str);
            if (url->is_valid) {
                url->visit_count++;
                printf("状态：有效\n");
                printf("访问次数：%d\n", url->visit_count);
                // 保存更新后的访问次数
                save_data_to_file();
            } else {
                printf("状态：已失效\n");
                printf("访问次数：%d\n", url->visit_count);
            }
            return;
        }
    }
    printf("❌ 未找到该短码对应的短网址！\n");
}

// 主菜单
void show_menu() {
    printf("\n==================== 短网址服务 ====================\n");
    printf("1. 生成短网址\n");
    printf("2. 查看所有短网址\n");
    printf("3. 解析短网址\n");
    printf("0. 退出程序\n");
    printf("====================================================\n");
    printf("请选择功能（0-3）：");
}

// ====================== 主函数 ======================
int main() {
    // 程序启动时加载数据
    load_data_from_file();

    int choice;
    while (true) {
        show_menu();
        scanf("%d", &choice);
        getchar(); // 吸收换行符

        switch (choice) {
            case 1:
                create_short_url();
                break;
            case 2:
                list_all_short_urls();
                break;
            case 3:
                parse_short_url();
                break;
            case 0:
                printf("👋 程序退出，正在保存数据...\n");
                save_data_to_file();
                printf("✅ 数据保存完成，感谢使用！\n");
                exit(0);
            default:
                printf("❌ 输入无效，请选择0-3的选项！\n");
                break;
        }

        printf("\n按回车键返回主菜单...");
        getchar();
    }

    return 0;
}