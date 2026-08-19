#include <stdio.h>   // 标准输入输出库，用于printf打印结果
#include <string.h>  // 字符串处理库，用于strlen/strcpy/strcmp等操作
#include <stdlib.h>  // 内存管理库，用于malloc/free/calloc等操作

/**
 * 辅助函数：反转字符串
 * 功能：将字符串首尾交换，使数字的低位（个位）出现在字符串头部
 * 目的：符合手工计算时"从低位到高位"的习惯，方便逐位处理
 * 参数：s - 待反转的字符串（注意：会直接修改原字符串）
 * 返回：反转后的字符串（与输入指针指向同一内存）
 */
char* reverse(char *s) {
    int len = strlen(s);  // 获取字符串长度（数字的位数）
    // 首尾交换：只需要循环到字符串中间位置
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];                          // 暂存左指针字符
        s[i] = s[len - 1 - i];                     // 右指针字符赋值给左指针
        s[len - 1 - i] = temp;                     // 暂存字符赋值给右指针
    }
    return s;
}

/**
 * 辅助函数：比较两个大整数字符串的大小
 * 功能：判断两个大整数的大小关系，为减法/除法提供依据
 * 参数：a - 第一个大整数字符串；b - 第二个大整数字符串
 * 返回：1（a > b）、-1（a < b）、0（a == b）
 */
int compare(char *a, char *b) {
    int lenA = strlen(a);  // 获取a的位数
    int lenB = strlen(b);  // 获取b的位数
    // 第一步：位数不同，位数多的数更大
    if (lenA != lenB) return lenA > lenB ? 1 : -1;
    // 第二步：位数相同，逐位比较字符（ASCII码：'9'>'8'>...>'0'）
    for (int i = 0; i < lenA; i++) {
        if (a[i] != b[i]) return a[i] > b[i] ? 1 : -1;
    }
    // 所有位都相同，两数相等
    return 0;
}

/**
 * 辅助函数：去掉字符串的前导零
 * 功能：规范大整数格式（如"00123"→"123"，"0000"→"0"）
 * 参数：s - 待处理的字符串
 * 返回：去除前导零后的新字符串（需要手动free释放内存）
 */
char* removeLeadingZeros(char *s) {
    int len = strlen(s);
    int start = 0;
    // 找到第一个非零字符的位置
    while (start < len && s[start] == '0') {
        start++;
    }
    // 特殊情况：全零字符串，直接返回"0"
    if (start == len) return "0";
    
    // 分配新内存，存储去除前导零后的字符串
    char *res = (char*)malloc(len - start + 1);  // +1 预留字符串结束符'\0'位置
    strcpy(res, s + start);  // 从第一个非零字符开始拷贝
    return res;
}

/**
 * 核心函数：大整数加法
 * 功能：计算两个非负大整数的和，支持超长位数（超出long long范围）
 * 原理：模拟手工加法，从低位到高位逐位相加，处理进位
 * 参数：a - 被加数（字符串）；b - 加数（字符串）
 * 返回：加法结果字符串（需要手动free释放内存）
 */
char* bigAdd(char *a, char *b) {
    // 1. 反转字符串：让低位在前（如"123"→"321"），方便逐位计算
    char *revA = reverse(strdup(a));  // strdup：复制字符串（避免修改原字符串）
    char *revB = reverse(strdup(b));
    
    // 2. 获取反转后字符串的长度，确定最大循环次数
    int lenA = strlen(revA), lenB = strlen(revB);
    int maxLen = lenA > lenB ? lenA : lenB;
    
    // 3. 分配结果内存：maxLen+2 → 预留1位存储最终进位，1位存储结束符
    char *res = (char*)malloc(maxLen + 2);
    int carry = 0;  // 进位标志（初始为0）
    int i = 0;      // 循环指针（指向当前处理的位）

    // 4. 逐位相加：处理所有位 + 最后的进位（carry≠0时仍需处理）
    while (i < maxLen || carry != 0) {
        // 获取当前位的数字（超出字符串长度则补0）
        int digitA = (i < lenA) ? (revA[i] - '0') : 0;  // 字符转数字：'5'-'0'=5
        int digitB = (i < lenB) ? (revB[i] - '0') : 0;
        
        // 计算当前位总和：位A + 位B + 上一轮进位
        int sum = digitA + digitB + carry;
        res[i] = (sum % 10) + '0';  // 当前位结果（取余10）：数字转字符
        carry = sum / 10;           // 新的进位（整除10）：0或1
        i++;
    }
    res[i] = '\0';  // 字符串结束符

    // 5. 反转结果，恢复正常顺序，去除前导零
    reverse(res);
    char *finalRes = removeLeadingZeros(res);

    // 6. 释放临时内存，避免内存泄漏
    free(revA);
    free(revB);
    free(res);

    return finalRes;
}

