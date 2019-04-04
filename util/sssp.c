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




int main() {
    
    printf("hei"); 

    return 0;
}

void sssp(struct Node *n, struct Node source, int size) {
    struct Node** q;
    struct Node* u;
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
        n[i].distance = INFINITY;
        n[i].previous = NULL;
    }
    
    
    
    //  source.distance = 0;
    source.distance = 0;

    
    //  while Q is not empty:
        u = extract_min(q); 
        while(u != NULL) {
            
            //for each connection in u.connections
            while (j < u->number_of_connections) {
                c = u->connections[j];
                alt = u->distance + c.weight;
                if (alt < c.destination->distance) {
                    c.destination->distance = alt;
                    c.destination->previous = u; 
                }
                j += 1;
            }
            j = 0;
            u = extract_min(q);
        }
    //
    //  return results. 
    //              
    //  but how should the results looook liiiike.
}



void generate_routing_tables(void) {
}
