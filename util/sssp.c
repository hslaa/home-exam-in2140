/*
 *
 *  Code for the single source shortest path (SSSP) algorithm and helper methods
 *
 *  Implementation of Dijkstra.
 *
 *
 */
#include <string.h> 
#include <math.h>
#include <stdio.h>

#include "../core/types/networktypes.h"
#include "../util/helpers.h"
#include "q.h"

void sssp(struct Node *n, int size);
void generate_routing_tables(struct Node* n, int size);


void sssp(struct Node *n, int size) {
    struct Node** q;
    struct Node* u;
    struct Node* d;
    struct Node* source;
    struct Connection c;
  
    int alt;
    int i;
    int j;

  


    //  Initialize a priority queue Q.
    //  Q sorts based on node.distance
    q = initialize_queue(n, size);        
    
    //  for each NODE in n*
    //      n[i].distance = INF;
    //      n[i].previous = NULL;
    for (i = 0; i < size; i++) {
        n[i].distance = 10000;
        n[i].previous = NULL;
    }
    
    
    source = get_pointer_to_node(1, size, n);

    //  source.distance = 0;
    source->distance = 0;

   
    
    //  while Q is not empty:

    j = 0;
    u = extract_min(q);
    while(u != NULL) {     
        printf("=== Treating node %d\n", u->own_address);
        //for each connection in u.connections
        while (j < u->number_of_connections) {
            c = u->connections[j];
            d = get_pointer_to_node(u->connections[j].destination, size, n);
            alt = u->distance + c.weight;
            printf("%d < %d", alt, d->distance);
            if (alt < d->distance) {
                printf(" (TRUE)\n");
                printf("Setting distance to: %d\n", alt);
    
                d->distance = alt;
                d->previous = u; 
            
            } else {
                printf(" (FALSE)\n");
            }
            j += 1;
        }
        j = 0;
        u = extract_min(q); 
    }
    
    free_queue(q);
}



void generate_routing_tables(struct Node* n, int size) {
    int i, destination;
    struct Node* tmp_node;
    initialize_routing_tables(n, size);
    

    for(i = 0; i < size; i++) {
        tmp_node = &n[i];
        destination = n[i].own_address;
        while (tmp_node->previous != NULL) {
            printf("Inserting hop into %d\n", i); 
            insert_hop_in_routing_table(tmp_node->previous, destination, tmp_node->own_address);
            tmp_node = tmp_node->previous;
        } 
    }
    
    tmp_node = get_pointer_to_node(1, size, n);
    

    // A hacky way to make sure that Node 1 receives messages for itself.
    insert_hop_in_routing_table(tmp_node, 1, 1);
}
