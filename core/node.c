/*
 *
 *  Main implementation of the Node
 *
 *
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../util/logger.h"
#include "types/networktypes.h"
#include "../util/helpers.h"
#include "../util/transmission.h"

int create_test_hops(struct Node* node); 
int parse_connection(struct Node* node, char c[]);
int read_file(char* file_name);

struct Node this;


int main(int argc, char *argv[]) {
    int number_of_connections;
    int i;
    
    
    logger("DEBUG", "Node starting");

    printf("Node starting with %d arguments\n", argc);

    number_of_connections = argc-3;

   
    this.port = atoi(argv[1]);
    this.own_address = atoi(argv[2]);

    initialize_node_connections(&this, number_of_connections); 
    


    printf("Initializing node %d\n", this.own_address);
    printf("Connections (%d): \n", number_of_connections);
    for (i = 3; i < argc; i++) {
        printf("\t %s \n", argv[i]);
        parse_connection(&this, argv[i]);
    } 
    
    printf("Calling function create_test_hops() from main()\n");
    create_test_hops(&this);
    
    test_routing_tables(&this);


    if (this.own_address == 1) {
        
        printf("This is node 1.\n");
        read_file("messages_1.txt");
        // I am Node 1, I should read messages from file and send them.

    } else {
        
        printf("This is node %d.\n", this.own_address);
        // I'm _not_ Node 1, I should listen for incoming packages, and forward them.

    }

    


    free(this.connections);

}





int read_file(char* file_name) {
    FILE *fd;
    char *buf;
    
    struct packet* p;
   
    char *message;
    int destination_address;
    fd = fopen(file_name, "r");
    buf = (char *)malloc(2048);


    
    if (fd == NULL) {
        perror("read_file(): fopen failed");
        return -1;
    }

    while (fgets(buf, 1024, fd) != NULL) {
        destination_address = strtol(buf, &message, 10);
        printf("\n\n\n");        
        message[strlen(message)-1] = '\0';
        printf("message: '%s' (%zu)\n", message, strlen(message));

        p = create_packet(destination_address, this.own_address, message, strlen(message));
        serialize_packet(p, strlen(message));
        printf("\n\n\n");
    } 
    

    return 0;
}


int create_test_hops(struct Node* node) {
    int addr;
    
    addr = node->own_address;
    
    switch(addr) {
        case 1: 
            printf("Creating test hops for node %d\n", addr);
            initialize_routing_table(node, 7);
            insert_hop_in_routing_table(node, 11, 11);
            insert_hop_in_routing_table(node, 19, 11);
            insert_hop_in_routing_table(node, 103, 11);
            insert_hop_in_routing_table(node, 13, 11); 
            insert_hop_in_routing_table(node, 101, 11);
            insert_hop_in_routing_table(node, 17, 11);
            insert_hop_in_routing_table(node, 107, 11);
            break;
        case 11:
            printf("Creating test hops for node %d\n", addr);
            initialize_routing_table(node, 6);
            insert_hop_in_routing_table(node, 19, 19);
            insert_hop_in_routing_table(node, 103, 19);
            insert_hop_in_routing_table(node, 13, 13);
            insert_hop_in_routing_table(node, 101, 19); 
            insert_hop_in_routing_table(node, 17, 19);
            insert_hop_in_routing_table(node, 107, 19);
            break;

        case 13:
            printf("Creating test hops for node %d\n", addr);
            initialize_routing_table(node, 0);
            break;

        case 17:
            printf("Creating test hops for node %d\n", addr);
            initialize_routing_table(node, 0);
            break;

        case 19:
            printf("Creating test hops for node %d\n", addr);
            initialize_routing_table(node, 4);
            insert_hop_in_routing_table(node, 103, 103);
            insert_hop_in_routing_table(node, 101, 101);
            insert_hop_in_routing_table(node, 17, 101);
            insert_hop_in_routing_table(node, 107, 101);
            break;

        case 101:
            printf("Creating test hops for node %d\n", addr);
            initialize_routing_table(node, 2);
            insert_hop_in_routing_table(node, 17, 107);
            insert_hop_in_routing_table(node, 107, 107);
            break;

        case 103:
            printf("Creating test hops for node %d\n", addr); 
            initialize_routing_table(node, 0);
            break;

        case 107:
            printf("Creating test hops for node %d\n", addr);
            initialize_routing_table(node, 1);
            insert_hop_in_routing_table(node, 17, 17);
            break;
        default:
            printf("own_address %d did not match any of the cases.\n", addr);
    
    
    }
        
   
    return 0;
}

int parse_connection(struct Node* node, char c[]) {
    int i;
    char *token;
    int connection_parameters[2];

    token = strtok(c, ":");
    
    i = 0;
    while (token != NULL && i < 2) {
        connection_parameters[i] = atoi(token);
        printf("extracted token %d from %s\n", connection_parameters[i], c);
        token = strtok(NULL, ":");
        
        i += 1;
    }

    set_connection(node, connection_parameters[0], connection_parameters[1]);    

    printf("Parsing connection %s\n", c);
    
    return 0;
}
