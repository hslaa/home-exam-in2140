#ifndef networktypes
#define networktypes

#include <stdint.h>

//struct Node;
//struct Connection;

/*
typedef struct Graph {
    // Graph
} Graph;
*/
#define RIDICULOUSLY_MUCH_SPACE = 1024;

typedef struct Connection {

    int weight;
    int destination;

} Connection;

typedef struct Node {
    int own_address;
    int port; // do I need this?    
    int number_of_connections;
    Connection *connections;

    // For SSSP
    int distance;
    struct Node* next;
    struct Node* previous;

    // For routing table 
    struct routing_table* rt;

} Node;

typedef struct hop {
    int destination;
    int next_hop;
} hop;

typedef struct routing_table {
    int size_of_rt;
    struct hop** hops;
} routing_table;



typedef struct packet {
    uint16_t packet_length;
    uint16_t destination_address;
    uint16_t source_address;
    unsigned char message[2048]; 
} packet;

typedef struct node_socket {
    int own_address;
    int sockfd;
} node_socket;


#endif
