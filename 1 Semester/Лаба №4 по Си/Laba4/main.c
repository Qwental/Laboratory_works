#include <stdio.h>
#include <stdlib.h>
int max(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int min(int a, int b) {
    if (a >= b) {
        return b;
    } else {
        return a;
    }
}

int absolute(int a) {
    if (a >= 0) {
        return a;
    } else {
        return -a;
    }
}


int main() {
    system("cls");
    system("chcp 65001");
    system("cls");
    const int i0 = -10, j0 = -10, l0 = 6, a = 10, b = 5, x = 20, y = 0;
    int i = i0, j = j0, l = l0, i_new, j_new, l_new, k = 1, flag = 0;
    for (k; k <= 50; k++) {
        i_new = absolute(max(min(i + j, i + l) % 30, max(i + l, j + k) % 25));
        j_new = absolute(i + k) % 10 + absolute(j + k) % 10 + absolute(l + k) % 10;
        l_new = (i * i * i + j * j * j + l * l * l - k) % 35;
        i = i_new;
        j = j_new;
        l = l_new;
        printf("%s%d %s%d %s%d %s%d\n","k=", k, " i=", i, " j=", j, " l=", l);
        if (((float)((i-x)*(i-x))/(float)(a*a))+((float)((j-y)*(j-y))/(float)(b*b))<=1){
            flag = 1;
            break;
        }

    }

    if (flag > 0) {
        printf("%s\n","Попадание в эллипс не более чем за 50 шагов");
        printf("%s%d\n","Время окончания = ",k);
        printf("%s%d%s%d%s\n","Конечные координаты точки: (",i,",",j,")");
        printf("%s%d\n","Значение динамического параметра движения = ",l);
    }
    else {
        printf("%s\n","Промах");
        printf("%s%d\n", "Время окончания = ",k);
        printf("%s%d%s%d%s\n","Конечные координаты точки: (",i,",",j,")");
        printf("%s%d\n","Значение динамического параметра движения = ",l);
    }

    return 0;
}
