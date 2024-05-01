#include <stdio.h>
#include <math.h>

int main() {
    double a = -1.0, b = 1.0, EPS = 1.0, x, amount_teylor = log(2.0), teylor_term;
    int n, iterations_number = 0, k;
    while (EPS / 2.0 + 1.0 > 1.0) {
        EPS /= 2.0;
    }
    printf("Введите количество частей n, на которые разбивается интервал: ");
    scanf("%d", &n);
    printf("Введите значение k, нужное для определения точности: ");
    scanf("%d", &k);
    printf("Машинное эпсилон EPS = %.16lf.\n", EPS);
    printf("------------------------------------------------------------------\n");
    printf("|   x   | Сумма ряда Тейлора | Значение функции | Число итераций |\n");
    printf("|-------|--------------------|------------------|----------------|\n");
    for (x = a; x <= b; x += (b - a) / n) {
        while (iterations_number < 100) {
            iterations_number += 1;
            teylor_term = ((powl(-1.0, iterations_number - 1.0)) * (powl(x, iterations_number))) / (iterations_number * (powl(2.0, iterations_number)));
            if (fabs(teylor_term) > EPS * k) {
                amount_teylor += teylor_term;
            } else {
                break;
            }
        }

        if (x < 0) {
            printf("| %1.1lf  |  %1.14lf  | %1.14lf |%9d       |\n", x, amount_teylor, log(2.0 + x), iterations_number);
        } else {
            printf("|  %1.1lf  |  %1.14lf  | %1.14lf |%9d       |\n", x, amount_teylor, log(2.0 + x), iterations_number);
        }
        amount_teylor = log(2.0);
        iterations_number = 0;

    }
    printf("------------------------------------------------------------------\n");
    return 0;
}
