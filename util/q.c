/*
 *
 *  helper function to perform SSSP 
 *
 *
 */
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "../core/types/networktypes.h"

int size_of_q;


struct Node** initialize_queue(struct Node *n, int size_q) {
    int i;
    struct Node** q;
    size_of_q = size_q;
    q = malloc(sizeof(struct Node*) * size_of_q);
    
    for (i = 0; i < size_of_q; i++) {
        printf("Inserting node %d into PriorityQueue with distance\n", n[i].own_address);
        q[i] = &n[i];
        printf("(%d)\n", q[i]->own_address);
    }


    return q;

}

int is_empty() {
    return size_of_q;
}

struct Node* extract_min(struct Node **q) {
    int i;
    int min_distance = 100000;
    int min_index = 0;

    printf("START extract_min()\n"); 
    struct Node *ret_node = NULL;

    if(size_of_q == 0) {
        printf("size_of_q == 0: returning NULL\n");
        return NULL;
    }

    i = 0;
    while(i < size_of_q) {
        printf("\n\tchecking element %d\n", i);
        if (q[i] == NULL) {
            printf("\t\t element %d was NULL\n", i);
            i += 1;
            continue;
        }

        if (q[i]->distance < min_distance) {
            printf("\t\t element %d replaces %d as the smallest element\n", i, min_index);
            ret_node = q[i];
            min_distance = ret_node->distance;
            min_index = i;
        }
        i += 1; 
    }
    q[min_index] = NULL;
    printf("END extract_min()\n"); 
    
    return ret_node;     
}

int free_queue(struct Node **q) {
    int i;

    for (i = 0; i < size_of_q; i++) {
        free(q[i]);
    }
    free(q);
    printf("Finished freeing %d queue elements", i);

    return 0;
}
