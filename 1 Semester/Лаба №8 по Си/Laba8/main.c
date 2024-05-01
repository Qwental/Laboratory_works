#include <stdio.h>

int main() {
    int n;
    int temp_k, temp_i, temp_j;
    int array[7][7];
    int new_array[7][7];
    printf("Введите порядок квадратной матрицы: ");
    scanf("%d\n", &n);
    if (n > 7) {
        printf("Ошибка, по условию задачи порядок матрицы не больше семи!\n");
        return 0;
    }
    for (int i = 0; i != n; ++i)
        for (int j = 0; j != n; ++j)
            scanf("%d", &array[i][j]);
    printf("\nПолучившаяся матрица в виде строки: \n");
    for (int k = 0; k != 2 * n - 1; ++k) {
        if (k < n) {
            if (k == 0) {
                printf("%d ", array[0][0]);

                continue;
            }
            temp_i = k;
            temp_j = 0;
            for (int repeat = 0; repeat != k + 1; ++repeat) {
                printf("%d ", array[temp_i][temp_j]);
                temp_i--;
                temp_j++;
            }


        } else {
            if (k == n) {
                temp_j = 1;
            } else {
                temp_j = temp_i + 1;
            }
            temp_i = n - 1;
            if (k == 2 * n - 2) {
                printf("%d ", array[n - 1][n - 1]);
                break;

            }
            for (int repeat = 0; repeat != k; ++repeat) {
                printf("%d ", array[temp_i][temp_j]);
                temp_i--;
                temp_j++;
                if (temp_j == n - 1) {
                    printf("%d ", array[temp_i][temp_j]);
                    break;
                }
            }


        }
    }
    printf("\n");
    return 0;
}
