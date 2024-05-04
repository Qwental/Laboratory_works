#include "queue.h"
#include <stdio.h>

void Create(queue *q) {
    q->first = 0;
    q->size = 0;
}

bool Empty(queue *q) {
    return q->size == 0;
}

int Size(queue *q) {
    return q->size;
}

bool Push(queue *q, const data_type t) {
    if (q->size == POOL_SIZE)
        return false;
    q->data[(q->first + q->size++) % POOL_SIZE] = t;
    return true;
}

bool Pop(queue *q) {
    if (!q->size)
        return false;
    q->first++;
    q->first %= POOL_SIZE;
    q->size--;
    return true;
}

data_type Top(const queue *q) {
    if (q->size)
        return q->data[q->first];
}

void Print(queue *q) {
    queue cur = *q;
    putchar('[');
    while (!Empty(&cur)) {
        printf(" %d:%d", Top(&cur).key, Top(&cur).value);
        Pop(&cur);
    }
    puts(" ]");
}

void Destroy(queue *q) {
    q->size = 0;
}
