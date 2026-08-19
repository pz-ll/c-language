#include <stdio.h>

int main() {
    int num, digit;
    int count[10] = {0};  // 统计0-9的出现次数

    printf("Enter a number: ");
    scanf("%d", &num);

    // 处理0的特殊情况
    if (num == 0) {
        count[0] = 1;
    } else {
        // 提取每一位数字并计数
        while (num > 0) {
            digit = num % 10;
            count[digit]++;
            num /= 10;
        }
    }

    // 输出结果
    printf("Digit:        ");
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i);
    }
    printf("\nOccurrences:  ");
    for (int i = 0; i < 10; i++) {
        printf("%2d ", count[i]);
    }
    printf("\n");

    return 0;
}