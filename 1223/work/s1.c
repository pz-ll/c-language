#include <stdio.h>
#define D fibonacci_recursion(n - 1) + fibonacci_recursion(n - 2)

int fibonacci(int n)
{

    if (n < 0)
    {
        printf("错误:n不能为负数\n");
        return -1; // 返回-1表示错误
    }
    int a = 0;
    int b = 1;
    int next;
    int sum = 0;
    if (n == 1)
    {
        sum += a;
        next = 0;
    }
    if (n == 2)
    {
        sum += b;
        next = 1;
    }
    for (int i = 3; i <= n; i++)
    {

        if (i == 3)
            sum = 1;
        next = a + b;
        sum += next;
        a = b;
        b = next;
    }
    printf("第%d项为%d,前%d项和为%d", n, next, n, sum);
    
}


int fibonacci_recursion(int n) {
    // 边界条件（递归终止条件）
    if (n < 0) {
        printf("错误:n不能为负数!\n");
        return -1;
    }
    int sum=0;
    if (n == 0) return 0;sum+=0;
    if (n == 1) return 1;sum+=1;
    // 递归调用：F(n) = F(n-1) + F(n-2)
    return D;
    int next=D;
    sum+=D;
}

int main(int argc, char const *argv[])
{
    int n;
    printf("请输入要计算的斐波那契数列项数n:");
    scanf("%d", &n);

    fibonacci(n);
    
    return 0;
}
