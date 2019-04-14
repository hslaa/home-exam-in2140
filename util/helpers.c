
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

int initialize_node_connections(struct Node* node, int number_of_connections) { 
    node->number_of_connections = 0;
    node->connections = malloc(sizeof(struct Connection) * number_of_connections);
    
    return 0;
}

int set_connection(struct Node* node, int dst, int weight) { 
    printf("set_connection() for connection %d with dst %d and weight %d\n", node->number_of_connections, dst, weight);
    node->connections[node->number_of_connections].destination = dst;
    node->connections[node->number_of_connections].weight = weight;
    node->number_of_connections += 1;

    return 0;

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



int initialize_routing_table(struct Node* n, int size) { 
    n->rt = malloc( sizeof ( struct routing_table ) );
    n->rt->size_of_rt = 0;
    
    printf("Initialized routing_table of Node %d", n->own_address);

    if (size > 0) {
        n->rt->hops = malloc( sizeof( struct hop** ) * size );
    } 

    return 0;
}
int initialize_routing_tables(struct Node *n, int size) {
    int i;
    printf("starting initialize_routing_tables with size %d\n", size);
    for (i = 0; i < size; i++) {    
        n[i].rt = malloc( sizeof ( struct routing_table ) );
        n[i].rt->size_of_rt = 0;
        n[i].rt->hops = malloc( sizeof( struct hop** ) * size );
        
    }
    return 0;
}

int insert_hop_in_routing_table(struct Node* node, int dst, int n_hop) {
    int size = node->rt->size_of_rt;
    
    node->rt->hops[size] = malloc(sizeof(struct hop*)); 
    
    node->rt->hops[size]->destination = dst;
    node->rt->hops[size]->next_hop = n_hop;
    
    printf("Finished adding hop <%d:%d> to node %d\n", 
            node->rt->hops[size]->destination,
            node->rt->hops[size]->next_hop,
            node->own_address
          );
    node->rt->size_of_rt += 1;
    


    return 0;
}

int free_routing_tables(struct Node *n, int size) {
    int i;
    int j;
    for (i = 0; i < size; i++) {
        printf("i = %d\n", i); 
        for (j = 0; j < n[i].rt->size_of_rt; j++) {
            printf("freeing n[%d].rt->hops[%d]\n", i, j);
            free(n[i].rt->hops[j]);
        }
        free(n[i].rt->hops);
        free(n[i].rt);
    }

    return 0;
}


int test_routing_tables(struct Node* node) {
    int i;
    struct hop* h;
    printf("Testing routing table of size %d\n", node->rt->size_of_rt);
    for (i = 0; i < node->rt->size_of_rt; i++) {
        h = node->rt->hops[i];
        printf("=== HOP ===\n");
        printf("to %d: jump to %d)\n", h->destination, h->next_hop);
        printf("===========\n\n");
    }

    return 0;
}

int create_routing_tables(struct Node *n, int size) {
    int i;
    struct Node* tmp_node;
    initialize_routing_tables(n, size);
    for (i = 0; i < size; i++) {
        //  
        //  For hver node
        //  Malloc plass
        //  tmpNode = node
        //  while (tmpNode != NULL) 
        //      sett på tmpNode->previous:  <NODE.own_address, NODE.own_address)
       
        //
      
        

        tmp_node = &n[i]; 
        while (tmp_node->previous != NULL) {            
            insert_hop_in_routing_table(tmp_node->previous, n[i].own_address, tmp_node->own_address); 
            tmp_node = tmp_node->previous;

        }
    }

    return 0;
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

    // Node 1   
    n[0].connections[0].destination = 11; 
    n[0].connections[0].weight = 2;
    
    n[0].connections[1].destination = 103; 
    n[0].connections[1].weight = 6;

    // Node 11
    n[1].connections[0].destination = 1;
    n[1].connections[0].weight = 2;
    
    n[1].connections[1].destination = 19; 
    n[1].connections[1].weight = 2;
    
    n[1].connections[2].destination = 13; 
    n[1].connections[2].weight = 7;
    
    
    // Node 19
    n[2].connections[0].destination = 11; 
    n[2].connections[0].weight = 2;

    n[2].connections[1].destination = 101; 
    n[2].connections[1].weight = 2;

    n[2].connections[2].destination = 103; 
    n[2].connections[2].weight = 1;


    // Node 103
    n[3].connections[0].destination = 1; 
    n[3].connections[0].weight = 6;

    n[3].connections[1].destination = 19; 
    n[3].connections[1].weight = 1;

    n[3].connections[2].destination = 107; 
    n[3].connections[2].weight = 4;


    // Node 13
    n[4].connections[0].destination = 11;
    n[4].connections[0].weight = 7;

    n[4].connections[1].destination = 101; 
    n[4].connections[1].weight = 4;

    n[4].connections[2].destination = 17; 
    n[4].connections[2].weight = 3;


    // Node 101
    n[5].connections[0].destination = 13; 
    n[5].connections[0].weight = 4;

    n[5].connections[1].destination = 19; 
    n[5].connections[1].weight = 2;

    
    n[5].connections[2].destination = 107; 
    n[5].connections[2].weight = 2;

    
    // Node 17
    n[6].connections[0].destination = 13; 
    n[6].connections[0].weight = 3;

    n[6].connections[1].destination = 107; 
    n[6].connections[1].weight = 2;

    // Node 107
    n[7].connections[0].destination = 17; 
    n[7].connections[0].weight = 2;
  
    n[7].connections[1].destination = 101; 
    n[7].connections[1].weight = 2;
   
    n[7].connections[2].destination = 103;
    n[7].connections[2].weight = 4;
    

    return n;
}
    