/**
 * 核心函数：大整数减法
 * 功能：计算两个非负大整数的差，支持结果为负数
 * 原理：模拟手工减法，先保证"大数减小数"，处理借位，最后补负号
 * 参数：a - 被减数（字符串）；b - 减数（字符串）
 * 返回：减法结果字符串（需要手动free释放内存）
 */
char* bigSub(char *a, char *b) {
    // 1. 先比较两数大小，处理特殊情况
    int cmp = compare(a, b);
    if (cmp == 0) return "0";  // 两数相等，结果为0

    int isNegative = 0;  // 结果是否为负数的标记（初始为0：正数）
    // 若a < b，交换a和b，标记结果为负数（保证后续只算"大数减小数"）
    if (cmp < 0) {
        char *temp = a;
        a = b;
        b = temp;
        isNegative = 1;
    }

    // 2. 反转字符串，低位在前，方便逐位计算
    char *revA = reverse(strdup(a));
    char *revB = reverse(strdup(b));
    int lenA = strlen(revA), lenB = strlen(revB);
    
    // 3. 分配结果内存：长度=大数的位数+1（存储结束符）
    char *res = (char*)malloc(lenA + 1);
    int borrow = 0;  // 借位标志（初始为0）
    int i = 0;       // 循环指针

    // 4. 逐位相减：处理借位
    while (i < lenA) {
        // 获取当前位的数字
        int digitA = (i < lenA) ? (revA[i] - '0') : 0;
        int digitB = (i < lenB) ? (revB[i] - '0') : 0;

        digitA -= borrow;  // 先减去上一轮的借位
        borrow = 0;        // 重置借位标志

        // 若当前位被减数 < 减数，需要借位
        if (digitA < digitB) {
            digitA += 10;  // 借1当10
            borrow = 1;    // 标记下一轮需要还借位
        }

        res[i] = (digitA - digitB) + '0';  // 当前位结果
        i++;
    }
    res[i] = '\0';  // 字符串结束符

    // 5. 反转结果，去除前导零
    reverse(res);
    char *finalRes = removeLeadingZeros(res);

    // 6. 释放临时内存
    free(revA);
    free(revB);
    free(res);

    // 7. 若结果为负数，拼接负号
    if (isNegative) {
        // 分配新内存：原长度+2（1位负号 + 1位结束符）
        char *negRes = (char*)malloc(strlen(finalRes) + 2);
        negRes[0] = '-';                // 第一位存负号
        strcpy(negRes + 1, finalRes);   // 后面拼接结果
        free(finalRes);                 // 释放原结果内存
        return negRes;
    }

    return finalRes;
}

/**
 * 核心函数：大整数乘法
 * 功能：计算两个非负大整数的积，支持超长位数
 * 原理：模拟手工乘法，逐位相乘后累加到对应位置，统一处理进位
 * 参数：a - 被乘数（字符串）；b - 乘数（字符串）
 * 返回：乘法结果字符串（需要手动free释放内存）
 */
char* bigMul(char *a, char *b) {
    int lenA = strlen(a), lenB = strlen(b);
    // 1. 分配整型数组存储中间结果：n位×m位，结果最多n+m位
    int resLen = lenA + lenB;
    int *res = (int*)calloc(resLen, sizeof(int));  // calloc：初始化为0

    // 2. 逐位相乘，累加到对应位置（从右到左遍历，符合手工乘法习惯）
    for (int i = lenA - 1; i >= 0; i--) {
        int digitA = a[i] - '0';  // 被乘数当前位数字
        for (int j = lenB - 1; j >= 0; j--) {
            int digitB = b[j] - '0';  // 乘数当前位数字
            int product = digitA * digitB;  // 两位相乘的结果

            // 关键：乘积的低位存到i+j+1位，高位存到i+j位
            res[i + j + 1] += product;          // 累加到当前位
            res[i + j] += res[i + j + 1] / 10;  // 处理进位（加到高位）
            res[i + j + 1] %= 10;               // 保留当前位的个位
        }
    }

    // 3. 将整型数组转换为字符串，去除前导零
    char *resStr = (char*)malloc(resLen + 1);
    int index = 0;  // 结果字符串的指针
    for (int i = 0; i < resLen; i++) {
        // 跳过前导零（第一个非零数字前的零）
        if (index == 0 && res[i] == 0) {
            continue;
        }
        resStr[index++] = res[i] + '0';  // 数字转字符
    }
    // 特殊情况：全零（如0×123），手动补一个0
    if (index == 0) {
        resStr[index++] = '0';
    }
    resStr[index] = '\0';  // 字符串结束符

    // 4. 释放临时内存
    free(res);

    return resStr;
}

