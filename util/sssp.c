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
#include <stdlib.h>

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
    
    for (i = 0; i < size; i++) {
        n[i].distance = 10000;
        n[i].previous = NULL;
    }
     
    source = get_pointer_to_node(1, size, n);

    //  source.distance = 0;
    source->distance = 0;


    j = 0;
    u = extract_min(q);
    while(u != NULL) {     
        printf("=== Treating node %d\n", u->own_address);
        //for each connection in u.connections
        while (j < u->number_of_connections) {
            c = u->connections[j];
            
            if (c.weight == -1) {
                printf("u->connections[%d].destination == -1\n", j);
                j+=1;
                continue;
            }

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
/*
 *
 *  helper function to perform SSSP 
 *
 *
 */
int size_of_q;


struct Node** initialize_queue(struct Node *n, int size_q) {
    int i;
    struct Node** q;
    size_of_q = size_q;
    q = malloc(sizeof(struct Node*) * size_of_q);
    
    for (i = 0; i < size_of_q; i++) {
        printf("Inserting node %d into PriorityQueue with distance\n", n[i].own_address);
        q[i] = &n[i];
        printf("(%d)\n", q[i]->own_address);
    }


    return q;

}

int is_empty() {
    return size_of_q;
}

struct Node* extract_min(struct Node **q) {
    int i;
    int min_distance = 100000;
    int min_index = 0;

    printf("START extract_min()\n"); 
    struct Node *ret_node = NULL;

    if(size_of_q == 0) {
        printf("size_of_q == 0: returning NULL\n");
        return NULL;
    }

    i = 0;
    while(i < size_of_q) {
        printf("\n\tchecking element %d\n", i);
        if (q[i] == NULL) {
            printf("\t\t element %d was NULL\n", i);
            i += 1;
            continue;
        }

        if (q[i]->distance < min_distance) {
            printf("\t\t element %d replaces %d as the smallest element\n", i, min_index);
            ret_node = q[i];
            min_distance = ret_node->distance;
            min_index = i;
        }
        i += 1; 
    }
    q[min_index] = NULL;
    printf("END extract_min()\n"); 
    
    return ret_node;     
}

int free_queue(struct Node **q) {
    int i;

    for (i = 0; i < size_of_q; i++) {
        free(q[i]);
    }
    free(q);
    printf("Finished freeing %d queue elements", i);

    return 0;
}
