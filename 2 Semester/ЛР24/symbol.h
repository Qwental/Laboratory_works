#ifndef __symbol_h__
#define __symbol_h__


typedef enum _OP_ASSOC {
    ASSOC_LEFT, ASSOC_RIGHT
} OP_ASSOC;


// ������������ ����� ����� ����������
#define VARNAME_LEN 10

typedef enum _symb_TYPE {
    symb_NONE,    // �� ������ �����
    symb_NUMBER,  // �����
    symb_VAR,     // ����������
    symb_OP,      // ��������
    symb_LEFT_BR, // ����������� ������
    symb_RIGHT_BR // ����������� ������
} symb_TYPE;

typedef enum _OP {
    OP_MINUS = '-',
    OP_PLUS = '+',
    OP_MULT = '*',
    OP_DIVIDE = '/',
    OP_POW = '^',
    OP_UNARY_MINUS = '!' // � ��� ��� ��� ������ ����� ����, �������, ����� � ������� ������� �� ������
} OP;

typedef struct {
    symb_TYPE type;
    union {
        float number;          // ���� ������ - �����
        char var[VARNAME_LEN]; // ���� ������ - ����������
        OP op;                 // ���� ������ - ��������
        char c;                // �� ������ ������, ����� ����� ��������� ���������� char
    } data;
} symbol;

#endif