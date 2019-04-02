
/*
 *
 *  Put all smaller helper functions here, such as search-functions +++
 *
 *
 *
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "../core/types/networktypes.h"

int get_index_of_node(int own_address, int size_of_array, struct Node *node_array) {
    int i = 0;
    
    printf("trying to find node %d in a array of size %d\n", own_address, size_of_array);

    while(i < size_of_array) {
        if (node_array[i].own_address == own_address) {
            printf("Checking array index %d\n", i);
            return i;
        }
        i += 1;
    }

    return -1;
}

struct Node* get_pointer_to_node(int own_address, int size_of_array, struct Node *node_array) {

    int i = 0;
    
    printf("trying to find node %d in a array of size %d\n", own_address, size_of_array);

    while(i < size_of_array) {
        if (node_array[i].own_address == own_address) {
            return &node_array[i]; 
        }
        i += 1;
    }

    return NULL;
}


void free_connections(struct Node n) {
    printf("Deleting connections on node %d\n", n.own_address);
    free(n.connections);

}

void free_nodes(struct Node *n, int number_of_nodes) {
    int i;

    for (i = 0; i < number_of_nodes; i++) {
        free_connections(n[i]);
    }
    free(n);
}


