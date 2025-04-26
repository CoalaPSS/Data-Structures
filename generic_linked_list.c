#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define DEBUG() printf("DEBUG\n")
#define BUF_LIMIT 50


struct Node {
    void *data;
    struct Node *next;
};

struct LinkedList {
    struct Node *head;
    size_t data_size;
};

typedef struct Node Node;
typedef struct LinkedList LinkedList;

void print_addr(void *ptr)
{
    printf("%p\n", ptr);
}

Node *create_node(size_t data_size, void *data)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = malloc(data_size);
    memcpy(new_node->data, data, data_size);
    new_node->next = NULL;
    return new_node;
}

LinkedList *init_linked_list(size_t data_size) {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->data_size = data_size;
    list->head = NULL;
    return list;
}

LinkedList *insert_at_head(LinkedList *list, void *data) {
    if (list->head == NULL)
    {
        Node *node_to_insert = create_node(list->data_size, data);
        list->head = node_to_insert;
        return list;    
    }

    Node *node_to_insert = create_node(list->data_size, data);
    node_to_insert->next = list->head;
    list->head = node_to_insert;
    return list;
}

LinkedList *delete_from_head(LinkedList *list) {
    if (list->head == NULL)
    {
        return NULL;
    }

    Node *node_to_delete = list->head;
    list->head = list->head->next;
    free(node_to_delete);
    return list;    
}

LinkedList *delete_data(LinkedList *list, void *data_to_delete, int (*comp)(void *, void *)) {
    Node *current_node = list->head;
    Node *previous_node = NULL;
    Node *aux;

    if (comp(current_node->data, data_to_delete)) {
        return delete_from_head(list);
    }

    while (current_node) {
        if (comp(current_node->data, data_to_delete)) {
            previous_node->next = current_node->next;
            aux = current_node;
            current_node = current_node->next;
            free(aux);
        }
        else {
            previous_node = current_node;
            current_node = current_node->next;
        }
    }

    return list;

}

LinkedList *insert_after_node(LinkedList *list, void *data, void *data_to_insert_after, int (*comp)(void *, void *)) {
    Node *temp = list->head;

    while ((temp) && (comp(temp->data, data_to_insert_after) == 0)) {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return list;
    }

    Node *new_node = create_node(list->data_size, data);
    new_node->next = temp->next;
    temp->next = new_node;

    return list;
}

void print_list(LinkedList *list, void (*print)(void *)) {
    Node *temp = list->head;

    while(temp) {
        print(temp->data);
        printf(" - ");
        temp = temp->next;
    }
    printf("\n");
}

void print_str(void *data) {
    printf("%s", (char *)(data));
}

void print_int(void *data) {
    printf("%d", *((int *)(data)));
}

int compare_int(void *data1, void *data2) {
    int data1_int = *((int *)data1);
    int data2_int = *((int *)data2);

    if (data1_int == data2_int) return 1;
    else return 0;
}

void get_str(char *buf) {
    fgets(buf, BUF_LIMIT, stdin);
}

void get_int(int *num) {
    scanf("%d", num);
}