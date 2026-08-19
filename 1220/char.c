// char,c

#include <stdio.h>
int main(int argc, char const *argv[])
{
    

    char s1[] = {'a', 'b', 'c'}; // 3
    // 字符串“”括住的文本内容，空间大小是元素大小+1
    char s2[] = "abc";                 // 4
    char ch[] = "中";       //每个汉字3字节，空间+1
    char s3[] = {'a', 'b', 'c', '\0'}; // 4
    printf("%ld\n", sizeof(s1));
    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s3);
    printf("%s\n", ch);

    // char ch1 = '1';
    // char ch2 = 1;
    // printf("%d,'%c'\n",ch1,ch1);
    // printf("%d,%c\n",ch2,ch2);
    // for (int i = 0; i <= 128; i++)
    // {
    //     /* code */
    //     printf("'%c'(%3d)\t", i, i);
    //     if (i % 8 == 7)
    //         printf("\n");
    // }

    // char ch = 'a';
    // printf("%c\n",ch + 2);
    // char ch;
    // printf("请输入一个字符:");
    // scanf("%c",&ch);

    // ch = getchar();
    // putchar(ch);
    // if (ch >= '0' && ch <= '9')
    // {
    //     printf("数字\n");
    // }
    // if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
    // {
    //     printf("字母\n");
    // }

    return 0;
}
