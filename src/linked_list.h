#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

// struct for a node in a doubly linked list
typedef struct node {
    int location;
    struct node* next;
    struct node* prev;
} node_t;

// function declarations
int length_list(node_t* head_list);
int get_first(node_t* head_list);
int get_last(node_t* head_list);
void insert_first(node_t** head_list, int to_add);
void insert_last(node_t** head_list, int to_add);
int get(node_t* head_list, int index);
int remove_element(node_t** head_list, int to_remove);
void reverse_helper(node_t** head_list);
void reverse(node_t** head_list);
int remove_first(node_t** head_list);
int remove_last(node_t** head_list);

#endif
