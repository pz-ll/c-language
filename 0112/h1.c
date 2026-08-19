#include <stdio.h>  // 标准输入输出库，用于printf打印结果
#include <string.h> // 字符串处理库，用于strlen/strcpy/strcmp等操作
#include <stdlib.h> // 内存管理库，用于malloc/free/calloc等操作
#include <stdbool.h>

int checkStr(char *str)
{
    bool flag = true;
    if (str == NULL)
        return 0;
    int len = strlen(str);
    if (len != 9)
        return 0;

    int digits[10] = {0};

    for (int i = 0; i < len; i++)
    {
        // 字符转数字（'1'→1，'9'→9）
        int num = str[i] - '0';

        // 3. 排除含0的情况
        if (num == 0)
        {
            return 0;
        }
        if (digits[num] == 1)
        {
            return 0;
        }
        digits[num] = 1;
    }
    for (int i = 1; i < 10; i++)
    {
        if (digits[i] == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    int a, b, c;
    char *a_str = malloc(4);
    char *b_str = malloc(4);
    char *c_str = malloc(4);
    char *total_str = malloc(10);

    if (a_str == NULL || b_str == NULL || c_str == NULL || total_str == NULL)
    {
        printf("内存分配失败！\n");
        // 释放已分配的内存，避免泄漏
        if (a_str)
            free(a_str);
        if (b_str)
            free(b_str);
        if (c_str)
            free(c_str);
        if (total_str)
            free(total_str);
        return 1;
    }

    for (a = 123; a <= 333; a++)
    {
        b = a * 2;
        c = a * 3;
        sprintf(a_str, "%d", a);
        sprintf(b_str, "%d", b);
        sprintf(c_str, "%d", c);

        strcpy(total_str, a_str);
        strcat(total_str, b_str);
        strcat(total_str, c_str);

        if (checkStr(total_str))
        {
            printf("a = %d, b = %d, c = %d\n", a, b, c);
        }
    }
    free(a_str);
    free(b_str);
    free(c_str);
    free(total_str);

    return 0;
}
