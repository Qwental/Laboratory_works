#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

#define POOL_SIZE 100

typedef struct data_type {
    int key;
    int value;
} data_type;

typedef struct queue {
    int first;
    int size;
    data_type data[POOL_SIZE];
} queue;

void Create(queue *q);

bool Empty(queue *q);

int Size(queue *q);

bool Push(queue *q, const data_type t);

bool Pop(queue *q);

void Print(queue *q);

data_type Top(const queue *q);

void Destroy(queue *q);

#endif

