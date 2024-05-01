#pragma once

/**
 * @brief Ошибка. Текст пишется красным цветом
 * 
 */
#define ERROR(text) printf("\033[1;31m%s\033[0m\n", text)

/**
 * @brief Предупреждение. Текст пишется жёлтым цветом
 * 
 */

#define WARNING(text) printf("\033[1;33m%s\033[0m\n", text)

/**
 * @brief Успешное выполнение чего-либо, логирование. Текст пишется зелёным цветом
 * 
 */

#define SUCCESS(text) printf("\033[1;32m%s\033[0m\n", text)

/**
 * @brief Структура графа содержи информацию (int), ссылку на левый и правый дочерный элемент, а также родительский
 *
 */
typedef struct Tree
{
    int data;
    struct Tree *left;
    struct Tree *right;
    struct Tree *parent;
} Tree;

/**
 * Печать в определенном уровне
 * @param root
 * @param level
 * @return
 */
int print_level(const Tree *root, int level);
/**
 * Максимум
 * @param x
 * @param y
 * @return максимальный из двух элементов
 */
int max(const int x, const int y);
/**
 * Находит высоту(глубину) графа
 * @param tree
 * @return высота(глубина) графа
 */
int height(const Tree *tree);

/**
 * Создает граф с корнем-значением без дочерных элементов
 * @param value
 * @return граф с корнем-значением без дочерных элементов
 */

Tree *create_root_tree(const int value);

/**
 * Добавить элемент в граф
 * @param root
 * @param value
 * @return Граф с новым элементом
 */

Tree *add_element_tree(Tree *root, const int value);

/**
 * Вывод дерева
 * @param tree
 * @param n
 * @todo Исправить последний перенос строки
 */

void print_tree(Tree *tree, int n);

/**
 * поиск элемента в графе по значению
 * @param tree
 * @param value
 * @return граф, если элемент существует
 */
Tree *search_in_tree(Tree *tree, const int value);

/**
 * поиск наименьшего элемента в графе
 * @param tree
 * @return наибольший элемент в графе
 */
Tree *maxi(Tree *tree);

/**
 * поиск наименьшего элемента в графе
 * @param tree
 * @return наименьший элемент в графе
 */
Tree *mini(Tree *tree);

/**
 * Подсчёт листочков
 * @param tree
 * @return количество листьев
 */
int count_leaf(const Tree *tree);

/**
 * Удалить элемент из графа
 * @param root
 * @param value
 * @return Граф без некоего элемента
 */
Tree *delete_element(Tree *root, int value);

/**
 * Нахождение степени
 * @param tree
 * @return степень
 */

int find_degree(Tree *tree);

/**
 * Уничтожение графа (иначе - утечка памяти)
 * @param tree
 */
void destroy_tree(Tree *tree);

/**
 * Вывод меню
 */
void print_menu();