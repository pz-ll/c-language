#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char m[16];
    printf(":");
    //scanf("%s",m);        //读取到空格结束
    //gets(m);              //读取到换行，不安全
    fgets(m, 15, stdin);    //从标准输入读取15个字符
    printf("%s\n", m);
    return 0;
}
