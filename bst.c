#include "bst.h"
#include "stack.h"   

/*
create_tree_node:
    Makes a node from the given data. The size in bytes of the data must be given
    in order to alloc the right amount of space for the data pointer of the node created.

    Note that, the memory is copied from the given data pointer (source) to the
    new node data pointer (destination). This is done because no changes to the (source) data
    should interfere with the data of the created node.
*/
Tree_node *create_tree_node(void *data, size_t data_size) {
    Tree_node *new_tnode = (Tree_node *)malloc(sizeof(Tree_node));
    if (new_tnode == NULL) return NULL;

    new_tnode->data = malloc(data_size);
    if (new_tnode->data == NULL) {
        free(new_tnode);
        return NULL;
    }

    memcpy(new_tnode->data, data, data_size);
    new_tnode->left = NULL;
    new_tnode->right = NULL;

    return new_tnode;
}
/*
destroy_tree_node:
    Destroy a node of the tree. First we must free the data pointer, as it is manually allocated.
    After that we can safely free the node, without leaving gargabe.
*/
void destroy_tree_node(Tree_node *node_to_destroy) {
    free(node_to_destroy->data);
    free(node_to_destroy);
}

/*
init_bst:
    Initializes the tree. The size of the data to be store by that tree must be given.
    Also, the function to compare the data, and to print the data, must be provided.
*/
Bin_Tree *init_bst(size_t data_size, 
        int (*comp_func)(void *data1, void *data2), 
        void (*print_data)(void *data)) {

    Bin_Tree *new_bst = (Bin_Tree *)malloc(sizeof(Bin_Tree));

    new_bst->root = NULL;
    new_bst->data_size = data_size;
    new_bst->compare = comp_func;
    new_bst->print_node = print_data; 
    
    return new_bst;
}
/*
insert_data:
    Inserts data in order.

    "result" stores the value of the comparison between the data to be inserted,
    and the current node data.

    "prev_result" stores the value of the comparison between the data to be inserted,
    and the parent node nada. That is done to know if the new node should be inserted to the left
    or to the right of the parent node. 
*/
void insert_data(Bin_Tree *t, void *data) {
    if (t->root == NULL) {
        t->root = create_tree_node(data, t->data_size);
    }
    else {
        Tree_node *previous = NULL;
        Tree_node *current = t->root;

        while (current) {
            previous = current;

            int result = t->compare(data, current->data);

            if (result >= 0) {
                current = current->right;
            }
            else {
                current = current->left;
            }
        }

        int prev_result = t->compare(data, previous->data);

        if (prev_result >= 0) {
            previous->right = create_tree_node(data, t->data_size);
        }
        else {
            previous->left = create_tree_node(data, t->data_size);
        }
    }
}
/*
replace_child:
    Is just a helper function for the "remove_data" function.

    If a node is deleted, and has a child, the parent of the deleted node must
    have the child of the delete node. This function determines it the new child
    should be placed to the left or to the right of the parent.
*/
void replace_child(Bin_Tree *t, Tree_node *previous, Tree_node *current, Tree_node *new_child) {
    if (previous == NULL) {
        t->root = new_child;
    }
    else if (previous->right == current) {
        previous->right = new_child;
    }
    else {
        previous->left = new_child;
    }

}

/*
remove_data:
    Removes the node that contains a certain data.
    
    It's important to note that, if the node to be deleted has 2 children.
    The node that will replace the deleted node, 
    will be the largest element of the deleted node left subtree.
*/
void remove_data(Bin_Tree *t, void *data) {
    Tree_node *current = t->root;
    Tree_node *previous = NULL;

    while (current) {
        int result = t->compare(data, current->data);

        if (result == 0) {

            //Case 1: Node to delete has no children
            if ((current->left == NULL) && (current->right == NULL)) {
                replace_child(t, previous, current, NULL);
                destroy_tree_node(current);
            }

            //Case 2: Node to delete has at least one children
            else if ((current->left == NULL) || (current->right == NULL)) {
                Tree_node *child = (current->left != NULL) ? current->left : current->right;
                replace_child(t, previous, current, child);
                destroy_tree_node(current);
            }

            //Case 3: Node to delete has two children
            else {
                Tree_node *succesor_parent = current;
                Tree_node *succesor = current->left;

                while (succesor->right) {
                    succesor_parent = succesor;
                    succesor = succesor->right;
                }
            
                memcpy(current->data, succesor->data, t->data_size);
                
                if (succesor_parent->left == succesor) {
                    succesor_parent->left = succesor->right;
                }
                else {
                    succesor_parent->right = succesor->right;
                }
                destroy_tree_node(succesor);
            }
            return;
        }
        previous = current;
        current = (result > 0) ? current->right : current->left;
    }
}
/*
print_tree:
    Uses the in-order-depth-first-search algorithm to traversal the entire tree,
    printing the elements from smallest to largest, according to the tree structure.

    This function uses a helper data structure called a stack, which is used to store the visited nodes.
*/
void print_tree(Bin_Tree *t) {
    Stack *node_stack = init_stack(sizeof(Tree_node));

    Tree_node *current = t->root;

    while (current != NULL || node_stack->length > 0) {
        while (current) {
            push(node_stack, current);
            current = current->left;
        }

        Tree_node *result = (Tree_node *)pop(node_stack);
        t->print_node(result->data);

        current = result->right;
    }
    printf("\n");
}