#include <stdio.h>

// 递归函数计算最大公约数
int gcd_recursive(int a, int b) {
    // 如果b为0，则a就是最大公约数
    if (b == 0) {
        return a;
    }
    // 否则递归调用，参数为b和a除以b的余数
    return gcd_recursive(b, a % b);
}
//大公约数的经典算法是Euclid算法，方法如下：
//分别让变量a 和b 存储两个数的值。如果b 为0，那么停止操作，a 中的值是GCD；
//否则计算a 除以b 的余数，把b 保存到a 中，并把余数保存到b 中。
//然后重复上述过程，每次都先判定b 是否为0。

int main() {
    int num1, num2;
    
    printf("请输入两个正整数: ");
    scanf("%d %d", &num1, &num2);
    
    // 确保输入为正数
    if (num1 <= 0 || num2 <= 0) {
        printf("请输入两个正整数！\n");
        return 1;
    }
    
    int result = gcd_recursive(num1, num2);
    printf("%d 和 %d 的最大公约数是: %d\n", num1, num2, result);
    
    return 0;
}