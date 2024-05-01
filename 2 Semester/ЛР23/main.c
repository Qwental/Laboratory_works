#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    int elem;
    struct Node *left;
    struct Node *right;
} Node;

Node *add_knot(Node *tree, int num);

Node *delete_knot(Node *tree, int num);

Node *find_Min(Node *tree);

int SearchNode(Node *tree, int number);

void print_tree(Node *tree, int number);

void print_menu();


Node *add_knot(Node *tree, int num) {
    if (tree == NULL) {
        Node *p = malloc(sizeof(Node));
        p->elem = num;
        p->left = p->right = NULL;
        return p;
    } else if (num < tree->elem) {
        tree->left = add_knot(tree->left, num);
    } else if (num > tree->elem) {
        tree->right = add_knot(tree->right, num);
    } else {
        printf("(ㆆ_ㆆ) Элемент с таким значением уже есть, попробуйте снова с другим элементом. \n");
        return tree;
    }
    return tree;
}

void print_tree(Node *tree, int number) {
    if (tree != NULL) {
        print_tree(tree->right, number + 1);
        for (int i = 0; i < number; i++) printf("\t");
        printf("%d\n", tree->elem);
        print_tree(tree->left, number + 1);
    }
}

Node *delete_knot(Node *tree, int number) {
    if (tree == NULL) {
        return NULL;
    }

    if (number > tree->elem) {
        tree->right = delete_knot(tree->right, number);
    } else if (number < tree->elem) {
        tree->left = delete_knot(tree->left, number);
    } else {
        if (tree->left == 0 && tree->right == 0) {
            free(tree);
            return NULL;
        } else if (tree->left == 0 || tree->right == 0) {
            Node *temp;
            if (tree->left == 0) {
                temp = tree->right;
            } else {
                temp = tree->left;
            }
            free(tree);
            return temp;
        } else {
            Node *temp;
            temp = find_Min(tree->right);
            tree->elem = temp->elem;
            tree->right = delete_knot(tree->right, temp->elem);
        }
    }
    return tree;
}

void print_menu() {
    printf("\n█ Выберите действие из списка, написав его номер: \n");
    printf("█ Введите 0, чтобы выйти.\n");
    printf("█ Введите 1, чтобы добавить в дерево элемент.\n");
    printf("█ Введите 2, чтобы вывести текстовую визуализацию дерева.\n");
    printf("█ Введите 3, чтобы удалить из дерева элемент.\n");
    printf("█ Введите 4, чтобы проверить, находятся ли во всех листьях двоичного дерева элементы со значениями из заданного диапазона.\n");
}


int SearchNode(Node *tree, int number) {
    if (tree == NULL) {
        return 0;
    } else if (tree->elem == number) {
        return 1;
    } else if (tree->elem < number) {
        if (tree->right != 0) {
            return SearchNode(tree->right, number);
        } else {
            return 0;
        }
    } else if (tree->elem > number) {
        if (tree->left != 0) {
            return SearchNode(tree->left, number);
        } else {
            return 0;
        }
    }
}

Node *find_Min(Node *tree) {
    if (tree == NULL) {
        return NULL;
    } else if (tree->left != NULL) {
        return find_Min(tree->left);
    }
    return tree;
}


int leaf_cheak(const Node *tree, int start_range, int end_range) {
    int flag = 1;

    if (tree->left == NULL && tree->right == NULL) {

        if (((tree->elem) < start_range) || (((tree->elem) > end_range))) {
            // Нашелся лист который не подошел, рекурсия вернет при умножении 0
            return 0;
        } else {

            return 1;
        }
    }

    if (tree->left != NULL && tree->right == NULL) {
        flag *= leaf_cheak(tree->left, start_range, end_range);
    }
    if (tree->left == NULL && tree->right != NULL) {
        flag *= leaf_cheak(tree->right, start_range, end_range);
    }
    if (tree->left != NULL && tree->right != NULL) {
        flag *= leaf_cheak(tree->left, start_range, end_range);
        flag *= leaf_cheak(tree->right, start_range, end_range);
    }
    return flag;
}


int main() {
    Node *tree = NULL;
    print_menu();
    int menu_number;
    scanf("%d", &menu_number);
    while (menu_number != 0) {
        int number;
        switch (menu_number) {
            case 0:
                printf("◁ Завершение работы... \n");
                exit(0);
            case 1:
                printf("▷ Введите значение элемента: \n");
                scanf("%d", &number);

                if (SearchNode(tree, number) == 1) {
                    printf("(ㆆ_ㆆ) Такой элемент уже содержится в дереве, попробуйте другой. \n");
                } else {
                    tree = add_knot(tree, number);
                    printf("◁ Значение элемента успешно добавлено в дерево. \n");
                }
                break;
            case 2:
                if (tree != NULL) {
                    printf("◁ Полученное дерево: \n");
                    print_tree(tree, 1);
                } else {
                    printf("◁ Дерево пустое. \n");
                }
                break;
            case 3:
                if (tree != NULL) {
                    printf("▷ Введите элемент, который хотите удалить из дерева: \n");
                    scanf("%d", &number);

                    if (SearchNode(tree, number) == 1) {
                        delete_knot(tree, number);
                        printf("◁ Элемент успешно удален из дерева. \n");
                    } else {
                        printf("(ㆆ_ㆆ) Такого элемента не содержится в дереве. \n");
                    }
                } else {
                    printf("(ㆆ_ㆆ) Дерево пустое, удалять нечего. \n");
                }
                break;
            case 4:
                if (tree != NULL) {
                    printf("▷ Введите заданный диапозон, следуюзим образом: a;b\n");

                    int start_range, end_range;
                    scanf("%d;%d", &start_range, &end_range);
                    printf("\n");
                    if (leaf_cheak(tree, start_range, end_range)) {
                        printf("Во всех листьях двоичного дерева элементы находятся в заданном диапозоне чисел [%d;%d]! \n",
                               start_range, end_range);
                    } else {
                        printf("НЕ во всех листьях двоичного дерева элементы находятся в заданном диапозоне чисел![%d;%d]! \n",
                               start_range, end_range);
                    }
                } else {
                    printf("◁ Дерево пустое. \n");
                }


                break;
            default:
                printf("(ㆆ_ㆆ) Неправильный ввод, попробуйте еще раз: \n");
        }

        print_menu();
        scanf("%d", &menu_number);
    }
    return 0;
}