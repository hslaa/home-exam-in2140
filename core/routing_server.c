/*
 *
 *  Main implementation of the routing_server
 *
 *
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../util/logger.h"
#include "../util/print.h"
#include "types/networktypes.h"

struct Node* create_test_nodes(int numberOfNodes);

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
    
     

    free_nodes(testnodes, 8); 
    


    return 0;
}

struct Node* create_test_nodes(int numberOfNodes) {
    // Creating nodes as in graph_1.pdf sample
    struct Node *n = malloc(sizeof(struct Node) * 8);
   
    
    // New Node    
    n[0].own_address = 1;
    n[0].number_of_connections = 2;
    n[0].connections = malloc(sizeof(struct Connection) * 2);
    
    n[0].connections[0].destination = 11;
    n[0].connections[0].weight = 2;
    

    n[0].connections[1].destination = 103;
    n[0].connections[1].weight = 6;
    

    // New Node
    n[1].own_address = 11;

    n[1].number_of_connections = 3;
    n[1].connections = malloc(sizeof(struct Connection) * 3); 
    
    n[1].connections[0].destination = 1;
    n[1].connections[0].weight = 2;
    
    n[1].connections[1].destination = 19;
    n[1].connections[1].weight = 2;
    
    n[1].connections[2].destination = 13;
    n[1].connections[2].weight = 7;


    
    // New Node
    n[2].own_address = 19;
    
    n[2].number_of_connections = 3;
    n[2].connections = malloc(sizeof(struct Connection) * 3);

    n[2].connections[0].destination = 11;
    n[2].connections[0].weight = 2;

    n[2].connections[1].destination = 101;
    n[2].connections[1].weight = 2;

    n[2].connections[2].destination = 103;
    n[2].connections[2].weight = 1;



    // New Node
    n[3].own_address = 103;
    
    n[3].number_of_connections = 3;
    n[3].connections = malloc(sizeof(struct Connection) * 3);
    
    n[3].connections[0].destination = 1;
    n[3].connections[0].weight = 6;

    
    n[3].connections[1].destination = 19;
    n[3].connections[1].weight = 1;

    n[3].connections[2].destination = 107;
    n[3].connections[2].weight = 4;


    // New Node
    n[4].own_address = 13;
    n[4].number_of_connections = 3;
    
    n[4].connections = malloc(sizeof(struct Connection) * 3);
    
    n[4].connections[0].destination = 11;
    n[4].connections[0].weight = 7;


    n[4].connections[1].destination = 101;
    n[4].connections[1].weight = 4;



    n[4].connections[2].destination = 17;
    n[4].connections[2].weight = 3;


    // New Node
    n[5].own_address = 101;

    n[5].number_of_connections = 3;
    
    n[5].connections = malloc(sizeof(struct Connection) * 3);
    
    n[5].connections[0].destination = 13;
    n[5].connections[0].weight = 4;

    n[5].connections[1].destination = 19;
    n[5].connections[1].weight = 2;

    
    n[5].connections[2].destination = 107;
    n[5].connections[2].weight = 2;
  


    // New Node
    n[6].own_address = 17;

    n[6].number_of_connections = 2;
    
    n[6].connections = malloc(sizeof(struct Connection) * 2);
    
    n[6].connections[0].destination = 13;
    n[6].connections[0].weight = 3;

    n[6].connections[1].destination = 107;
    n[6].connections[1].weight = 2;



    // New node
    n[7].own_address = 107;
    n[7].number_of_connections = 3;
    
    n[7].connections = malloc(sizeof(struct Connection) * 3);

    n[7].connections[0].destination = 17;
    n[7].connections[0].weight = 2;
  
    n[7].connections[1].destination = 101;
    n[7].connections[1].weight = 2;
   
    n[7].connections[2].destination = 103;
    n[7].connections[2].weight = 4;
    
     

    return n;
}
    
