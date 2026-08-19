#include <stdio.h>

int main(int argc, char const *argv[])
{
    int m[9][9] = {0};
    int c = 0;
    // for (int i = 0; i < 9; i++)
    // {
    //     m[i][0]=1;
    //     for (int j = 0; j < 9; j++)
    //     {
    //         if(i>=2) {m[i][j]=m[i-1][j-1]+m[i-1][j];c++;}
    //         if(i==j) {m[i][j]=1;printf("%d\t",m[i][j]);break;}
    //         printf("%d\t",m[i][j]);
    //     }
    //     printf("\n");
    // }
    for (int i = 0; i < 9; i++)
    {
        m[i][0] = 1;
        m[i][i] = 1;
        for (int j = 0; j < 9; j++)
        {
            if (i >= 2 && i > j)
            {
                m[i][j] = m[i - 1][j - 1] + m[i - 1][j];
                c++;
            }
            if (m[i][j] != 0)
                printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
    printf("%d", c);
    return 0;
}
