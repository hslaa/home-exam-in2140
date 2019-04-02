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
#include "types/networktypes.h"

struct Node* create_test_nodes(int numberOfNodes);

int main() {

    logger("DEBUG", "Starting routing_server");
    
    struct Node *testnodes = malloc(sizeof(struct Node) * 8);;
    testnodes = create_test_nodes(8);
    return 0;
}

struct Node* create_test_nodes(int numberOfNodes) {
    // Creating nodes as in graph_1.pdf sample
    struct Node *n = malloc(sizeof(struct Node) * 8);
   
    
    // New Node    
    n->own_address = 1;
    n->number_of_connections = 2;
    n->connections = malloc(sizeof(struct Connection) * 2);
    n->connections->destination = 11;
    n->connections->weight = 2;
    
    n->connections += 1;
    n->connections->destination = 103;
    n->connections->weight = 6;

    n += 1;

    // New Node
    n->own_address = 11;

    n->number_of_connections = 3;
    n->connections = malloc(sizeof(struct Connection) * 3); 
    
    n->connections->destination = 1;
    n->connections->weight = 2;
    
    n->connections += 1;


    n->connections->destination = 19;
    n->connections->weight = 2;
    
    n->connections += 1;

    n->connections->destination = 13;
    n->connections->weight = 7;

    n += 1;
    
    // New Node
    n->own_address = 19;
    
    
    n->number_of_connections = 3;
    n->connections = malloc(sizeof(struct Connection) * 3);

    n->connections->destination = 11;
    n->connections->weight = 2;
    n->connections += 1;


    n->connections->destination = 101;
    n->connections->weight = 2;
    n->connections += 1;


    n->connections->destination = 103;
    n->connections->weight = 1;
    n->connections += 1;


    n += 1;

    // New Node
    n->own_address = 103;
    
    n->number_of_connections = 3;
    n->connections = malloc(sizeof(struct Connection) * 3);
    
    n->connections->destination = 1;
    n->connections->weight = 6;
    n->connections += 1;
    
    n->connections->destination = 19;
    n->connections->weight = 1;
    n->connections += 1;


    n->connections->destination = 107;
    n->connections->weight = 4;

    n += 1;

    // New Node
    n->own_address = 13;
    n->number_of_connections = 3;
    
    n->connections = malloc(sizeof(struct Connection) * 3);
    
    n->connections->destination = 11;
    n->connections->weight = 7;
    n->connections += 1;

    n->connections->destination = 101;
    n->connections->weight = 4;
    n->connections += 1;


    n->connections->destination = 17;
    n->connections->weight = 3;



    n += 1;

    // New Node
    n->own_address = 101;

    n->number_of_connections = 3;
    
    n->connections = malloc(sizeof(struct Connection) * 3);
    
    n->connections->destination = 13;
    n->connections->weight = 4;
    n->connections += 1;


    n->connections->destination = 19;
    n->connections->weight = 2;
    n->connections += 1;
    
    n->connections->destination = 107;
    n->connections->weight = 2;
  
    n += 1;

    // New Node
    n->own_address = 17;

    n->number_of_connections = 2;
    n->connections = malloc(sizeof(struct Connection) * 2);
    
    n->connections->destination = 13;
    n->connections->weight = 3;
    n->connections += 1;

    n->connections->destination = 107;
    n->connections->weight = 2;

    n += 1;

    // New node
    n->own_address = 107;
    n->number_of_connections = 3;
    n->connections = malloc(sizeof(struct Connection) * 3);

    n->connections->destination = 17;
    n->connections->weight = 2;
    n->connections += 1;
    

    n->connections->destination = 101;
    n->connections->weight = 2;
    n->connections += 1;
    

    n->connections->destination = 103;
    n->connections->weight = 4;
    
    

    return n;
}
    
