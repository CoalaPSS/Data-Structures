#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node {
    void *data;
    struct Node *next;
};

struct Stack {
    struct Node *top;
    int length;
    size_t data_size;
};

typedef struct Node Node;
typedef struct Stack Stack;

//functions declarations
Node *create_node(void *data, size_t data_size);
void destroy_node(Node *node_to_delete);
Stack *init_stack(size_t data_size);
void push(Stack *s, void *data);
void *pop(Stack *s);
void clear_stack(Stack *s);
void print_stack(Stack *s, void (*print_func)(void *data));

#endif