#ifndef networktypes
#define networktypes

//struct Node;
//struct Connection;

/*
typedef struct Graph {
    // Graph
} Graph;
*/


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

#endif
