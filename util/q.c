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
        q[i] = &n[i];
    }


    return q;

}

struct Node* extract_min(struct Node **q) {
    int i;
    double min_distance = INFINITY;
   
    
    struct Node *ret_node;
    
    if (size_of_q == 0) {
        return NULL;
    }

    i = 0;
    while (i < size_of_q) {
        
        if (q[i] == NULL) {
            continue;
        }

        if (q[i]->distance < min_distance) {
            ret_node = q[i];
            min_distance = ret_node->distance;
        }

        i += 1;
    
    }
    size_of_q -= 1;
    return ret_node;    
}


/*
int main() {

    struct Node *testnodes = malloc(sizeof(struct Node) * 3);

    testnodes[0].own_address = 100;
    testnodes[0].distance = 60;

    testnodes[1].own_address = 200;
    testnodes[1].distance = 100;

    testnodes[2].own_address = 123;
    testnodes[2].distance = 0;
    
    struct Node **q = initialize_queue(testnodes, 3);

    struct Node *smallestNode = extract_min(q);
    
    
    printf("Address of smallest node: %d\n", smallestNode->own_address);

    free(testnodes); 
    free(q);
}

*/
