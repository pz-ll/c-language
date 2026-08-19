#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Sex
{
    //字面值为0,1,2,3,但可以修改
    MALE,FEMALE,UNKOWN
};

struct Date
{
    int year;
    int month;
    int day;
}a1,a2,a3;

// 组合数据类型，封装多个成员
struct Student
{
    char name[16];
    char sex;
    int score;
    struct Date birthday;       //嵌套
    
};

int dayin(struct Student *s);
int update_score(struct Student *s, int a);

int main(int argc, char const *argv[])
{
    struct Student s1 = {"alice", 'W', 100,{2005,7,30}};
    struct Student s2 = {"bob", 'M', 66,.birthday={2027,9,4}};
    struct Student s3 = {"leo", 'M', 74};
    s3.birthday.year = 2005;
    s3.birthday.month = 2;
    s3.birthday.day = 28;
    struct Student s4;
    s4.score = 86;
    s4.sex = 'M';
    // s4.name = "jack";        //错的，字符数组不能直接赋值
    strcpy(s4.name, "jack");

    dayin(&s1);
    update_score(&s1, 59);
    dayin(&s1);
    dayin(&s2);
    dayin(&s3);
    // dayin(&s4);
    // printf("%ld\n",sizeof(s1));
    //  \t tab 重构
    // printf("%s\t%c\t%d\n",s1.name,s1.sex,s1.score);
    // printf("%s\t%c\t%d\n",s2.name,s2.sex,s2.score);
    // printf("%s\t%c\t%d\n",s3.name,s3.sex,s3.score);

    return 0;
}

int dayin(struct Student *s)
{
    printf("%s\t%c\t%d\t%4d-%2d-%2d\n", s->name, s->sex, s->score,
    s->birthday.year,s->birthday.month,s->birthday.day);
}

int update_score(struct Student *s, int a)
{
    s->score = a;           //一样的
    //(*s).score = a;
}
