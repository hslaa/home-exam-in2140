
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

struct Node* create_test_nodes() {
    // Creating nodes as in graph_1.pdf sample
    struct Node *n = malloc(sizeof(struct Node) * 8);
   
    
    // New Node    
    n[0].own_address = 1;
    n[0].number_of_connections = 2;
    n[0].connections = malloc(sizeof(struct Connection) * 2);
    
       

    // New Node
    n[1].own_address = 11;
    n[1].number_of_connections = 3;
    n[1].connections = malloc(sizeof(struct Connection) * 3); 
  

    
    // New Node
    n[2].own_address = 19;
    n[2].number_of_connections = 3;
    n[2].connections = malloc(sizeof(struct Connection) * 3);

   

    // New Node
    n[3].own_address = 103;
    n[3].number_of_connections = 3;
    n[3].connections = malloc(sizeof(struct Connection) * 3);
    
    

    // New Node
    n[4].own_address = 13;
    n[4].number_of_connections = 3;
    n[4].connections = malloc(sizeof(struct Connection) * 3);
    
    

    // New Node
    n[5].own_address = 101;
    n[5].number_of_connections = 3;
    n[5].connections = malloc(sizeof(struct Connection) * 3);
    

    // New Node
    n[6].own_address = 17;
    n[6].number_of_connections = 2;    
    n[6].connections = malloc(sizeof(struct Connection) * 2);

    // New node
    n[7].own_address = 107;
    n[7].number_of_connections = 3;
    
    n[7].connections = malloc(sizeof(struct Connection) * 3);

       
    n[0].connections[0].destination = get_pointer_to_node(11, 8, n);
    n[0].connections[0].weight = 2;
    
    n[0].connections[1].destination = get_pointer_to_node(103, 8, n);
    n[0].connections[1].weight = 6;

    
    n[1].connections[0].destination = get_pointer_to_node(1, 8, n);
    n[1].connections[0].weight = 2;
    
    n[1].connections[1].destination = get_pointer_to_node(19, 8, n);
    n[1].connections[1].weight = 2;
    
    n[1].connections[2].destination = get_pointer_to_node(13, 8, n);
    n[1].connections[2].weight = 7;
    
    
    
    n[2].connections[0].destination = get_pointer_to_node(11, 8, n);
    n[2].connections[0].weight = 2;

    n[2].connections[1].destination = get_pointer_to_node(101, 8, n);
    n[2].connections[1].weight = 2;

    n[2].connections[2].destination = get_pointer_to_node(103, 8, n);
    n[2].connections[2].weight = 1;



    n[3].connections[0].destination = get_pointer_to_node(11, 8, n);
    n[3].connections[0].weight = 6;

    n[3].connections[1].destination = get_pointer_to_node(19, 8, n);
    n[3].connections[1].weight = 1;

    n[3].connections[2].destination = get_pointer_to_node(107, 8, n);
    n[3].connections[2].weight = 4;


    n[4].connections[0].destination = get_pointer_to_node(11, 8, n);
    n[4].connections[0].weight = 7;

    n[4].connections[1].destination = get_pointer_to_node(101, 8, n);
    n[4].connections[1].weight = 4;

    n[4].connections[2].destination = get_pointer_to_node(17, 8, n);
    n[4].connections[2].weight = 3;

    n[5].connections[0].destination = get_pointer_to_node(13, 8, n);
    n[5].connections[0].weight = 4;

    n[5].connections[1].destination = get_pointer_to_node(19, 8, n);
    n[5].connections[1].weight = 2;

    
    n[5].connections[2].destination = get_pointer_to_node(107, 8, n);
    n[5].connections[2].weight = 2;

    
   
    n[6].connections[0].destination = get_pointer_to_node(13, 8, n);
    n[6].connections[0].weight = 3;

    n[6].connections[1].destination = get_pointer_to_node(107, 8, n);
    n[6].connections[1].weight = 2;

    
    n[7].connections[0].destination = get_pointer_to_node(17, 8, n);
    n[7].connections[0].weight = 2;
  
    n[7].connections[1].destination = get_pointer_to_node(101, 8, n);
    n[7].connections[1].weight = 2;
   
    n[7].connections[2].destination = get_pointer_to_node(103, 8, n);
    n[7].connections[2].weight = 4;
    

    return n;
}
    
