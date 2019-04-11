/*
 *
 *  Main implementation of the routing_server
 *
 *
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../util/sssp.h"
#include "../util/logger.h"
#include "../util/print.h"
#include "../util/print_lib.h"
#include "types/networktypes.h"
#include "../util/helpers.h"

struct Node* create_test_nodes();
int test_sssp(struct Node *n, struct Node source, int size);

int free_routing_tables(struct Node *n, int size);
int test_routing_tables(struct Node* node); 
int create_routing_tables(struct Node *n, int size); 
int is_node_on_shortest_path(struct Node* destination, struct Node* intermediate);

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
    

    test_sssp(testnodes, testnodes[0], 8);
    
    create_routing_tables(testnodes, 8);
    test_routing_tables(&testnodes[6]);
    free_routing_tables(testnodes, 8);
    free_nodes(testnodes, 8); 

    return 0;
}

int test_sssp(struct Node *n, struct Node source, int size) {
    int i;  
    int j;
    int pathlen;
    struct Node* tmpNode;
    sssp(n, source, size);
    
    printf("==== test_sssp() ====\n");
    
    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            pathlen = is_node_on_shortest_path(&n[i], &n[j]);
            logger("DEBUG", "Running print_weighted_edge()");
            print_weighted_edge(n[i].own_address, n[j].own_address, pathlen);
        }
    }
    
    for (i = 0; i < size; i++) {
        tmpNode = &n[i];
        printf("Path backwards from Node %d\n", tmpNode->own_address);
   
        while (tmpNode->previous != NULL) {
            printf(" %d --> ", tmpNode->own_address);
            
            //cost += tmpNode->distance;
            tmpNode = tmpNode->previous;
        }
        printf("1 (%d)\n", n[i].distance);
    }

    return 0;
}


int initialize_routing_table(struct Node *n, int size) {
    int i;
    printf("starting initialize_routing_table with size %d\n", size);
    for (i = 0; i < size; i++) {    
        n[i].rt = malloc( sizeof ( struct routing_table ) );
        n[i].rt->hops = malloc( sizeof( struct hop** ) * size );
        n[i].rt->size_of_rt = 0;
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
    initialize_routing_table(n, size);
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

int is_node_on_shortest_path(struct Node* destination, struct Node* intermediate) {
    int hit_intermediate = 0;
    int pathlen = destination->distance;
    struct Node* tmp_node;
    logger("DEBUG", "running is_node_on_shortest_path"); 
    tmp_node = destination;
    while(tmp_node->previous != NULL) {
        
        if (tmp_node->own_address == intermediate->own_address) {
            hit_intermediate = 1;   
        }
             
        tmp_node = tmp_node->previous;
    }
 
    if (hit_intermediate) {
        pathlen = -1;
    }
    
    printf("Returning %d for pathlen (destination node %d has distacne %d from node 1", 
            pathlen,
            destination->own_address,
            destination->distance
          );

    return pathlen;
}
