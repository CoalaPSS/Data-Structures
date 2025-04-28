#include "stack.h"


Node *create_node(void *data, size_t data_size) {
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->data = (void *)malloc(data_size);
    memcpy(new_node->data, data, data_size);
    new_node->next = NULL;
    
    return new_node;
}

void destroy_node(Node *node_to_delete) {
    free(node_to_delete->data);
    free(node_to_delete);
}

Stack *init_stack(size_t data_size) {
    Stack *new_stack = (Stack *)malloc(sizeof(Stack));
    new_stack->data_size = data_size;
    new_stack->top = NULL;
    new_stack->length = 0;

    return new_stack;
}

void push(Stack *s, void *data) {
    if (s->top == NULL) {
        s->top = create_node(data, s->data_size);
        s->length++;
        return;
    }
    
    Node *node_to_push = create_node(data, s->data_size);

    node_to_push->next = s->top;
    s->top = node_to_push;
    s->length++;
}

void *pop(Stack *s) {
    if (s->top == NULL) {
        return NULL;
    }

    void *result = malloc(s->data_size);
    memcpy(result, s->top->data, s->data_size);

    Node *aux_del = s->top;
    s->top = s->top->next;

    destroy_node(aux_del);
    s->length--;

    return result;
}

void clear_stack(Stack *s) {
    while(s->length > 0) {
        void *r;
        r = pop(s);
    }

    s->top = NULL;
}

void print_stack(Stack *s, void (*print_func)(void *data)) {
    if (s->top == NULL) {
        printf("Stack empty.\n");
    }

    Node *temp = s->top;

    for (int i = 0; i < s->length; i++) {
        print_func(temp->data);
        temp = temp->next;
    }
}

void print_int(void *data) {
    printf("%d ", *((int *)data));
}