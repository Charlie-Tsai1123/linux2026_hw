#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int n = 10, time = 1;
    struct list_node *head = NULL;
    bool is_shuffle = false;
    
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <number_of_nodes> <shuffle|no_shuffle> <fast_slow|two_pass> <time> <print/none>\n", argv[0]);
        return -1;
    }
    n = atoi(argv[1]);
    is_shuffle = (strcmp(argv[2], "shuffle") == 0);
    time = atoi(argv[4]);

    if (init_list(&head, n, is_shuffle) == -1) {
        return -1;
    }

    if (strcmp(argv[3], "fast_slow") == 0) {
        for (int i = 0; i < time; i++) {
             struct list_node *middle = middle_node_fast_slow(head);
             printf("Middle node value: %d\n", middle->val);
        }
    } else if (strcmp(argv[3], "two_pass") == 0) {
        for (int i = 0; i < time; i++) {
            struct list_node *middle = middle_node_two_pass(head);
            printf("Middle node value: %d\n", middle->val);
        }
    } else {
        fprintf(stderr, "Invalid method: %s. Use 'fast_slow' or 'two_pass'.\n", argv[3]);
        free_list(head);
        return -1;
    }

    if (argc >= 6 && strcmp(argv[5], "print") == 0) {
        printf("List: ");
        print_list(head);
    }
    
    free_list(head);
    return 0;

}