/**
 * 核心函数：大整数除法（整除）
 * 功能：计算两个非负大整数的商，余数通过指针返回
 * 原理：模拟手工长除法，从高位到低位逐位截取被除数，循环减除数求商
 * 参数：a - 被除数（字符串）；b - 除数（字符串）；remainder - 输出余数的指针
 * 返回：商的字符串（需要手动free释放内存）；除数为0时返回NULL
 */
char* bigDiv(char *a, char *b, char **remainder) {
    // 1. 边界判断：除数不能为0
    if (strcmp(b, "0") == 0) {
        printf("除数不能为0\n");
        return NULL;
    }

    // 2. 被除数 < 除数，商为0，余数=被除数
    int cmp = compare(a, b);
    if (cmp < 0) {
        *remainder = strdup(a);  // 复制被除数作为余数
        return "0";
    }

    int lenA = strlen(a);
    // 3. 分配内存：商的最大长度=被除数的长度；当前余数的最大长度=被除数的长度
    char *quotient = (char*)malloc(lenA + 1);  // 存储商
    char *currRem = (char*)malloc(lenA + 1);   // 存储当前余数
    int qIndex = 0;    // 商的指针
    int remIndex = 0;  // 当前余数的指针

    // 4. 逐位处理被除数，模拟长除法
    for (int i = 0; i < lenA; i++) {
        // 4.1 截取被除数的当前位，拼接到余数后
        currRem[remIndex++] = a[i];
        currRem[remIndex] = '\0';  // 补充结束符
        // 4.2 去掉余数的前导零（避免"0012"这种格式影响比较）
        currRem = removeLeadingZeros(currRem);
        remIndex = strlen(currRem);  // 更新余数长度

        // 4.3 循环减除数，统计减的次数（即商的当前位）
        int qDigit = 0;
        while (compare(currRem, b) >= 0) {
            char *temp = bigSub(currRem, b);  // 余数 = 余数 - 除数
            free(currRem);                    // 释放旧余数内存
            currRem = temp;                   // 更新余数
            qDigit++;                         // 商的当前位+1
        }

        // 4.4 存储商的当前位（数字转字符）
        quotient[qIndex++] = qDigit + '0';
    }
    quotient[qIndex] = '\0';  // 商的结束符

    // 5. 处理最终结果：去掉商的前导零，余数赋值给输出指针
    char *finalQuotient = removeLeadingZeros(quotient);
    *remainder = currRem;  // 最终余数通过指针返回

    // 6. 释放临时内存
    free(quotient);

    return finalQuotient;
}

/**
 * 主函数：输入两个大整数，测试四则运算
 * 功能：从控制台读取两个大整数，执行加减乘除并输出结果
 * 注意：
 * 1. 输入缓冲区设为1000字节，支持超长位数（可根据需要调整）
 * 2. 处理fgets读取的换行符，避免影响后续运算
 * 3. 所有动态分配的字符串仍需手动free，避免内存泄漏
 */
int main() {
    // 1. 定义足够大的字符数组存储输入（支持最长999位的大整数）
    char a[1000];
    char b[1000];

    // 2. 提示用户输入两个大整数
    printf("=== 大整数四则运算 ===\n");
    printf("请输入第一个大整数：");
    // 使用fgets读取输入（避免scanf截断空格/超长输入）
    fgets(a, sizeof(a), stdin);
    // 去除fgets读取的换行符（关键：否则字符串末尾会带\n，影响运算）
    a[strcspn(a, "\n")] = '\0';

    printf("请输入第二个大整数：");
    fgets(b, sizeof(b), stdin);
    b[strcspn(b, "\n")] = '\0';

    // 3. 验证输入（简单检查：非空）
    if (strlen(a) == 0 || strlen(b) == 0) {
        printf("错误：输入不能为空！\n");
        return 1;
    }

    // 4. 执行加法运算并输出
    char *addRes = bigAdd(a, b);
    printf("\n【加法】%s + %s = %s\n", a, b, addRes);
    free(addRes);  // 释放内存

    // 5. 执行减法运算并输出
    char *subRes = bigSub(a, b);
    printf("【减法】%s - %s = %s\n", a, b, subRes);
    free(subRes);  // 释放内存

    // 6. 执行乘法运算并输出
    char *mulRes = bigMul(a, b);
    printf("【乘法】%s * %s = %s\n", a, b, mulRes);
    free(mulRes);  // 释放内存

    // 7. 执行除法运算并输出（处理除数为0的情况）
    char *remainder;
    char *divRes = bigDiv(a, b, &remainder);
    if (divRes != NULL) {  // 除数不为0时输出
        printf("【除法】%s / %s = %s，余数：%s\n", a, b, divRes, remainder);
        free(divRes);
        free(remainder);
    }

    return 0;
}