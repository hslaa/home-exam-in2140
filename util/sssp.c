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

#include "../core/types/networktypes.h"
#include "../util/helpers.h"

struct Node extract_min(struct Node *n, int size_of_array) {
    double min = INFINITY; // math.h
    int min_index;
    int i;
    struct Node tmp_node;
    // Find the node with the smallest distance
    while (i < size_of_array) {
        if (n[i].distance < min) { /* This might fail because nodes are initialized to INF (Dijkstra) */
            min_index = i;
            min = n[i].distance;
        }
    }
    tmp_node = n[min_index];



    // Memmove the last item of the list to them index we just
    // retrieved the node from
    memcpy(&n[min_index], &n[size_of_array], sizeof(struct Node));



    // Free the allocated memory for the smallest node  


    

}


void sssp(struct Node *n, struct Node source) {

    //  Initialize a priority queue Q.
    //  Q sorts based on node.distance

    //  for each NODE in n*
    //      n[i].distance = INF;
    //      n[i].previous = NULL;
    
    //  source.distance = 0;
    
    //  while Q is not empty:
    //      u = Q.extractMin()
    //      (removing u from Q)
    //
    //      for each connection in u.connections
    //          alt = u.distance + (u.distance + connection.weight)
    //          if alt < connection.destination.distance:
    //              connection.destination.distance = alt:
    //              connection.destination.previous = u;
    //
    //  return results. 
    //              
    //  but how should the results looook liiiike.
}



void generate_routing_tables(void) {
}
