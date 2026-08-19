//str.c
//字符串

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // char s1[] = "ad";
    // char s2[] = "afsfx";
    // char *a = &s1[1];
    // char *b = &s2[2];
    // printf("%p\n%p\n", &a, &b);

    // // 字符数组，**不**是字符串
    // char s1[] = {'a', 'b', 'a', 'b', 'a', 'b'};
    // // 字符数组，字符串
    // char s2[] = {'a', 'b', 'a', '\0', 'a', '\0'};
    // char s3[] = "hello"; // n+1 有个\0的
    // char *s4 = "hello";  // 8

    // //%s
    // printf("s1=%s,空间=%ld,字符串长度=%ld\n", s1, sizeof(s1), strlen(s1));
    // printf("s1=%s,空间=%ld,字符串长度=%ld\n", s2, sizeof(s2), strlen(s2));
    // printf("s1=%s,空间=%ld,字符串长度=%ld\n", s3, sizeof(s3), strlen(s3));
    // printf("s1=%s,空间=%ld,字符串长度=%ld\n", s4, sizeof(s4), strlen(s4));

    ////数组是一个指针常量
    // char s1[]="hello";
    // //s1 = "bye"    //错的不能改地址，相当于指针常量
    // s1[0]='B';
    // printf("%s\n",s1);

    ////指针变量，可以指向其它地址空间
    //字符串常量，不可变
    // char *s2="hello";
    // s2="bye";
    // //s2[0]='B'     //错的，不能改值，相当于常量指针
    // printf("%s\n",s2);
    return 0;
}
