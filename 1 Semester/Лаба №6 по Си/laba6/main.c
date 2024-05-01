#include <stdio.h>
#include <stdbool.h>
#include <wctype.h>
#include <ctype.h>

int main() {
    char previous_char = ' ', current_char, input_char;
    bool flag = true, there_was_divisor_before = false, there_was_digit = false;
    int status = 0, counter = 0, temp = 0;

    while (status != 4) {

        input_char = getchar();

        if (input_char == '\n' || input_char == '\t' || input_char == ',' || input_char == ' '
            || input_char == '+' || input_char == '-' || input_char == '=' || input_char == '/' || input_char == '.'
            || input_char == '*' || input_char == '(' || input_char == ')' || input_char == ';' || input_char == '`') {
            status = 1;
            current_char = input_char;
        }
        else {
            input_char = tolower(input_char);
            if (previous_char == '\n' || previous_char == '\t' || previous_char == ',' || previous_char == ' '
                || previous_char == '+' || previous_char == '-' || previous_char == '=' || previous_char == '/' || previous_char == '.'
                || previous_char == '*' || previous_char == '(' || previous_char == ')' || previous_char == ';' || previous_char == '`') {
                flag = true;
            }

        }

        if (iswdigit(input_char)) {
            there_was_digit = true;
            flag = false;
        }

        if (status == 1) {

            if (there_was_divisor_before == true) {
                status = 0;
                continue;
            }

            if (flag == true) {
                if (previous_char == '\n' || previous_char == '\t' || previous_char == ',' || previous_char == ' '
                    || previous_char == '+' || previous_char == '-' || previous_char == '=' || previous_char == '/' || previous_char == '.'
                    || previous_char == '*' || previous_char == '(' || previous_char == ')' || previous_char == ';' || previous_char == '`'){
                    there_was_divisor_before = true;
                    previous_char = current_char;
                    status = 0;
                    continue;
                }
                counter++;
            }

            there_was_divisor_before = true;
            status = 0;
            previous_char = current_char;
            continue;

        }

        if (input_char == EOF) {
            printf("\n%d\n", counter);

            status = 4;
            continue;
        }

        if (status == 2) {
            current_char = input_char;
            there_was_divisor_before = false;

            if (current_char <= previous_char) {
                flag = false;
            }

            status = 3;

            previous_char = current_char;
            continue;
        }

        if (status == 3) {
            current_char = input_char;

            if (current_char <= previous_char) {
                flag = false;
            }
            status = 2;
            previous_char = current_char;
            continue;
        }

        if (status == 0) {
            previous_char = input_char;
            status = 2;
            continue;
        }



    }


    return 0;
}
