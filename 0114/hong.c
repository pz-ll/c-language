// 宏.c

#include <stdio.h>
#include <stdbool.h>
#include "my.h"

#define PI 3.1415926535897932384626433832795
#define C(r) 2 * PI *r
#define ADD(a, b) a + b
#define MUL(a, b) (a) * (b)
//参数无类型:解决函数不能重载的问题
#define MAX(a, b) (a) > (b) ? (a) : (b)         //()是防止因‘优先级问题’出错
// # 转字符串
//#define STR(a) #a         //直接使用时不会先展开参数中的宏，而通过嵌套宏调用时会先展开参数宏，再字符串化。
#define TO_STR(x) #x
#define STR(x) TO_STR(x)
//## 拼接字符串
#define CAT(a,b) a##b

double c(int r)
{
    return 2 * r * PI;
}


int main(int argc, char const *argv[])
{

    printf("%d\n",my_max(3,2));

    // int a=2,b=3;
    // printf("%d+%d=%d\n",a,b,a+b);
    // printf("%s=%d\n",STR(a+b),a+b);
    // printf("%s\n",STR(PI));
    
    // int num1 = 100;
    // int num2 = 200;
    // int num3 = 300;
    // printf("%d\n",CAT(num,1));
    // printf("%d\n",CAT(num,2));
    // printf("%d\n",CAT(num,3));

    // int r = 5;
    // printf("%lf\n", 2 * PI * r); // 表达式
    // printf("%lf\n", C((r + 1))); // 宏
    // printf("%lf\n", c(r + 1));   // 函数
    // int n = ADD(2, 3);
    // int m = MUL(3, 5);
    // printf("%d\n", m);
    // printf("%d\n", MUL(2 + 1, 3 + 2));
    // printf("%d\n",MAX(2,3));
    // printf("%c\n",MAX('a','A'));
    // printf("%f\n",MAX(22.12,3.145));
    
    return 0;
}
