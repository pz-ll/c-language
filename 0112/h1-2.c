#include <stdio.h>  // 标准输入输出：printf、sprintf
#include <string.h> // 字符串操作：strlen、strcpy、strcat
#include <stdlib.h> // 内存管理：malloc、free

/**
 * @brief 校验拼接后的字符串是否满足「1-9无重复、无0、长度为9」
 * @param str 待校验的字符串（a+b+c拼接结果，需为9位）
 * @return 1-符合所有条件；0-不符合（空指针/长度不对/含0/数字重复/缺数字）
 * @note 核心校验逻辑：
 *       1. 空指针直接返回0，避免崩溃
 *       2. 长度必须为9（3个三位数拼接）
 *       3. 排除数字0，且1-9每个数字仅出现1次
 */
int checkStr(char *str)
{
    // 1. 健壮性校验：空指针直接返回（避免strlen访问空地址崩溃）
    if (str == NULL)
        return 0;

    // 2. 长度校验：必须是9位（3个三位数拼接，无多余/缺失位）
    int len = strlen(str);
    if (len != 9)
        return 0;

    // 数字标记数组：digits[0]弃用（排除0），digits[1-9]标记对应数字是否出现
    int digits[10] = {0};

    // 逐字符遍历，校验数字合法性
    for (int i = 0; i < len; i++)
    {
        // 字符转数字（ASCII码差值：'1'-'0'=1，'9'-'0'=9）
        int num = str[i] - '0';

        // 3. 排除含0的情况（题目要求仅用1-9）
        if (num == 0)
        {
            return 0;
        }

        // 4. 校验数字重复：已出现过则返回0
        if (digits[num] == 1)
        {
            return 0;
        }

        // 标记该数字已出现
        digits[num] = 1;
    }

    // 5. 完整性校验：确保1-9每个数字都恰好出现1次
    for (int i = 1; i < 10; i++)
    {
        if (digits[i] == 0)
            return 0;
    }

    // 所有条件满足
    return 1;
}

/**
 * @brief 主函数：寻找满足条件的三位数组合（a, b=2a, c=3a，数字覆盖1-9无重复/无0）
 * @return 0-程序正常结束；1-内存分配失败
 * @note 核心优化点：
 *       1. 提前过滤无效a（个位为5的a，b=2a个位为0，直接跳过）
 *       2. 内存分配显式指定sizeof(char)，增强可移植性
 *       3. 代码分段注释，逻辑块清晰
 *       4. 严格的内存管理：malloc后检查NULL，结束后统一free
 */
int main(int argc, char const *argv[])
{
    int a, b, c; // 核心变量：a为基础三位数，b=2a，c=3a

    // 动态分配字符串缓冲区（显式sizeof(char)增强可移植性）
    // a_str/b_str/c_str：存储3位数字+结束符'\0'，需4字节
    // total_str：存储9位拼接结果+结束符'\0'，需10字节
    char *a_str = (char *)malloc(4 * sizeof(char));
    char *b_str = (char *)malloc(4 * sizeof(char));
    char *c_str = (char *)malloc(4 * sizeof(char));
    char *total_str = (char *)malloc(10 * sizeof(char));

    // 健壮性检查：内存分配失败时，释放已分配内存并退出
    if (a_str == NULL || b_str == NULL || c_str == NULL || total_str == NULL)
    {
        printf("错误：内存分配失败！\n");
        // 释放已成功分配的内存（避免泄漏）
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

    // 输出标题，提升可读性
    printf("满足条件的组合(a, b=2a, c=3a,数字覆盖1-9无重复/无0):\n");
    printf("----------------------------------------------------\n");

    // 遍历a的有效范围：100 ≤ a ≤ 333（保证c=3a≤999，仍是三位数）
    for (a = 100; a <= 333; a++)
    {
        // 性能优化：提前过滤无效a
        // 若a的个位为5，b=2a的个位必为0（违反无0规则），直接跳过
        if (a % 10 == 5)
        {
            continue;
        }

        // 计算b和c（核心逻辑：b=2a，c=3a）
        b = a * 2;
        c = a * 3;

        // 整数转字符串（sprintf自动添加结束符'\0'，4字节缓冲区足够）
        snprintf(a_str, 4, "%d", a);
        snprintf(b_str, 4, "%d", b);
        snprintf(c_str, 4, "%d", c);

        // 拼接三个字符串为总字符串（a+b+c）
        strcpy(total_str, a_str); // 先复制a的字符串
        strcat(total_str, b_str); // 追加b的字符串
        strcat(total_str, c_str); // 追加c的字符串

        // 校验并输出符合条件的组合
        if (checkStr(total_str))
        {
            printf("a = %-4d, b = %-4d, c = %-4d\n", a, b, c); // 格式化输出，对齐更美观
        }
    }

    // 释放所有动态分配的内存（避免内存泄漏）
    free(a_str);
    free(b_str);
    free(c_str);
    free(total_str);

    printf("\n程序执行完毕,内存已全部释放。\n");
    return 0;
}