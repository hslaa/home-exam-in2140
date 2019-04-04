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
#include "../util/helpers.h"

struct Node* create_test_nodes();

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
