
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
