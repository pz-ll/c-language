#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 组合数据类型，封装多个成员
struct Student
{
    char name[16];
    char sex;
    int score;
};

int dayin(struct Student s)
{
    printf("%s\t%c\t%d\n",s.name,s.sex,s.score);
}

union dayin
{
    char a;
    int b;
}a1;
int main(int argc, char const *argv[])
{
    printf("%ld",sizeof(a1));
    return 0;
}

