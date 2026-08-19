#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char *m[] = {"零", "壹", "貳", "叁", "肆", "伍", "陆",
                 "柒", "捌", "玖"};
    char *r[] = {"千", "万", "十", "百"};
    // char *r[] = {"万", "千", "百", "十"};
    char n[16];
    printf("输入数字:");
    fgets(n, 15, stdin);
    int len = strlen(n) - 1;
    int q = len;
    for (int i = 0; i < len; i++)
    {
        int w = n[i] - '0';
        int j = q % 4;
        //printf("%s", m[w]);
        if (w == 0 && n[i-1] != '0') {}
        else
            printf("%s", m[w]);
            
        if ((q - 1 && w != 0) || j==1)
        {
            printf("%s", r[j]);
        }
        q--;
    }
    printf("rmb\n");
    return 0;
}
