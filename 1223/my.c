#include<stdio.h>

//函数定义
void print_array(int x[], int len)
{

    for (int i = 0; i < len; i++)
    {
        printf("%d,", x[i]);
        /* code */
    }
    printf("\n");
}