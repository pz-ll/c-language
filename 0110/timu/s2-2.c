#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 整数转16进制字符串函数（返回动态分配的字符指针，需手动释放）
char* int_to_hex(int num) {
    // 16进制字符表
    const char hex_chars[] = "0123456789ABCDEF";
    // 最多需要存储 8位16进制 + 1位结束符（int占4字节=32位）
    int buf_size = 16;
    char* result = (char*)malloc(buf_size * sizeof(char));
    // 检查内存分配是否成功
    if (result == NULL) {
        fprintf(stderr, "内存分配失败！\n");
        return NULL;
    }

    int index = 0;
    // 把负数转为无符号数，按补码规则处理
    unsigned int unum = (unsigned int)num;

    // 处理0的特殊情况
    if (unum == 0) {
        result[index++] = '0';
        result[index] = '\0';
        return result;
    }

    // 除16取余，记录余数对应的16进制字符（低位到高位）
    while (unum > 0) {
        int remainder = unum % 16;
        result[index++] = hex_chars[remainder];
        // 防止缓冲区溢出（极端情况保护）
        if (index >= buf_size - 1) {
            buf_size *= 2;
            result = (char*)realloc(result, buf_size * sizeof(char));
            if (result == NULL) {
                fprintf(stderr, "内存重分配失败！\n");
                return NULL;
            }
        }
        unum = unum / 16;
    }

    // 逆序字符串（余数是低位到高位，需要反转成正常顺序）
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - 1 - i];
        result[index - 1 - i] = temp;
    }

    // 添加字符串结束符
    result[index] = '\0';

    return result;
}

// 测试函数
int main() {
    int num;
    printf("请输入整数: ");
    scanf("%d", &num);
    
    char* hex_str = int_to_hex(num);
    // 检查函数返回是否正常
    if (hex_str != NULL) {
        printf("%d 的16进制为: 0x%s\n", num, hex_str);
        // 释放动态分配的内存，避免内存泄漏
        free(hex_str);
        hex_str = NULL; // 避免野指针
    }

    return 0;
}