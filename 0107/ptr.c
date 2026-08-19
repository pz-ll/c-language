// ptr.c
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // int a = 32;
    // int *p = NULL;      // 初始化为空指针（0）
    //*p = 42;
    //%p
    // printf("%p\n", p);
    // printf("%d\n", *p);

    // p = &a;
    // if (p != NULL)
    // {
    //     printf("p = %d\n", *p);
    // }

    // 指针与数组
    // 数组：复合/组合数据类型
    //char ch[9] = {'a', 'b', 'c', 'd', 'l', 'l'};
    // ch++   错误❌️
    // 指针变量p
    //char *p = ch;
    // while (p < ch +5)
    // {
    //     printf("%c\n", *p++);
    // }

    // char *p1 = ch;
    // char *p2 = &ch[4];           //指针数组相加减
    // printf("%p,%p\n", p1, p2);
    // printf("%ld\n", p2 - p1);

    // printf("%c\n", *p);
    // p += 4; // ch地址不能改，但p为变量地址可改
    // printf("%c\n", *p);
    // //ch+=4
    // printf("%c\n",*(ch + 4));

    // int ch[9] = {0};
    // int *p = NULL;

    // 以下3种等价
    //p = ch;   //*p还是p等于,存疑
    // p = &ch
    // p = &ch[0]
    //printf("%p",p);

    // for (int i = 0; i < 9; i++)
    // {
    //     printf("%d,%d,%p\n", i, ch[i], &ch[i]);
    // }
    // printf("\n%p\n,%p\n,%p\n", ch, &ch, &ch[0]);

    return 0;
}
