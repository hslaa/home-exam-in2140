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

void sssp(struct Node *n, struct Node source, int size);
void generate_routing_tables(void);


void sssp(struct Node *n, struct Node source, int size) {
    struct Node** q;
    struct Node* u;
    struct Node* d;
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
    
    
    
    //  source.distance = 0;
    n[0].distance = 0;

    // Does this remove the unused parameter warning?
    if (source.distance == 0) {
        
    }
    
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



void generate_routing_tables(void) {
}
