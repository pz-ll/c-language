// stu.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义常量，宏定义
#define NAME_SIZE 16

typedef struct Date
{
    int year;
    int month;
    int day;
}Date;


// 定义一个新的数据类型
typedef struct Stdent
{
    char name[NAME_SIZE]; // 姓名
    int age;              // 年龄
    // struct Date birthday;       //
    // struct Date *birth;
    
} Stu;

int main(int argc, char const *argv[])
{

    // 动态(长度可变)数组
    Stu *ptr = (Stu *)malloc(4 * sizeof(struct Stdent));
    if (!ptr)
    {
        printf("内存分配失败\n");
        return EXIT_FAILURE;
    }
    Stu *p = ptr;
    for (int i = 0; i < 4; i++)
    {
        printf("请输入姓名与年龄:");
        // scanf("%s %d",(ptr+i)->name,&(ptr + i)->age);   //->的优先级高于&

        // 两种
        scanf("%s %d", p->name, &p->age);
        p++;

        // 字符串:学生1，学生2
        // char str[16];
        // sprintf(str, "%s %d", a, b);
        // 字段赋值
        // strcpy((ptr + i)->name, str);
        // (ptr + i)->age = 18 + i;
        // strcat(ptr[i].name, str);
        // ptr[i].age = 18 + i;

        // 打印
        // printf("%s\t%d\n", (ptr + i)->name, (ptr + i)->age);
    }
    for (int i = 0; i < 4; i++)
    {
        printf("%s\t%d\n", (ptr + i)->name, (ptr + i)->age);
    }

    free(ptr);

    // // Stu s1;
    // Stu a[4] = {
    //     {"猪猪星", 21},
    //     {"五灵王", 21},
    //     {"唐舞麟", 18}};
    // strncpy(a[3].name, "古月娜",NAME_SIZE-1);
    // a[3].age = 18;

    // Stu *p = a;
    // for (int i = 0; i <= 3; i++)
    // {
    //     //printf("%s\t%d\n", a[i].name, a[i].age);          //数组下标
    //     //printf("%s\t%d\n", (*p).name, (*p).age);          //指针
    //     printf("%s\t%d\n", p->name, p->age);            //指针 -> (多见)
    //     p++;
    // }
    return 0;
}
