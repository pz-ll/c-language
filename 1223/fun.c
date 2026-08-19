// fun.c
// 函数

#include <stdio.h>
#include <stdbool.h>

// #include <string.h>

// 当前路径的 自定义头文件
// 模块化：高内聚、低耦合
// KISS: Keep It Simple Stupid - 单一任务原则
#include "my.h"

// 函数声明：没有函数体
// void print_array(int x[], int len);
bool is_prime(int n)
{
    bool flag = true;
    // 2~n-1或2~n的平方根
    for (int i = 2; i * i <= n; i++)
    {
        if (!(n % i))
        {
            flag = false;
            break;
        }
    }

    return flag;
}

int fact(int n)
{
    //必须有收敛（返回条件）
    if (1 == n)
    {
        return 1;
    }
    //一个函数调用自身
    return n * fact(n - 1);
}

// 程序的入口
int main()
{


    // int a[] = {100, 200, 300, 400, 500};
    // int b[20] = {0};
    // int c[20] = {1};
    // DYP = Don't Repeat Yourself
    // print_array(a, 5);          //x=1,len=5

    // print_array(b, 20);         //a,b,c，实际参数
    // print_array(c, 20);

    // for (int i = 2, c = 0; c < 100; i++)
    // {
    //     if (is_prime(i))
    //     {
    //         printf("%d,", i);
    //         c++;
    //     }
    //     /* code */
    // }

    int r = fact(4);
    printf("%d\n",r);

    printf("%d\n",fact(9));

    return 0;
}

// 构成：函数名，参数列表，函数体，返回类型
//  声明、定义函数  参数：形式参数
// void print_array(int x[], int len)
// {

//     for (int i = 0; i < len; i++)
//     {
//         printf("%d,", x[i]);
//         /* code */
//     }
//     printf("\n");
// }