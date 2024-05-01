#include <stdio.h>
#include <stdlib.h>

int len(int a) {
    int l = 0;
    while (a > 0) {
        l++;
        a = a / 10;
    }
    return l;
}


int pow(int x, int a) {
    int result = x;
    if (x == 0) {
        return 0;
    } else {
        for (int i = 1; i < a; i++) {
            result = result * x;
        }
        return result;
    }
}

int main() {
    system("cls");
    system("chcp 65001");
    system("cls");
    int a, l, ans, a_copy, l_copy, left_part, right_part, sred, k;

    printf("Введите число: \t");
    scanf("%d", &a);
    if (a > 0) {
        l = len(a);
        a_copy = a;
        l_copy = len(a_copy);
        if (l % 2 != 0) {
            sred = (int) l / 2 + 1; // индекс средней цифры
            ans = a % (pow(10, sred - 1)); // часть числа до средней цифры

            for (int i = 0; i < (int) l / 2; i++) {
                a_copy = a % pow(10, len(a) - i);
                ans += (int) (a_copy / (pow(10, len(a_copy) - 1))) * pow(10, len(a_copy) - 2);

            }
            printf("Результат выполнения программы: ");
            printf("%d\n", ans);

        } else {
            sred = (int) l / 2 + 1; // индекс средней цифры
            ans = a % (pow(10, sred - 1)); // часть числа до средней цифры
            for (int i = 0; i < (int) l / 2 - 1; i++) {
                a_copy = a % pow(10, len(a) - i);
                ans += (int) (a_copy / (pow(10, len(a_copy) - 1))) * pow(10, len(a_copy) - 2);

            }
            printf("Результат выполнения программы: ");
            printf("%d\n", ans);

        }
    } else if (a == 0) {
        ans = 0;
        printf("Результат выполнения программы: ");
        printf("%d\n", ans);

    } else if (a < 0) {
        a = -a;
        l = len(a);
        a_copy = a;
        l_copy = len(a_copy);
        if (l % 2 != 0) {
            sred = (int) l / 2 + 1; // индекс средней цифры
            ans = a % (pow(10, sred - 1)); // часть числа до средней цифры

            for (int i = 0; i < (int) l / 2; i++) {
                a_copy = a % pow(10, len(a) - i);
                ans += (int) (a_copy / (pow(10, len(a_copy) - 1))) * pow(10, len(a_copy) - 2);

            }
            printf("Результат выполнения программы: ");
            printf("%d\n", -ans);

        } else {
            sred = (int) l / 2 + 1; // индекс средней цифры
            ans = a % (pow(10, sred - 1)); // часть числа до средней цифры
            for (int i = 0; i < (int) l / 2 - 1; i++) {
                a_copy = a % pow(10, len(a) - i);
                ans += (int) (a_copy / (pow(10, len(a_copy) - 1))) * pow(10, len(a_copy) - 2);
            }
            printf("Результат выполнения программы: ");
            printf("%d\n", -ans);

        }
    }
    return 0;
}
