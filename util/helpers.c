
    /*
     *
     *  Put all smaller helper functions here
     *
     */

#include <stdio.h>
#include <stdlib.h>

#include "../core/types/networktypes.h"


int get_index_of_node(int own_address, int size_of_array, struct Node *node_array) {
    int i = 0;

    while(i < size_of_array) {
        if (node_array[i].own_address == own_address) {
            return i;
        }
        i += 1;
    }

    return -1;
}

int initialize_node_connections(struct Node* node, int number_of_connections) { 
    node->number_of_connections = 0;
    node->connections = (struct Connection*) malloc(sizeof(struct Connection) * number_of_connections);
    
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
    if (n.number_of_connections > 1) {
        free(n.connections);
    }
}


int free_routing_table(struct Node node) {
    int i; 
    int size;

    size = node.rt->size_of_rt;
    for (i = 0; i < size; i++) {
        free(node.rt->hops[i]);
    }
    
    free(node.rt->hops);
    free(node.rt);
    
    return 0;
}


int free_nodes(struct Node* n, int number_of_nodes) {
    int i;

    for (i = 0; i < number_of_nodes; i++) {
        free_connections(n[i]);
        free_routing_table(n[i]);      
    } 

    free(n);

    return 0;
}


void free_node(struct Node* n) {
    int i;

    for (i = 0; i < n->number_of_connections; i++) {
        free(&(n->connections[i]));
    }

    if (n->number_of_connections > 1) {
            free(n->connections);
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
        // Surely a 100 hops should be enough?!
        initialize_routing_table(&n[i], 100);
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

int validate_connections(struct Node* n, int num_nodes) {
    int i, j, k;
    
    struct Node dest_node;


    for (i = 0; i < num_nodes; i++) {
        printf("Validating connections for node %d\n", n[i].own_address);

        for (j = 0; j < n[i].number_of_connections; j++) {
            printf("\tvalidating connection %d -> %d (%d)\n", n[i].own_address, n[i].connections[j].destination, n[i].connections[j].weight);
            
            dest_node = n[get_index_of_node(n[i].connections[j].destination, num_nodes, n)];
            
            for (k = 0; k < dest_node.number_of_connections; k++) {
                
                if (dest_node.connections[k].destination == n[i].own_address) {
                  
                    if (dest_node.connections[k].weight != n[i].connections[j].weight) {
                        printf("\t\tfound returning connection with different weight. Invalidate\n");
                        n[i].connections[j].weight = -1;
                    }
                }
            }             
        }
    }

    return 0;

}

