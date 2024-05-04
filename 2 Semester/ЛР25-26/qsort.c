#include "queue.h"
#include "stdio.h"


int min_search(queue *q) {
    //    Нашли минимальный элемент
    queue cur = *q;
    int min = 2147483647;

    while (!Empty(&cur)) {
        if (min > Top(&cur).value)
            min = Top(&cur).value;
        Pop(&cur);
    }
    return min;
}


queue minimal_search(queue *q) {
    if (Empty(q))
        return *q;
    if (Size(q) == 1)
        return *q;

    int min = min_search(q);

    queue cur = *q;
    queue new_temp_que;
    Create(&new_temp_que);


    printf("До: ");
    Print(&cur);


    int flag = 0;

    while (!Empty(&cur)) {
        if ((min == Top(&cur).value) && (flag == 0)) {
            flag = 1;
        } else {
            Push(&new_temp_que, Top(&cur));
        }
        Pop(&cur);
    }
    return new_temp_que;

}

queue min_pop(queue *q) {
    if (Empty(q))
        return *q;
    if (Size(q) == 1) {
        return *q;
    }
    *q = minimal_search(q);
    printf("После: ");
    Print(q);
    return *q;
}




// линейная сортировка очереди
// ищем минимальный элемент, добавляем его во временную очередь и удаляем из оригинальной. Повторяем так пока оригинальная очередь не опустеет
queue qsort(queue *q) {
    if (Empty(q))
        return *q;
    if (Size(q) == 1) {
        return *q;
    }
    printf("ДО: ");
    Print(q);

    queue cur = *q;

    queue help_que;
    Create(&help_que);
    const int size_que = Size(&cur);

    int min_value;
    for (int i = 0; i < size_que; i++) {
        // Ищем минимальный элемент в очереди
        min_value = min_search(&cur);
        // Cоздаем временную очередь для удаления из оригинальной минимального текущего элемента
        queue temp_que;
        Create(&temp_que);

        int flag = 0;

        while (!Empty(&cur)) {
            if ((min_value == Top(&cur).value) && (flag == 0)) {
                flag = 1;
                // Добавляем min_value в вспомогательную очередь
                Push(&help_que, Top(&cur));
            } else {
                Push(&temp_que, Top(&cur));
            }
            Pop(&cur);
        }
        cur = temp_que;

    }

    printf("После: ");
    Print(&help_que);
    return help_que;

}


