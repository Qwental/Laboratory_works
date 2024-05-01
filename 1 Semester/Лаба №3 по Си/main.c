#include <stdio.h>

int main() {

    printf("Эта программа будет вычислять площадь треугольника!\n");
    float a, b, c, r;
    double s;
    printf("Введите сторону треугольника а: ");
    scanf("%f", &a);
    printf("Введите сторону треугольника b: ");
    scanf("%f", &b);
    printf("Введите сторону треугольника c: ");
    scanf("%f", &c);
    printf("Введите радиус описанной окружности R: ");
    scanf("%f", &r);
    s = ((a * b * c) / (4 * r));
    printf("Площадь треугольника s=%f", s);
    printf("\n");
    return 0;
}
