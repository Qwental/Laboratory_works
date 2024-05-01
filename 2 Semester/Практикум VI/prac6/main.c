#include <stdio.h>
#include <string.h>
#include "student.h"


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("НЕПРАВИЛЬНЫЙ ВВОД ⚠ Правильно так:  <Имя вводимого файла с суффиксом>\n -p (провести вычисления) ИЛИ -f (вывести базу данных)");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");

    if (input == NULL) {
        perror("Can't open file in");
        return 2;

    }

    student stud;


    if (strcmp(argv[2], "-f") == 0) {
        printf(" %-25s| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s  | %-15s |\n", "Surname",
               "Initials", "Sex", "Group", "FI", "AkiIS", "LAAG", "DM", "ORG");


        for (int n = 1; n < 170; n++) printf("-");

        printf("\n");

        while (fread(&stud, sizeof(student), 1, input) == 1) {
            printf(" %-25s| %-15s | %-15s | %-15d | %-15d | %-15d | %-15d | %-15d | %-15d |\n",
                   stud.surname, stud.initials, stud.sex, stud.group, stud.markfi, stud.markakis, stud.marklaag,
                   stud.markdm, stud.markorg);
        }


    } else if (strcmp(argv[2], "-p") == 0) {
        double minAVERAGEscore = 9999999.0;
        double Averagescore;
        int n = 0;
        int array_group[200];
        int array_averagesum[200];
        int i = 0;
        while (fread(&stud, sizeof(student), 1, input) == 1) {
            n++;
            int markfi = stud.markfi;
            int group = stud.group;
            int markakis = stud.markakis;
            int marklaag = stud.marklaag;
            int markdm = stud.markdm;
            int markorg = stud.markorg;
            if ((strcmp(stud.sex, "M")) == 0) {
                array_averagesum[i] = (int) (markfi + markakis + marklaag + markdm + markorg);
                array_group[i] = (int) (group);
            } else {
                array_averagesum[i] = 0;
                array_group[i] = 0;
            }
            Averagescore = (double) ((double) ((int) (markfi + markakis + marklaag + markdm + markorg)) / 5.0);

            if (Averagescore < minAVERAGEscore) {
                minAVERAGEscore = Averagescore;
            }
            i++;
        }
        int groupcount[15];
        for (int j = 0; j < 15; j++) groupcount[j] = 0;
        int flag = 0;
        int index;

        for (int j = 0; j < n; j++) {
            if ((array_averagesum[j] != 0) && (array_group[j] != 0)) {
                flag = 1;
                if (((double) array_averagesum[j] / 5.0) == minAVERAGEscore) {
                    if (array_group[j] == 100) index = 0;
                    else index = array_group[j] % 100;
                    groupcount[index] = groupcount[index] + 1;
                }
            }
        }
        if (flag == 0) {
            printf("%s%s", "В базе данных студентов НЕТ мужского пола, следовательно невозможно выяснить в какой группе ",
                   "учится максимальное число студентов с минимальным на курсе средним баллом\n");

            return 2;
        }


        int maxi = 0;

        for (int j = 0; j < 15; j++) {

            if (maxi <= groupcount[j]) maxi = groupcount[j];
        }


        for (int j = 0; j < 15; j++) {
            if (groupcount[j] == maxi) {
                printf("В группе %d учится максимальное число студентов с минимальным на курсе средним баллом \n",
                       j + 100);

            }
        }
        printf("Минимальный средний балл составил: %f\n", minAVERAGEscore);


    } else {
        printf("НЕПРАВИЛЬНЫЙ ВВОД АРГУМЕНТОВ, Правильно так:  <Имя вводимого бинарного файла>\n -p (для нахождения искомой группы в вводимой БД)/-f (для вывода всей базы данных)\n");
    }
    fclose(input);
    return 0;
}









