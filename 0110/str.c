// str.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char s1[16] = "hello";
    char s2[] = "c++";
    int size = strlen(s1) + strlen(s2);
    char s4[size + 1];

    

    // // strtok token 拆分
    // char d1[] = "alice,boob-bead;afsjf fsd,gss";
    // char d2[sizeof(d1)];
    // strcpy(d2,d1);
    // // 1.目标字符串;2.分隔符
    // char *tok = strtok(d2, ",- ");          //可以有多个分隔符//会对原数据有所改变
    // while (tok)
    // {
    //     printf("%s\n", tok);
    //     //1.参数NULL
    //     tok = strtok(NULL,",- ");           //表示 “继续拆分之前的字符串”，返回下一个子串的地址。
    // }
    // printf("%s\n",d1);
    // printf("%s\n",d2);

    // // strstr字串查找
    // char b1[] = "hello";

    // // BF,KMP
    // char *w = strstr(b1, "lo");
    // if (w)
    // {
    //     printf("index=%ld\n", w - b1);
    //     printf("%s\n", w);
    // }
    // else
    // {
    //     printf("没有找到\n");
    // }

    // char c1[] = "javac";
    // char c2[] = "javbc";

    // strcmp字符查找
    //  int r = strcmp(c1, c2);         //前者的ascll值减后者的

    // char *p = strchr(c1 ,'q');      //返回指针,没找到返回NULL
    // if (p == NULL)
    // {
    //     printf("没有找到\n");
    // }
    // else{
    //     printf("%ld\n",p - c1);
    //     printf("%s\n", p);
    // }

    // printf("%d\n", r);

    // char s3[10]={0};
    // strcat(s3,"hello");
    // strcat(s3,"c++");
    // strcat(s4, s1);
    // strcat(s4, s2);
    // strcat(s1, s2);

    // strcpy(s1, s2);
    // strcpy(s4, s1);
    // strcat(s4, s2);
    // strncpy(s2,"welcom",sizeof(s2)-1);

    // printf("%s\n", s1);
    // printf("%s\n", s2);
    // printf("%s\n", s4);
    return 0;
}
