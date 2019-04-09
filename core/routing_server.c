/*
 *
 *  Main implementation of the routing_server
 *
 *
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../util/sssp.h"
#include "../util/logger.h"
#include "../util/print.h"
#include "../util/print_lib.h"
#include "types/networktypes.h"
#include "../util/helpers.h"

struct Node* create_test_nodes();
int test_sssp(struct Node *n, struct Node source, int size);

int is_node_on_shortest_path(struct Node* destination, struct Node* intermediate);

int main() {

    logger("DEBUG", "Starting routing_server");
    
    struct Node *testnodes = malloc(sizeof(struct Node) * 8);
    testnodes = create_test_nodes(8);
    
    print_node(testnodes[0]);
    print_node(testnodes[1]); 
    print_node(testnodes[2]);
    print_node(testnodes[3]);
    print_node(testnodes[4]);
    print_node(testnodes[5]);
    print_node(testnodes[6]);
    print_node(testnodes[7]);
    

    test_sssp(testnodes, testnodes[0], 8);

    free_nodes(testnodes, 8); 
    
    return 0;
}

int test_sssp(struct Node *n, struct Node source, int size) {
    int i;  
    int j;
    int pathlen;
    struct Node* tmpNode;
    sssp(n, source, size);
    
    printf("==== test_sssp() ====\n");
    
    
    for (i = 0; i < size; i++) {

        for (j = 0; j < n[i].number_of_connections; j++) {
            pathlen = is_node_on_shortest_path(&n[i], n[i].connections[j].destination);
            print_weighted_edge(n[i].own_address, n[i].connections[j].destination->own_address, pathlen);
        }
    }
    
    for (i = 0; i < size; i++) {
        tmpNode = &n[i];
        printf("Path backwards from Node %d\n", tmpNode->own_address);
   
        while (tmpNode->previous != NULL) {
            printf(" %d --> ", tmpNode->own_address);
            
            //cost += tmpNode->distance;
            tmpNode = tmpNode->previous;
        }
        printf("(%d)\n", n[i].distance);
    }

    return 0;
}

int is_node_on_shortest_path(struct Node* destination, struct Node* intermediate) {

    struct Node* tmpNode;
    int pathlen = 1;
    int hit_root = 0;
    tmpNode = destination;
    while (tmpNode != NULL) {
        
        
        if (tmpNode->own_address == 1) {
            printf("we hit roooot\n");
            hit_root = 1;
        }
        tmpNode = tmpNode->previous;


    }
    
    if (!hit_root) {
        pathlen = -1; 

    }


    printf("Returning %d for pathlen (destination node %d has distance %d from node 1)\n",
            pathlen,
            destination->own_address,
            destination->distance
          );


    return pathlen;
}
