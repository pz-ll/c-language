#include <stdio.h>
#define D fib_recursion(n-1) + fib_recursion(n-2)

// 循环实现
long long fib_loop(int n) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long a = 0, b = 1, res = 0;
    for (int i = 2; i <= n; i++) {
        res = a + b;
        a = b;
        b = res;
    }
    return res;
}

// 递归实现
long long fib_recursion(int n) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (n == 1) return 1;
    return D;
}

int main() {
    int n;
    printf("请输入n值(计算斐波那契数列第n项):");
    scanf("%d", &n);

    long long res_loop = fib_loop(n);
    long long res_rec = fib_recursion(n);

    if (res_loop == -1) {
        printf("输入错误:n不能为负数!\n");
    } else {
        printf("循环方案结果:F(%d) = %lld\n", n, res_loop);
        printf("递归方案结果:F(%d) = %lld\n", n, res_rec);
    }

    return 0;
}