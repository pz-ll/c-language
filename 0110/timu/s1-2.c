#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 人民币大写数字转换函数
void num_to_rmb(const char *num_str) {
    // 大写数字
    char *m[] = {"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};
    // 修正：数位单位数组（索引对应pos：1=个位,2=十位,3=百位,4=千位,5=万位,6=十万位,7=百万位,8=千万位,9=亿位）
    char *unit[] = {"", "", "十", "百", "千", "万", "十", "百", "千", "亿"};
    
    int len = strlen(num_str);
    // 校验输入是否为纯数字
    for (int i = 0; i < len; i++) {
        if (num_str[i] < '0' || num_str[i] > '9') {
            printf("输入错误!请输入纯数字(0-99999999)\n");
            return;
        }
    }
    printf("%d",len);
    // 处理特殊情况：输入为0
    if (strcmp(num_str, "0") == 0) {
        printf("零元整\n");
        return;
    }
    
    int last_zero = 1;  // 标记上一位是否是0（初始为1表示无前置0）
    int has_value = 0;  // 标记是否已经输出过有效数字
    int digit;          // 当前位的数字
    int has_wan = 0;    // 标记是否已经输出过“万”（避免重复）

    for (int i = 0; i < len; i++) {
        digit = num_str[i] - '0';
        // 当前位的数位索引（从右往左数：个位=1，十位=2，百位=3...千万位=8）
        int pos = len - i;
        
        if (digit != 0) {
            // 补零逻辑：前一位是0且已有有效数字，输出“零”
            if (!last_zero && has_value) {
                printf("零");
            }
            // 特殊处理：十位（pos=2）且数字是1时，省略“壹”（符合人民币书写习惯）
            if (!(pos == 2 && digit == 1 && i == 0 && len == 2)) {
                printf("%s", m[digit]);   // 输出大写数字
            }
            printf("%s", unit[pos]);      // 输出数位单位
            last_zero = 1;                // 标记当前位非0
            has_value = 1;                // 标记已有有效数字
            // 标记万位已输出
            if (pos == 5) {
                has_wan = 1;
            }
        } else {
            // 零的处理逻辑优化：
            // 1. 万位（pos=5）：有有效数字且未输出过“万”，补“万”
            if (pos == 5 && has_value && !has_wan) {
                printf("万");
                has_wan = 1;
            }
            // 2. 连续零只标记，不输出
            last_zero = 0;
        }
    }
    
    // 补充人民币结尾（规范写法）
    printf("元整\n");
}

int main(int argc, char const *argv[]) {
    char n[16];
    printf("请输入需要转换的数字(0-99999999):");
    // 读取输入并去除换行符
    fgets(n, sizeof(n), stdin);
    n[strcspn(n, "\n")] = '\0';
    
    num_to_rmb(n);
    
    return 0;
}