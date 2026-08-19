#include <stdio.h>
#include <stdbool.h>

int main() {
    int num, digit;
    bool seen[10];

    printf("Enter numbers (enter <=0 to exit):\n");
    while (1) {
        // 重置标记数组
        for (int i = 0; i < 10; i++) {
            seen[i] = false;
        }
        bool has_repeat = false;

        printf("Enter a number: ");
        scanf("%d", &num);
        if (num <= 0) {
            break;  // 输入<=0时终止
        }

        // 检查重复数字
        int temp = num;  // 保存原始数字（避免修改后无法输出）
        while (temp > 0) {
            digit = temp % 10;
            if (seen[digit]) {
                has_repeat = true;
                break;  // 找到重复即退出循环
            }
            seen[digit] = true;
            temp /= 10;
        }

        // 输出结果
        if (has_repeat) {
            printf("Number %d has repeated digits\n", num);
        } else {
            printf("Number %d has no repeated digits\n", num);
        }
    }

    return 0;
}