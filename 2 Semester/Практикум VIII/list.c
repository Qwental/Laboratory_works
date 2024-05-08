#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100


typedef struct Item {
    char s[MAX_SIZE];
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

// Проверка на равенство  по итератору.
int Equal(Iterator *lhs, Iterator *rhs) {
    return lhs->node == rhs->node;
}

// Проверка на неравенство  по итератору.
int Not_Equal(Iterator *lhs, Iterator *rhs) {
    return !Equal(lhs, rhs);
}

// Переход итератора на следующий элемент списка.
Iterator *next(Iterator *i, List *l) {
    if (i->node != l->terminator)
        i->node = i->node->next;
    return i;
}

// установить итератор на первый элемент списка.
Iterator first(List *l) {
    Iterator res = {l->head};
    return res;
}

// установить итератор на последний элемент списка.
Iterator last(List *l) {
    Iterator res = {l->terminator};
    return res;
}

// получить значение по итератору.
char *GET(Iterator *i) {
    return i->node->s;
}

// установить новое значение по итератору
void PUT(Iterator *i, char *str) {
    strcpy(i->node->s, str);
}

// создать список
void Create(List *l) {
    l->head = (Item *) malloc(sizeof(Item));
    l->terminator = l->head->next = (Item *) malloc(sizeof(Item));
    l->size = 0;
}

// вставить элемент после элемента с указанным индексом
void Insert(List *l, char *str, int n) {
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
        PUT(&elem, str);
        elem.node->next = temp.node;
    }
    (l->size)++;
}

// печать списка
void print_list(List *l) {
    if (!l->size) {
        printf("Список пуст!\n");
    } else {
        printf("Вывод списка:\n[ ");
        Iterator elem = first(l);
        Iterator barier = last(l);
        do {
            printf("%s ", GET(&elem));
            next(&elem, l);
        } while (Not_Equal(&elem, &barier));
        puts("]");
    }
}

// размер списка
int Size(List *l) {
    return l->size;
}


// удаление элемента по индексу
void remove_list_index(List *l, int n) {
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
}


// обменять значения второго и предпоследнего элемента
void swap_second_penultimate(List *l) {
    if (!l->size) {
        puts("Список пуст!");
        return;
    }

    if (l->size < 4) {
        puts("Количества элементов в списке не достаточно для выполнения процедуры");
        return;
    }
    printf("ДО\n");
    print_list(l);

    Item **elem1 = &(l->head);
    Item **copy_elem1 = &(l->head);
    Item **elem2 = &(l->head);
    // указатель на второй элемент
    elem1 = &((*elem1)->next);
    copy_elem1 = &((*copy_elem1)->next);

    //    указатель на предпоследний элемент
    for (int i = 0; i < Size(l) - 2; i++) {
        elem2 = &((*elem2)->next);
    }
    printf("Меняем элементы [%s] и [%s] местами\n", (**elem1).s, (**elem2).s);

    // Создаем копию
    char temp[MAX_SIZE];
    //Используем адресную арифметику и создаем копию второго элемента
    for (int j = 0; j < MAX_SIZE; j++) {
         temp[j] = *(&(*((**(elem1)).s)) + j);
    }
//    printf("Копия [%s] \n", temp);

    //Используем адресную арифметику
    for (int i = 0; i < MAX_SIZE; i++) {
        // обмениваем указатели значений элементов строк списка
        *(&(*((**(elem1)).s)) + i) = *(&(*((**(elem2)).s)) + i);
        *(&(*((**(elem2)).s)) + i) = temp[i];
//        print_list(l);
    }

    printf("\nПОСЛЕ \n");
    print_list(l);
}


// удаление списка
void Destroy(List *l) {
    Iterator cur = first(l);
    Iterator barier = last(l);
    while (Not_Equal(&cur, &barier)) {
        Iterator nexts = {cur.node->next};
        free(cur.node);
        cur = nexts;
    }
    free(barier.node);
    l->head = NULL;
    l->terminator = NULL;
    l->size = 0;
}

void Menu() {
    puts("-----------------------------------------------------------");
    puts("█ 1) Печать списка.");
    puts("█ 2) Вставка нового элемента в список.");
    puts("█ 3) Удаление элемента из списка.");
    puts("█ 4) Подсчет длины списка.");
    puts("█ 5) Oбменять местами 2-й и предпоследний элементы списка");
    puts("█ 0) Выход.");
    puts("-----------------------------------------------------------");
    printf("▷▷▷ ");
}

int main() {
    List list;
    Create(&list);
    char c;
    char str[100];
    int n;
    Menu();
    scanf("%c", &c);
    while (c != '0') {
        switch (c) {
            case '1':
                print_list(&list);
                break;

            case '2':
                printf("Введите значение:\n ▷▷▷ ");
                scanf("%s", str);
                printf("Введите по какому индексу выполнить вставку:\n>>> ");
                scanf("%d", &n);
                Insert(&list, str, n);
                break;

            case '3':
                printf("Введите индекс элемента, который хотите удалить:\n>>> ");
                scanf("%d", &n);
                remove_list_index(&list, n);
                break;

            case '4':
                printf("Длина = %d\n", Size(&list));
                break;

            case '5':
                swap_second_penultimate(&list);
                break;

            default:
                puts("Неизвестное значение!");
                break;
        }
        Menu();
        scanf("\n%c", &c);
    }
    Destroy(&list);
    puts("Программа завершена!");
}
