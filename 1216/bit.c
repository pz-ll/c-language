#include <stdio.h>

int main(int argc, char const *argv[])
{
    // int n;
    // printf("请输入整数:");
    // scanf("%d", &n);

    // if ((n & 1) == 1)
    // {
    //     printf("奇数-odd\n");
    // }
    // else
    // {
    //     printf("偶数-even\n");
    // }

    // int a = 2;
    // int b = 3;
    // 案1
    // 2
    // 3异或,了解但不常用
    // a = a ^ b;
    // b = a ^ b;
    // a = a ^ b;
    // printf("a=%d,b=%d\n", a, b);

    // int a[] = {1, 2, 3, 4, 3, 2, 1};
    // int n = 0;
    // for (int i = 0; i < 7; i++)
    // {
    //     n = n ^ a[i];
    // }
    // printf("%d\n", n);

    // int a=3;
    // int b=~a;
    // printf("%d\n",b);
    // printf("%b\n",a);
    // printf("%b\n",b);

    // printf("%d,%d",-15,~(-15));

    int n;
    printf("请输入整数:"); // 转化为2进制
    scanf("%d", &n);

    for (int i = 0; i < 32; i++)
    {
        // 0000 0000  0000 0000  0000 0000  0000 0011
        //  01

        // method 1
        // printf("%d", (n >> (31 - i)) & 1);

        // me 2
        int b = 1 << (31 - i);
        printf("%d", (n & b) == b);
        if (i % 8 == 7)
            printf(" ");
    }
    
    return 0;
}
