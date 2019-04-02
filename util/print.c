#include <stdio.h>


#include "../core/types/networktypes.h"



void print_node(struct Node node) {
    struct Connection c;
 
    printf("==== Node with address %d ====\n\n", node.own_address);
    printf("Number of connections: \n\t %d\n", node.number_of_connections);
    
    int i = 0;
    printf("Connections: \n");
    
    while (i < node.number_of_connections) {
        c = node.connections[i];
        printf("\t %d", node.own_address);
        printf(" -> ");
        printf("%d", c.destination);
        printf(" (%d)\n", c.weight);
        i += 1; 
    }
    printf("\n==============================\n");
}
