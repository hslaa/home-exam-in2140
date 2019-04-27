/*
 *
 *  Main implementation of the routing_server
 *
 *
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>



#include "../util/sssp.h"

#include "../util/print_lib.h"
#include "types/networktypes.h"
#include "../util/helpers.h"
#include "network.h"
#include "protocol.h"


struct Node* create_test_nodes();
int test_sssp(struct Node *n, int size);

int insert_in_sockets(int own_address, int socket, int number_of_sockets, struct node_socket* ns); 
int free_routing_tables(struct Node *n, int size);
int test_routing_tables(struct Node* node); 
int create_routing_tables(struct Node *n, int size); 
int is_node_on_shortest_path(struct Node* destination, struct Node* intermediate);
int print_routing_tables(struct Node* n, int size);
int create_socket(int base_port, int number_of_nodes);
struct Node* receive_nodes(int sockfd, int number_of_nodes);
int send_routing_tables(struct Node* n, int size); 


// remembers which node listens on which sockets
struct node_socket* sockets;



int main(int argc, char *argv[]) {
    int sockfd;
    int base_port;
    int num_nodes;
    int i;

    if (argc < 3) {
        printf("usage: ./routing_server <base port> <number of nodes>\n");
        exit(EXIT_FAILURE);
    }
        
    base_port = atoi(argv[1]);
    num_nodes = atoi(argv[2]);
    
    sockfd = create_server_socket(base_port, num_nodes);

    if (sockfd < 0) {
        exit(EXIT_FAILURE);
    }
 
     
    struct Node* nodes = receive_nodes(sockfd, num_nodes);   
    

    validate_connections(nodes, num_nodes);

    test_sssp(nodes, num_nodes);  

    
    generate_routing_tables(nodes, num_nodes);
     
    send_routing_tables(nodes, num_nodes);
    
    close(sockfd);

    for (i = 0; i < num_nodes; i++) {
        close(sockets[i].sockfd);
    }

    free(sockets);
    
    printf("/// CALLING free_nodes FROM MAIN THREAD ///\n");
    free_nodes(nodes, num_nodes);
    return 0;
}


int print_routing_tables(struct Node* n, int size) {
    int i;
    
    printf("Generated routing tables:\n");
   
    
    for (i = 0; i < size; i++) {
        printf("=== Node %d ===\n", n[i].own_address);
        printf("\t rt_size: %d\n", n[i].rt->size_of_rt);
    }
    return 0;

}

int send_routing_tables(struct Node* n, int size) {
    int i, length;
    unsigned char* packet_buf;
    for (i = 0; i < size; i++) {

        packet_buf = (unsigned char*) malloc(1024);
        length = serialize_routing_table(packet_buf, n[i].rt);        

        printf("sending routing table to %d on socket %d\n", 
                sockets[i].own_address,
                sockets[i].sockfd);
        
        send_node(sockets[i].sockfd, packet_buf, length);
        free(packet_buf); 
    }        
    
    return 0;
}




struct Node* receive_nodes(int sockfd, int number_of_nodes) {
    int nodes_received, node_socket;
    
    unsigned char* testbuf;
    struct sockaddr_storage nodeaddr;
    socklen_t addr_len;

    nodes_received = 0;
     
    struct Node *nodes = malloc(sizeof(struct Node) * number_of_nodes);
    sockets = malloc(sizeof(struct node_socket) * number_of_nodes);
    

    while (nodes_received < number_of_nodes) {
        addr_len = sizeof(nodeaddr);
        node_socket = accept(sockfd, (struct sockaddr *)&nodeaddr, &addr_len);
                
        testbuf = receive_node(node_socket);
        deserialize_node(&nodes[nodes_received], testbuf);
        insert_in_sockets(nodes[nodes_received].own_address, node_socket, nodes_received, sockets);
        
        printf("Added new node to nodes\n"); 
        
        nodes_received += 1;
        free(testbuf); 
        
        printf("finished processing node %d out of %d\n", nodes_received, number_of_nodes);
    }

    int i; 

    for (i = 0; i < nodes_received; i++) {
        printf("node %d waits on socket %d\n", sockets[i].own_address, sockets[i].sockfd);
    }
    
 

    return nodes;
} 

int insert_in_sockets(int own_address, int socket, int number_of_sockets, struct node_socket* ns) {
    ns[number_of_sockets].own_address = own_address;
    ns[number_of_sockets].sockfd = socket;
    number_of_sockets += 1; 
    return number_of_sockets;
}

int test_sssp(struct Node *n, int size) {
    int i;  
    int j;
    int pathlen;
    struct Node* tmpNode;
    sssp(n, size);
    

    
    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            pathlen = is_node_on_shortest_path(&n[i], &n[j]);

            print_weighted_edge(n[i].own_address, n[j].own_address, pathlen);
        }
    }
    
    for (i = 0; i < size; i++) {
        tmpNode = &n[i];
        printf("Path backwards from Node %d\n", tmpNode->own_address);
   
        while (tmpNode->previous != NULL) {
            printf(" %d --> ", tmpNode->own_address);
            tmpNode = tmpNode->previous;
        }
        printf("1 (%d)\n", n[i].distance);
    }

    return 0;
}

int is_node_on_shortest_path(struct Node* destination, struct Node* intermediate) {
    int hit_intermediate = 0;
    int pathlen = destination->distance;
    struct Node* tmp_node;

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
