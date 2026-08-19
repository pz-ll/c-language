// person.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date
{
    int year;
    int month;
    int day;
} Date;

typedef struct Person
{
    char name[16];        // 姓名
    int age;              // 年龄
    Date birthday; // 生日   共生关系
    struct Person *lover; // 配偶   指针，可独立存在
} Person;

int main()
{
    // Person *p=(Person*)malloc(sizeof(Person));
    Person p = {"Alice", 21, {2023, 4, 66}};
    Person p2 = {"Bob"};
    p.lover = &p2;

    printf("%s\t%d\t%d-%d-%d\t%s\n", p.name, p.age,
           p.birthday.year,
           p.birthday.month,
           p.birthday.day,
           p.lover->name);
    return 0;
}
