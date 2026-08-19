// ptr2.c
// 常量指针和指针常量
#include <stdio.h>



int main(int argc, char const *argv[])
{

    


    // int a = 1;
    // int b = 2;

    // 指针常量:地址不可以改
    // int *const p = &a; // p->a
    // // p = &b;               //p->b修改不成
    // printf("%d\n", a);
    // *p = 8;
    // printf("%d\n", a);

    // 常量指针:值是常量
    //  int const *p = &a;
    //  printf("%d\n", *p);

    //  p = &b;          //修改地址
    // //*p = 9;         //不能改值
    // printf("%d\n", *p);

    //指向常量 的指针常量
    //值和地址都是常量
    //int const *const h = &a;
    //h = &b;       //❌️
    //*h=3;         //不能改

    return 0;
}
