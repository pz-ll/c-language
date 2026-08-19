#include <stdio.h>
// pointer.c

int swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

int main(int argc, char const *argv[])
{

    int a = 2;
    int b = 3;
    // swap(x,y)
    // int t = a;
    // a = b;
    // b = t;
    swap(&a,&b);

    printf("a=%d,b=%d\n", a, b);

    // char c = 'C';
    // int i = 42;
    // double d = 3.14159;

    // printf("%lu\n", sizeof c);
    // printf("%lu\n", sizeof i);
    // printf("%lu\n", sizeof d);

    // char *p1 = &c;
    // int *p2 = &i;
    // double *p3 = &d;

    // // 可以存储各种类型变量的地址，但不能解引用
    // void *p;
    // p = &c;
    // p = &i;
    // p = &d;

    // printf("指针大小:%lu,值:%p,指针所指向空间的数据:%c\n,", sizeof(p1), p1, *p1);
    // printf("指针大小:%lu,值:%p,指针所指向空间的数据:%d\n", sizeof(p2), p2, *p2);
    // printf("指针大小:%lu,值:%p,指针所指向空间的数据:%lf\n", sizeof(p3), p3, *p3);

    return 0;
}
