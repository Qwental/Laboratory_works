#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 300

typedef struct {
    int number;
    char description[MAX_LINE_LENGTH];
} HashMap;


HashMap *readFromFile(const char *filename, int *count) {
    FILE *file = fopen(filename, "r"); // Открываем файл для чтения
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return NULL;
    }

    // Считаем количество строк в файле
    *count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            (*count)++;
        }
    }
    rewind(file); // Возвращаем указатель в начало файла

    // Выделяем память под массив структур
    HashMap *data = (HashMap *) malloc((*count) * sizeof(HashMap));
    if (data == NULL) {
        perror("Ошибка выделения памяти");
        fclose(file);
        return NULL;
    }

    // Считываем данные из файла в структуру
    for (int i = 0; i < *count; ++i) {
        if (fscanf(file, "%d %[^\n]", &data[i].number, data[i].description) != 2) {
            perror("Ошибка чтения данных из файла");
            fclose(file);
            free(data);
            return NULL;
        }
    }

    fclose(file); // Закрываем файл
    return data;
}

void print_HashMap(HashMap *table, int count) {
    printf("------------------------------------------------------------------\n");
    printf("Ключ| Значение\n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < count; ++i) {
        printf("%d | %s\n", table[i].number, table[i].description);
    }
    printf("------------------------------------------------------------------\n");
}


void shekerSort(HashMap *mass, int count) {
    int left = 0, right = count - 1; // левая и правая границы сортируемой области массива
    int flag = 1;  // флаг наличия перемещений
    // Выполнение цикла пока левая граница не сомкнётся с правой
    // и пока в массиве имеются перемещения
    while ((left < right) && flag > 0) {
        flag = 0;
        for (int i = left; i < right; i++)  //двигаемся слева направо
        {
            if (mass[i].number > mass[i + 1].number) // если следующий элемент меньше текущего,
            {             // меняем их местами
                HashMap t = mass[i];
                mass[i] = mass[i + 1];
                mass[i + 1] = t;
                flag = 1;      // перемещения в этом цикле были
            }
        }
        right--; // сдвигаем правую границу на предыдущий элемент
        for (int i = right; i > left; i--)  //двигаемся справа налево
        {
            if (mass[i - 1].number > mass[i].number) // если предыдущий элемент больше текущего,
            {            // меняем их местами
                HashMap t = mass[i];
                mass[i] = mass[i - 1];
                mass[i - 1] = t;
                flag = 1;    // перемещения в этом цикле были
            }
        }
        left++; // сдвигаем левую границу на следующий элемент
        if (flag == 0) break;
    }
    printf("Отсортировано методом Шейкер-сортировка \n");

}


int isSorted(HashMap *array, int n) {
    for (int i = 1; i < n; ++i) {
        if (array[i].number < array[i - 1].number) {
            return 0; // Если обнаружен неправильный порядок, возвращаем 0
        }
    }
    return 1; // Если таблица отсортирована по возрастанию, возвращаем 1
}

int isreSorted(HashMap *array, int n) {
    for (int i = 1; i < n; ++i) {
        if (array[i].number > array[i - 1].number) {
            return 0;
        }
    }
    return 1;
}

int binarySearch(HashMap *array, int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Если ключ найден, возвращаем индекс элемента
        if (array[mid].number == key) {
            return mid;
        }

        // Если ключ меньше, чем средний элемент, ищем в левой половине
        if (array[mid].number > key) {
            right = mid - 1;
        }
            // Иначе ищем в правой половине
        else {
            left = mid + 1;
        }
    }

    // Если ключ не найден, возвращаем -1
    return -1;
}

void reverseHashMap(HashMap *array, int n) {
    int left = 0;
    int right = n - 1;

    while (left < right) {
        // Обмен значениями между левым и правым элементами
        HashMap temp = array[left];
        array[left] = array[right];
        array[right] = temp;

        // Сдвигаем указатели внутрь массива
        left++;
        right--;
    }
}


void menu() {
    printf("\n------------------------------------------------------------------\n");
    printf("█ 1) Распечатать таблицу\n");
    printf("█ 2) Найти по ключу\n");
    printf("█ 3) Отсортировать или проверить, отсортирована ли таблица\n");
    printf("█ 4) Реверс таблицы\n");
    printf("█ 0) Выйти\n");
    printf("------------------------------------------------------------------\n");
    printf("▷▷▷ ");
}

int main() {

    printf("Введите имя файла для работы программы:\n");
    char str[30];
    scanf("%s", str);
    const char *filename = str;
    int count; //количество переменных
    HashMap *data = readFromFile(filename, &count); // Читаем данные из файла в структуру
    char c;
    menu();
    printf("\n");
    scanf("%c", &c);
    while (c != '0') {
        switch (c) {
            case '1':
                print_HashMap(data, count);
                break;
            case '2':
                printf("Введите ключ:\n");
                int k;
                scanf("%d", &k);
                int result = binarySearch(data, count, k);
                if (result != -1) printf("\n%s\n", data[result].description);
                else printf("Нет такого ключа!\n");
                break;
            case '3':
                if (isSorted(data, count)) { printf("Уже отсортировано\n"); }
                else if (isreSorted(data, count)) {
                    reverseHashMap(data, count);
                    printf("Реверс!\n");
                } else {
                    shekerSort(data, count);
                }
                break;
            case '4':
                reverseHashMap(data, count);
                break;
            case '0':
                c = '0';
                printf("Конец работы программы\n");
                break;
            default:
                printf("Нет такого действия\n");
                break;
        }
        menu();
        scanf("\n%c", &c);
    }


    return 0;
}
