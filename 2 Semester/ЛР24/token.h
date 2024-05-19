#ifndef __token_h__
#define __token_h__


typedef enum _OP_ASSOC {
    ASSOC_LEFT, ASSOC_RIGHT
} OP_ASSOC;


// максимальная длина имени переменной
#define VARNAME_LEN 10

typedef enum _TOK_TYPE {
    TOK_NONE,    // не лексема
    TOK_NUMBER,  // число
    TOK_VAR,     // переменная
    TOK_OP,      // оператор
    TOK_LEFT_BR, // открывающая скобка
    TOK_RIGHT_BR // закрывающая скобка
} TOK_TYPE;

typedef enum _OP {
    OP_MINUS = '-',
    OP_PLUS = '+',
    OP_MULT = '*',
    OP_DIVIDE = '/',
    OP_POW = '^',
    OP_UNARY_MINUS = '!' // а тут что угодно может быть, главное, чтобы с простым минусом не путать
} OP;

typedef struct {
    TOK_TYPE type;
    union {
        float number;          // если лексема - число
        char var[VARNAME_LEN]; // если лексема - переменная
        OP op;                 // если лексема - операция
        char c;                // на случай ошибок, здесь будет считанный непонятный char
    } data;
} TOKEN;

#endif