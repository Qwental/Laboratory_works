#include <stdlib.h>
#include <stdbool.h>

#include "symbol.h"
#include "stack.h"

#define MINSIZE 4

STACK *stack_create() {
    STACK *stack = (STACK*)malloc(sizeof(STACK));
    stack->cap = MINSIZE;
    stack->size = 0;
    stack->body = (symbol*)malloc(sizeof(symbol) * stack->cap);
    return stack;
}

STACK *stack_copy(STACK *original) {
    // Создаем новый стек
    STACK *copy = stack_create();

    // Копируем элементы из исходного стека в новый
    for (int i = 0; i < original->size; i++) {
        stack_push(copy, original->body[i]);
    }

    // Возвращаем копию стека
    return copy;
}

void stack_delete(STACK *stack) {
    // free(stack->body);
    // free(stack);
    FREE_AND_NULL(stack);

}
bool stack_empty(STACK *stack) {
    return stack->size == 0;
}

void stack_push(STACK *stack, symbol t) {
    if(stack->size <= stack->cap) {
        stack->cap *= 2;
        stack->body = (symbol*)realloc(stack->body, sizeof(symbol) * stack->cap);
    }

    stack->body[stack->size] = t;
    stack->size++;
}

symbol stack_pop(STACK *stack) {
    symbol res = stack->body[stack->size - 1];
    stack->size--;

    if(stack->size * 2 < stack->cap && stack->cap > MINSIZE) {
        stack->cap /= 2;
        stack->body = (symbol*)realloc(stack->body, sizeof(symbol) * stack->cap);
    }

    return res;
}

symbol stack_peek(STACK *stack) {
    return stack->body[stack->size - 1];
}

