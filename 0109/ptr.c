// ptr.c
#include <stdio.h>

int *f(int a, int b, int *r)
{
    *r = a + b; // 局部变量
    // int *p = &r;
    // return p;        //错误❌️
    return r;
}

void max(int *a, int len, int *r)
{
    //无返回的方案
    // *r = a[0];
    // for (int i = 1; i < len; i++)
    // {
    //     if (a[i] > *r)
    //         *r = a[i];
    // }

    r = a;
    
    for (int i = 1; i < len; i++)
    {
        if (*(a+i) > *r)
            r = a+i;
    }


    // 基于下标的
    //  int max = a[0];
    //  for (int i = 1; i < len; i++)
    //  {
    //      if (a[i] > max)
    //          max = a[i];
    //  }

    // 基于指针的
    // int max = *a;
    // for (int i = 1; i < len; i++)
    // {
    //     if (max < *(a + i))
    //     {
    //         max = *(a + i);
    //     }
    // }
    // return max;
}

int main(int argc, char const *argv[])
{

    int m[] = {0, 1, 2, 45, 6, 7, 77};
    int size = sizeof(m) / sizeof(m[0]);
    int r;
    //面向过程的程序设计思维方式
    max(m, size, &r);
    printf("%d\n", r);

    // int a = 1, b = 2;
    // int r;
    // int *p = f(a, b, &r);
    // printf("%p,%d\n", &r, r);
    return 0;
}
