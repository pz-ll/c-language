#include <stdio.h>

#define ROWS 5
#define COLS 5

int main() {
    int arr[ROWS][COLS];
    int row_totals[ROWS] = {0};
    int col_totals[COLS] = {0};

    // 输入5×5数组
    for (int i = 0; i < ROWS; i++) {
        printf("Enter row %d: ", i + 1);
        for (int j = 0; j < COLS; j++) {
            scanf("%d", &arr[i][j]);
            row_totals[i] += arr[i][j];  // 计算行和
            col_totals[j] += arr[i][j];  // 计算列和
        }
    }

    // 输出行和
    printf("\nRow totals: ");
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", row_totals[i]);
    }
    // 输出列和
    printf("\nColumn totals: ");
    for (int j = 0; j < COLS; j++) {
        printf("%d ", col_totals[j]);
    }
    printf("\n");

    return 0;
}