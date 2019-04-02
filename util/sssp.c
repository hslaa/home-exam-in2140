/*
 *
 *  Code for the single source shortest path (SSSP) algorithmi and helper methods
 *
 *  Implementation of Dijkstra.
 *
 *
 */
include 

struct Node extract_min(struct Node n*) {
    // Find the node with the smallest distance
    //

    // Memmove the last item of the list to them index we just
    // retrieved the node from
    
    // Free the allocated memory for the smallest node  


    

}


void sssp(struct Node n*, struct Node source) {

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
