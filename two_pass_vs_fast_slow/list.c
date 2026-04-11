#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(struct list_node **arr, int n) {
    // Fisher-Yates shuffle algorithm
    srand((unsigned)time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct list_node *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


int init_list(struct list_node **head, int n, bool is_shuffle) {
    // initialize an array of pointers to list nodes
    struct list_node **arr = (struct list_node **)malloc(n * sizeof(struct list_node *));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed for array of pointers\n");
        return -1;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = (struct list_node *)malloc(sizeof(struct list_node));
        if (!arr[i]) {
            fprintf(stderr, "Memory allocation failed for node %d\n", i);
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return -1;
        }
        arr[i]->val = i + 1;
        arr[i]->next = NULL;
    }
    if (is_shuffle) {
        shuffle(arr, n);
    }
    // link the nodes together
    for (int i = 0; i < n - 1; i++) {
        arr[i]->next = arr[i + 1];
    }
    *head = arr[0];
    free(arr);
    return 0;
}

void free_list(struct list_node *head) {
    struct list_node *cur = head;
    while (cur) {
        struct list_node *temp = cur;
        cur = cur->next;
        free(temp);
    }
}


void print_list(struct list_node *head) {
    struct list_node *cur = head;
    while (cur) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

struct list_node *middle_node_fast_slow(struct list_node *head) {
    struct list_node *slow, *fast;
    slow = fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct list_node *middle_node_two_pass(struct list_node *head) {
    struct list_node *cur = head;
    int n = 0;
    while (cur) {
        ++n;
        cur = cur->next;
    }
    int k = 0;
    cur = head;
    while (k < n / 2) {
        ++k;
        cur = cur->next;
    }
    return cur;
}