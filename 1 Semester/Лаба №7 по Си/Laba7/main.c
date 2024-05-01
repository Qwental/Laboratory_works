#include <stdio.h>
#include <ctype.h>

//множество coгласных букв
#define CONSONANTS (1u << ('b' - 'a') | 1u << ('c' - 'a') | 1u << ('d' - 'a') | 1u << ('f' - 'a') | 1u << ('g' - 'a') |1u << ('h' - 'a') | 1u << ('j' -'a') | 1u << ('k' - 'a') | 1u << ('l' - 'a') | 1u << ('m' - 'a') |1u << ('n' - 'a') | 1u << ('p' - 'a') | 1u << ('q' - 'a') | 1u << ('r' - 'a') | 1u << ('s' -'a') |1u << ('t' - 'a') | 1u << ('v' - 'a') | 1u << ('w' - 'a') | 1u << ('x' - 'a') | 1u << ('z' - 'a'))


unsigned int char_to_set(char c) {
    c = tolower(c); //для упрощения кода не будем учитывать регистр
    if (c < 'a' || c > 'z') {
        return 0; // если это не буква, то 0
    } else {
        return 1u << (c - 'a');
    }
}

int main() {
    int c, flag = 0;
    unsigned int word_consonants_set = 0;
    unsigned int temp_consonants;
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == '\t' || c == ',' || c == ' '
            || c == '+' || c == '-' || c == '=' || c == '/' || c == '.'
            || c == '*' || c == '(' || c == ')' || c == ';' || c == '`') {
            word_consonants_set = 0;
            continue;
        }
        if ((char_to_set(c) & CONSONANTS) != 0) { // работаем только с согласными
            if (word_consonants_set == 0) {
                word_consonants_set = word_consonants_set | char_to_set(c);
            } else {
                temp_consonants = word_consonants_set;
                word_consonants_set = word_consonants_set | char_to_set(c);
                if (temp_consonants == word_consonants_set) {
                    flag = 1;
                }
            }
        }
    }
    if (flag == 1) {
        printf("\nНашлось слово, в котором хотя бы одна согласная повторяется!\n");
    } else {
        printf("\nНЕ нашлось слово, в котором хотя бы одна согласная повторяется!\n");
    }
    return 0;
}
