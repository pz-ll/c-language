#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 辅助函数1：反转字符串（方便从低位开始计算）
char* reverse_str(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
    }
    return s;
}

// 辅助函数2：比较两个大整数字符串的大小（a>b返回1，a<b返回-1，相等返回0）
int compare_big_num(char *a, char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    // 长度不同，长的数更大
    if (len_a != len_b) {
        return len_a > len_b ? 1 : -1;
    }
    // 长度相同，逐位比较
    for (int i = 0; i < len_a; i++) {
        if (a[i] != b[i]) {
            return a[i] > b[i] ? 1 : -1;
        }
    }
    return 0; // 两数相等
}

// 辅助函数3：去掉前导零（保证结果规范）
char* remove_leading_zero(char *s) {
    int len = strlen(s);
    int start = 0;
    // 找到第一个非零字符
    while (start < len && s[start] == '0') {
        start++;
    }
    // 全零的情况，返回"0"
    if (start == len) {
        return "0";
    }
    // 截取非零开头的字符串
    char *res = (char*)malloc(len - start + 1);
    strcpy(res, s + start);
    return res;
}

// 大整数加法（支持任意长度正整数相加）
char* big_num_add(char *a, char *b) {
    // 复制字符串避免修改原数据，然后反转
    char *rev_a = reverse_str(strdup(a));
    char *rev_b = reverse_str(strdup(b));
    int len_a = strlen(rev_a);
    int len_b = strlen(rev_b);
    // 结果最大长度 = 较长数长度 + 1（进位）
    int max_len = (len_a > len_b ? len_a : len_b) + 1;
    char *res = (char*)malloc(max_len + 1); // +1 留字符串结束符位置
    int carry = 0; // 进位标记
    int i = 0;

    // 逐位相加，直到所有位处理完且无进位
    while (i < len_a || i < len_b || carry != 0) {
        // 取出当前位的数字（超出长度则为0）
        int digit_a = (i < len_a) ? (rev_a[i] - '0') : 0;
        int digit_b = (i < len_b) ? (rev_b[i] - '0') : 0;
        // 当前位总和 = 位1 + 位2 + 进位
        int sum = digit_a + digit_b + carry;
        // 存储当前位结果（取余）
        res[i] = (sum % 10) + '0';
        // 更新进位（整除）
        carry = sum / 10;
        i++;
    }
    res[i] = '\0'; // 字符串结束符

    // 反转结果，去掉前导零
    reverse_str(res);
    char *final_res = remove_leading_zero(res);

    // 释放临时内存
    free(rev_a);
    free(rev_b);
    free(res);
    return final_res;
}

// 大整数减法（仅支持正整数相减，a - b）
char* big_num_sub(char *a, char *b) {
    int cmp = compare_big_num(a, b);
    // 两数相等，结果为0
    if (cmp == 0) {
        return "0";
    }

    int is_negative = 0; // 结果是否为负
    char *big, *small;
    // 确定被减数和减数（保证大数减小数）
    if (cmp < 0) {
        big = b;
        small = a;
        is_negative = 1; // a < b，结果为负
    } else {
        big = a;
        small = b;
    }

    // 复制并反转，方便低位计算
    char *rev_big = reverse_str(strdup(big));
    char *rev_small = reverse_str(strdup(small));
    int len_big = strlen(rev_big);
    int len_small = strlen(rev_small);
    char *res = (char*)malloc(len_big + 1);
    int borrow = 0; // 借位标记
    int i = 0;

    // 逐位相减
    while (i < len_big) {
        // 取出当前位数字，减去借位
        int digit_big = (i < len_big) ? (rev_big[i] - '0') : 0;
        digit_big -= borrow;
        borrow = 0; // 重置借位

        // 取出减数当前位（超出长度则为0）
        int digit_small = (i < len_small) ? (rev_small[i] - '0') : 0;

        // 当前位不够减，借位
        if (digit_big < digit_small) {
            digit_big += 10;
            borrow = 1; // 标记需要借位
        }

        // 存储当前位结果
        res[i] = (digit_big - digit_small) + '0';
        i++;
    }
    res[i] = '\0';

    // 反转结果，去掉前导零
    reverse_str(res);
    char *final_res = remove_leading_zero(res);

    // 处理负数情况
    if (is_negative) {
        char *neg_res = (char*)malloc(strlen(final_res) + 2);
        neg_res[0] = '-'; // 加负号
        strcpy(neg_res + 1, final_res);
        free(final_res);
        final_res = neg_res;
    }

    // 释放临时内存
    free(rev_big);
    free(rev_small);
    free(res);
    return final_res;
}

// 测试函数
int main() {
    // 定义两个大整数（字符数组存储，长度可自定义）
    char a[32] = "99999999999999999999";
    char b[32] = "22222222222222222222";

    // 测试加法
    char *add_result = big_num_add(a, b);
    printf("加法：%s + %s = %s\n", a, b, add_result);
    free(add_result); // 释放内存

    // 测试减法（a - b）
    char *sub_result1 = big_num_sub(a, b);
    printf("减法：%s - %s = %s\n", a, b, sub_result1);
    free(sub_result1);

    // 测试减法（b - a，结果为负）
    char *sub_result2 = big_num_sub(b, a);
    printf("减法：%s - %s = %s\n", b, a, sub_result2);
    free(sub_result2);

    // 测试边界情况（全零、前导零）
    char c[32] = "000000";
    char d[32] = "0";
    char *add_zero = big_num_add(c, d);
    printf("边界测试：%s + %s = %s\n", c, d, add_zero);
    free(add_zero);

    return 0;
}