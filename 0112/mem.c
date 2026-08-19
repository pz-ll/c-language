// mem.c
// 动态内存管理
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mem
{
    char tel1[11]; // 11
    char *tel2;    // 8
} u1;

char *cat(char *a, char *b)
{
    int size = strlen(a) + strlen(b) + 1;
    // char str[size];   //错误,函数不能返回局部变量地址
    char *str = (char *)malloc(size); // 正确✅️
    if (str != NULL)
    {
        strcpy(str, a);
        strcat(str, b);
    }
    return str;
}

int main(int argc, char const *argv[])
{
    char *p = calloc(1,19);         //大小+个数
    for (int i = 0; i < 19; i++)
    {
        printf("%c,%d\n",p[i],p[i]);
        /* code */
    }
    

    // strcpy(u1.tel1, "15964624562");
    // u1.tel2 = "14214521451";
    // printf("%s,%s\n",u1.tel1,u1.tel2);
    // u1.tel2 = malloc(12);        //不填充0，块
    // memset(u1.tel2, 0, 12);

    // u1.tel2 = malloc(12);        //填充0，慢

    // char *p = cat("hello", "c++");
    // printf("%s,%p\n", p, p);
    // free(p);

    // // 数组大小都是确定的
    // int a[6]; //固定的不变的

    // //动态内存分配
    // int *p = (int *)malloc(sizeof(int) * 6);

    // if (p == NULL)
    // {
    //     perror("内存不足\n");
    //     return EXIT_FAILURE;
    // }
    // // for (int i = 0; i < 6; i++)
    // // {
    // //     p[i] = 100 * (i + 1);
    // // }
    // p[0] = 100;
    // p[1] = 200;
    // p[2] = 300;
    // p[3] = 400;
    // p[4] = 500;
    // p[5] = 600;
    // printf("before re: %p\n", p);
    // p = realloc(p, sizeof(int) * 9);
    // printf("after re: %p\n", p);

    // // 释放
    // free(p);

    return EXIT_SUCCESS; // 相当于0
}
