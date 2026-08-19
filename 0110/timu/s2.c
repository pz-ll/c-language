#include <stdio.h>
#include <string.h>

// 整数参数的16进制转换函数
char* int_to_hex(int num) {
    // 16进制字符表
    char x[] = "0123456789ABCDEF";
    // 静态缓冲区存储结果
    static char result[16];
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
        result[index++] = x[remainder];
        unum = unum / 16;
    }

    // 逆序字符串（因为余数是从低位到高位得到的，需要反转成正常顺序）
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
    printf("请输入整数:");
    scanf("%d",&num);
    printf("%d的16进制为:0x%s\n",num,int_to_hex(num));
    return 0;
}