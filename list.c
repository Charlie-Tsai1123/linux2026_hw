#include <stdlib.h>
#include <stdio.h>

struct list_node {
    int val;
    struct list_node *next;
};

int init_list(struct list_node **head, int n) {
    struct list_node **current = head;
    for (int i = 0; i < n; i++) {
        *current = (struct list_node *)malloc(sizeof(struct list_node));
        if (*current == NULL) {
            perror("malloc failed");
            return -1;
        }
        (*current)->val = i;
        (*current)->next = NULL;
        current = &((*current)->next);
    }
    return 0;
}

void free_list(struct list_node *head) {
    while (head) {
        struct list_node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(struct list_node *head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    struct list_node *head = NULL;
    if (argc > 1) {
        int n = atoi(argv[1]);
        if (n < 0) {
            fprintf(stderr, "Invalid number of nodes: %d\n", n);
            return -1;
        }
        if (init_list(&head, n) == -1) {
            return -1;
        }
    } else {
        if (init_list(&head, 10) == -1) {
            return -1;
        }
    }

    print_list(head);
    free_list(head);
    return 0;
}