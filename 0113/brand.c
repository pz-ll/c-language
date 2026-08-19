// brand.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct time
// {
//     int year;
//     int month;
//     int day;
// } time;

typedef struct product
{
    char neme[16];
    int price;
    brand *Brand;
    // struct brand *Brand;
} product;

typedef struct brand
{
    char neme[16];
    char cretime[20];
    product *products[10];
    int counts;
    // product Product;
} brand;

int main(int argc, char const *argv[])
{
    brand p1 = {"小米", "2010-1-16", .counts = 0};

    product s1 = {"手机", 1000};
    p1.products[p1.counts++] = &s1;
    product s2 = {"小车", 100000};
    p1.products[p1.counts++] = &s2;

    printf("品牌名称：%s\n", p1.neme);
    printf("创建时间：%s\n", p1.cretime);
    printf("旗下产品：\n");

    for (int i = 0; i < p1.counts; i++)
    {
        printf("- %s ￥%.2d\n", p1.products[i]->neme, p1.products[i]->price);
    }

    // s1.Brand = &p1;
    // printf("产品:%s\n价格:%d\n品牌:%s\n创建时间:%s\n",
    //        s1.neme, s1.price, s1.Brand->neme,
    //        s1.Brand->cretime
    //        );
    return 0;
}
