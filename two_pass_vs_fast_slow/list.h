#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

struct list_node {
    int val;
    struct list_node *next;
};

int init_list(struct list_node **head, int n, bool is_shuffle);
void free_list(struct list_node *head);
void print_list(struct list_node *head);

struct list_node *middle_node_fast_slow(struct list_node *head);
struct list_node *middle_node_two_pass(struct list_node *head);

#endif