#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fib(int n)
{
    int a = 1, b = 1;
    int c;
    if (n == 1 || n == 2)
        return 1;
    if (n >= 3)
    {
        for (int i = 2; i < n; i++)
        {
            c = a + b;
            a = b;
            b = c;
        }
    }
    return c;
}

int days(int year, int month, int day)
{
    int q = 0;
    int mout[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
    {
        mout[2] += 1;
    }
    for (int i = 1; i < month; i++)
    {
        q += mout[i];
    }
    q += day;

    return q;
}

struct Date
{
    int year;
    int month;
    int day;
};

int datecmp(struct Date *s1, struct Date *s2)
{
    int n1 = 0, n2 = 0, n3 = 0;
    int mout[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int i = 2000; i <= s1->year; i++)
    {
        if (i < s1->year)
            n1 += 365;
        if (i == s1->year)
        {
            for (int i = 1; i <= s1->month; i++)
            {
                n1 += mout[i];
            }
            n1 += s1->day;
        }
    }
    for (int i = 2000; i <= s2->year; i++)
    {
        if (i < s2->year)
            n2 += 365;
        if (i == s2->year)
        {
            for (int i = 1; i <= s2->month; i++)
            {
                n2 += mout[i];
            }
            n2 += s2->day;
        }
    }
    if (n1 > n2)
    {
        int t = n1;
        n1 = n2;
        n2 = t;
    }
    n3 = n2 - n1;

    return n3;
}

int main(int argc, char const *argv[])
{
    int n;
    printf("请输入斐波那契数列第n个数:");
    scanf("%d", &n);
    int year, month, day;
    printf("请输入年月:(2026-3-15)");
    scanf("%d-%d-%d", &year, &month, &day);
    // printf("斐波那契数列第%d数是%d\n", n, fib(n));
    // printf("%d-%d-%d是%d年的第%d天\n", year, month, day, year, days(year, month, day));

    struct Date s1;
    struct Date s2;
    printf("请输入2个日期(2025-3-7&2026-4-8):");
    scanf("%d-%d-%d&%d-%d-%d",
          &s1.year, &s1.month, &s1.day,
          &s2.year, &s2.month, &s2.day);
    printf("斐波那契数列第%d数是%d\n", n, fib(n));
    printf("%d-%d-%d是%d年的第%d天\n", year, month, day, year, days(year, month, day));

    printf("两个日期相差%d天\n", datecmp(&s1, &s2));
    return 0;
}
