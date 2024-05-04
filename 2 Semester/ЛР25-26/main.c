#include <stdio.h>
#include <stdbool.h>
#include "queue.c"
#include "qsort.c"

void menu() {
    puts("---------------------------------------------");
    puts("█ 1) Добавить элемент в очередь.");
    puts("█ 2) Удаление первого элемента в очереди.");
    puts("█ 3) Размер очереди.");
    puts("█ 4) Удаление минимального элемента.");
    puts("█ 5) Печать очереди.");
    puts("█ 6) Сортировка очереди.");
    puts("█ 0) Выход.");
    puts("---------------------------------------------");
    printf("▷▷▷ ");
}

int main() {
    queue q;
    data_type t;
    Create(&q);
    char c;
    menu();
    scanf("%c", &c);
    while (c != '0') {
        switch (c) {
            case '1':
                printf("Введите элемент(ключ - значение):\n▷▷▷ ");
                scanf("%d - %d", &t.key, &t.value);
                Push(&q, t);
                break;

            case '2':
                if (!Empty(&q)) {
                    printf("Элемент <%d - %d> удалён.\n", Top(&q).key, Top(&q).value);
                    Pop(&q);
                } else {
                    puts("Очередь пуста!");
                }
                break;

            case '3':
                printf("Размер очереди: %d", Size(&q));
                break;

            case '4':
                q = min_pop(&q);
                puts("Минимальный элемент был удален");
                break;

            case '5':
                Print(&q);
                break;

            case '6':
                q = qsort(&q);
                puts("Очередь отсортирована!");
                break;

            default:
                puts("Неизвестное значение!");
                break;
        }
        menu();
        scanf("\n%c", &c);
    }
    Destroy(&q);
    puts("Программа завершена!");
}
