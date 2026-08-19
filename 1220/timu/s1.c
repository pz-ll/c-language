#include <stdio.h>
#include <stdbool.h>

int main() {
    int num, digit;
    bool seen[10] = {false};  // 记录数字是否出现过
    bool repeated[10] = {false};  // 记录重复数字

    printf("Enter a number: ");
    scanf("%d", &num);

    // 处理0的特殊情况
    if (num == 0) {
        printf("Repeated digit(s): 0\n");
        return 0;
    }

    // 提取每一位数字
    while (num > 0) {
        digit = num % 10;
        if (seen[digit]) {
            repeated[digit] = true;  // 标记重复数字
        } else {
            seen[digit] = true;     // 标记首次出现
        }
        num /= 10;
    }

    // 输出重复数字
    printf("Repeated digit(s): ");
    for (int i = 0; i < 10; i++) {
        if (repeated[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}