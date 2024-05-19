//
// Created by Qwental on 08.05.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char s[100];
    struct Item *next;
} Item;

typedef struct {
    Item *head;
    int size;
    Item *terminator;
} List;

typedef struct Iterator {
    Item *node;
} Iterator;

int equal(Iterator *lhs, Iterator *rhs) {
    return lhs->node == rhs->node;
}

int not_equal(Iterator *lhs, Iterator *rhs) {
    return !equal(lhs, rhs);
}

Iterator *next(Iterator *i, List *l) {
    if (i->node != l->terminator)
        i->node = i->node->next;
    return i;
}

Iterator first(List *l) {
    Iterator res = {l->head};
    return res;
}

Iterator last(List *l) {
    Iterator res = {l->terminator};
    return res;
}

char *fetch(Iterator *i) {
    return i->node->s;
}

void store(Iterator *i, char *str) {
    strcpy(i->node->s, str);
}

void create(List *l) {
    l->head = (Item *) malloc(sizeof(Item));
    l->terminator = l->head->next = (Item *) malloc(sizeof(Item));
    l->size = 0;
}

void insert(List *l, char *str, int n) {
    if (n <= 0) {
        return;
    }
    if (l->size == 0) {
        strcpy(l->head->s, str);
    } else {
        Iterator elem = first(l);
        for (int i = 0; i < (n - 2); i++) {
            next(&elem, l);
        }
        Iterator temp = {elem.node->next};
        elem.node->next = (Item *) malloc(sizeof(Item));
        next(&elem, l);
        store(&elem, str);
        elem.node->next = temp.node;
    }
    (l->size)++;
}

void print_list(List *l) {
    if (!l->size) {
        printf("Список пуст!\n");
    } else {
        printf("Вывод списка:\n[ ");
        Iterator elem = first(l);
        Iterator barier = last(l);
        do {
            printf("%s ", fetch(&elem));
            next(&elem, l);
        } while (not_equal(&elem, &barier));
        puts("]");
    }
}

int size_list(List *l) {
    return l->size;
}

void del_elem(List *l, char *str) {
    if (!l->size) {
        puts("Список пуст!");
        return;
    }
    Item **elem = &(l->head);
    while ((*elem) != l->terminator) {
        if (!strcmp((*elem)->s, str)) {
            Item *next = (*elem)->next;
            free(*elem);
            *elem = next;
            (l->size)--;
            puts("Элемент удалён");
            return;
        }
        elem = &((*elem)->next);
    }
    puts("Элемент не найден!");
}

void del_elem_n(List *l, int n) {
    if (n >= l->size || n < 0) {
        puts("Элемента с указанным индексом не существует!");
        return;
    }
    Item **elem = &(l->head);
    for (int i = 0; i < n; i++) {
        elem = &((*elem)->next);
    }
    Item *next = (*elem)->next;
    free(*elem);
    *elem = next;
    (l->size)--;
    puts("Элемент удалён");
    return;
}

void del_elem_without(List *l, char *str) {
    Iterator elem = first(l);
    Iterator barier = last(l);
    int k = 0;
    while (not_equal(&elem, &barier)) {
        Iterator next = {elem.node->next};
        if (strcmp(fetch(&elem), str) == 0) {
            k = 1;
        }
        elem = next;
    }
    if (!k) {
        puts("Элемента с заданным значением не существует!");
    } else {
        Iterator elem = first(l);
        Iterator barier = last(l);
        while (not_equal(&elem, &barier)) {
            Iterator next = {elem.node->next};
            if (strcmp(fetch(&elem), str) != 0) {
                del_elem(l, fetch(&elem));
            }
            elem = next;
        }
        printf("Все элементы, кроме <%s> удалены\n", str);
    }
}

void destroy(List *l) {
    Iterator cur = first(l);
    Iterator barier = last(l);
    while (not_equal(&cur, &barier)) {
        Iterator nexts = {cur.node->next};
        free(cur.node);
        cur = nexts;
    }
    free(barier.node);
    l->head = NULL;
    l->terminator = NULL;
    l->size = 0;
}

void menu() {
    puts("-----------------------");
    puts("1) Печать списка.");
    puts("2) Вставка нового элемента в список.");
    puts("3) Удаление элемента из списка.");
    puts("4) Подсчет длины списка.");
    puts("5) Удалить из списка все элементы, кроме заданного.");
    puts("0) Выход.");
    puts("-----------------------");
    printf(">>> ");
}

int main() {
    List list;
    create(&list);
    char c;
    char str[100];
    int n;
    menu();
    scanf("%c", &c);
    while (c != '0') {
        switch (c) {
            case '1':
                print_list(&list);
                break;

            case '2':

                printf("Введите значение:\n>>> ");
                scanf("%s", &str);
                printf("Введите по какому индексу выполнить вставку:\n>>> ");
                scanf("%d", &n);
                insert(&list, str, n);
                break;

            case '3':
                printf("Введите номер элемента:\n>>> ");
                scanf("%d", &n);
                del_elem_n(&list, n);
                break;

            case '4':
                printf("%d\n", size_list(&list));
                break;

            case '5':
                printf("Введите значение:\n>>> ");
                scanf("%s", &str);
                del_elem_without(&list, str);
                break;

            default:
                puts("Неизвестное значение!");
                break;
        }
        menu();
        scanf("\n%c", &c);
    }
    destroy(&list);
    puts("Программа завершена!");
}
