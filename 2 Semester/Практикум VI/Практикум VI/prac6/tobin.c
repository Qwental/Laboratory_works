
#include "student.h"
//#include <string.h>
#include <stdio.h>
#include <locale.h>


int read_student(student *stud, FILE *input) {
    return (fscanf(input, "%s %s %s %d %d %d %d %d %d", stud->surname, stud->initials, stud->sex, &stud->group,
                   &stud->markfi, &stud->markakis, &stud->marklaag, &stud->markdm, &stud->markorg) == 9);
}


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    if (argc != 3) {
        printf("НЕПРАВИЛЬНЫЙ ВВОД АРГУМЕНТОВ ⚠ Правильно так:  <Имя вводимого файла> <Имя выводимого>\n");
        return 1;
    }

    student stud;

    FILE *input = fopen(argv[1], "r");
    FILE *bin = fopen(argv[2], "wb");

    if (!input) {
        perror("Не могу открыть файл ⚠");
        return 2;

    } else if (!bin) {
        perror("Не могу открыть файл ⚠");
        return 2;
    }


    while (read_student(&stud, input)) {
        fwrite(&stud, sizeof(stud), 1, bin);

    }

    printf("Бинарный файл был заполнен!\n");
    fclose(input);
    fclose(bin);
    return 0;
}
    
