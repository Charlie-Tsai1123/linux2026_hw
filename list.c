#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct list_node {
    int val;
    struct list_node *next;
};

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

int init_list(struct list_node **head, int n) {
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

    // shuffle the array of pointers
    shuffle(arr, n);

    // link the nodes together
    for (int i = 0; i < n - 1; i++) {
        arr[i]->next = arr[i + 1];
    }
    *head = arr[0];
    free(arr);
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