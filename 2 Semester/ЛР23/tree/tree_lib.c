#include <stdlib.h>
#include <stdio.h>
#include "tree_lib.h"

static int sum = 0;

int print_level(const Tree *root, int level)
{
    if (root == NULL)
        return 0;
    if (level == 1)
        return sum++;
    else if (level > 0)
    {
        print_level(root->left, level--);
        print_level(root->right, level--);
    }
    return 0;
}

int max(const int x, const int y)
{
    return (x >= y) ? x : y;
}

int height(const Tree *tree)
{
    if (tree == NULL)
        return 0;
    return max(height(tree->left), height(tree->right));
}

Tree *create_root_tree(const int value)
{
    Tree *tree = malloc(sizeof(Tree));
    tree->data = value;
    tree->left = NULL;
    tree->right = NULL;
    tree->parent = NULL;
    return tree;
}

//Tree *add_element_tree(Tree *root, const int value)
//{
//
//    if (root == NULL)
//    {
//        SUCCESS("Выполнено.");
//        return create_root_tree(value);
//    }
//    Tree *NewTree = (Tree *)malloc(sizeof(Tree));
//    NewTree->data = value;
//    Tree *tree1 = root;
//    Tree *tree2 = NULL;
//    while (tree1 != NULL)
//    {
//        tree2 = tree1;
//        if (value < tree1->data)
//        {
//            tree1 = tree1->left;
//        }
//        else if (value > tree1->data)
//        {
//            tree1 = tree1->right;
//        }
//        else
//        {
//            WARNING("Элемент с таким значением уже есть, введите новый.");
//            return root;
//        }
//    }
//    NewTree->parent = tree2;
//    NewTree->left = NULL;
//    NewTree->right = NULL;
//    if (value < tree2->data)
//    {
//        tree2->left = NewTree;
//    }
//    else
//    {
//        tree2->right = NewTree;
//    }
//    SUCCESS("Выполнено.");
//    return root;
//}
Tree *add_element_tree(Tree *root, const int value)
{
    if (root == NULL)
    {
        SUCCESS("Выполнено.");
        return create_root_tree(value);
    }

    Tree *current = root;
    Tree *parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (value < current->data)
        {
            current = current->left;
        }
        else if (value > current->data)
        {
            current = current->right;
        }
        else
        {
            WARNING("Элемент с таким значением уже есть, введите новый.");
            return root;
        }
    }

    Tree *newTree = (Tree *)malloc(sizeof(Tree));
    newTree->data = value;
    newTree->parent = parent;
    newTree->left = NULL;
    newTree->right = NULL;

    if (value < parent->data)
    {
        parent->left = newTree;
    }
    else
    {
        parent->right = newTree;
    }
    SUCCESS("Выполнено.");
    return root;
}

void print_tree(Tree *tree, int n)
{
    int work = 0;
    if (tree != NULL)
    {
        print_tree(tree->right, n + 1);
        for (int i = 0; i < n; i++)
            printf("\t");
        printf("%d\n", tree->data);
        print_tree(tree->left, n + 1);
        work = 1;
    }
    else
    {
        // пустая строка
        printf(" ");
    }
}

Tree *search_in_tree(Tree *tree, const int value)
{
    if (tree == NULL)
        return NULL;
    if (tree->data == value)
        return tree;
    if (value > tree->data)
        return search_in_tree(tree->right, value);
    else
        return search_in_tree(tree->left, value);
}

Tree *maxi(Tree *tree)
{
    Tree *cur = tree;
    while (cur->right != NULL)
    {
        cur = cur->right;
    }
    return cur;
}

Tree *mini(Tree *tree)
{
    Tree *cur = tree;
    while (cur->left != NULL)
    {
        cur = cur->left;
    }
    return cur;
}

int count_leaf(const Tree *tree)
{
    int cnt = 0;
    if (tree->left == NULL && tree->right == NULL)
    {
        printf("%d\t", tree->data);
        return 1;
    }
    if (tree->left != NULL && tree->right == NULL)
    {
        cnt += count_leaf(tree->left);
    }
    if (tree->left == NULL && tree->right != NULL)
    {
        cnt += count_leaf(tree->right);
    }
    if (tree->left != NULL && tree->right != NULL)
    {
        cnt += count_leaf(tree->left);
        cnt += count_leaf(tree->right);
    }
    return cnt;
}

Tree* delete_element(Tree* root, int value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->data) {
        root->left = delete_element(root->left, value);
    }
    else if (value > root->data) {
        root->right = delete_element(root->right, value);
    }
    else {
        if (root->left == NULL) {
            Tree* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Tree* temp = root->left;
            free(root);
            return temp;
        }

        Tree* temp = mini(root->right);
        root->data = temp->data;
        root->right = delete_element(root->right, temp->data);
    }
    return root;
}

int find_degree(Tree *tree) {
    if (tree == NULL) {
        return 0;
    } else {
        int degree = 0;
        if (tree->left != NULL) {
            degree++;
        }
        if (tree->right != NULL) {
            degree++;
        }
        int leftDegree = find_degree(tree->left);
        int rightDegree = find_degree(tree->right);
        int maxSubtreeDegree = max(leftDegree, rightDegree);
        return max(degree, maxSubtreeDegree);
    }
}

void destroy_tree(Tree *tree)
{
    if (tree != NULL)
    {
        destroy_tree(tree->left);
        destroy_tree(tree->right);
        void *ptr = (void *)tree;
        tree->data = 0;
        tree->left = NULL;
        tree->parent = NULL;
        tree->right = NULL;
        free(ptr);
    }
}

void print_menu()
{
    printf("\nВыберите дейтвие и введите его номер:\n0) Выход\n");
    printf("1) Ввести в дерево элемент.\n");
    printf("2) Распечатать дерево.\n");
    printf("3) Удалить элемент из дерева.\n");
    printf("4) Определить степень двоичного дерева.\n");
}