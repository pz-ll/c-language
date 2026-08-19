#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "zh_CN.UTF-8");
    wchar_t zi[] = {L'零', L'壹', L'貳', L'叁', L'肆', L'伍', L'陆', L'柒', L'捌', L'玖'};
    int n;

    wprintf(L"请输入金额");
    scanf("%d", &n);
    while (n > 0)
    {
        int b = n % 10;
        //printf("%d", b);
        wprintf(L"%lc", zi[b]);
        n /= 10;
    }

    return 0;
}
