#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tree_node {
    void *data;
    struct Tree_node *left, *right;
};

struct Bin_Tree {
    struct Tree_node *root;
    size_t data_size;
    int (*compare)(void *data1, void *data2);
    void (*print_node)(void *data);
};

typedef struct Tree_node Tree_node;
typedef struct Bin_Tree Bin_Tree;

Bin_Tree *init_bst(size_t data_size, int (*comp_func)(void *data_to_insert, void *data_comp), void (*print_data)(void *data));
void insert_data(Bin_Tree *t, void *data);
void remove_data(Bin_Tree *t, void *data);
void print_tree(Bin_Tree *t);

#endif