#ifndef networktypes
#define networktypes

//struct Node;
//struct Connection;


typedef struct Graph {
    // Graph
} Graph;



typedef struct Connection {

    int weight;
    int destination;

} Connection;

typedef struct Node {
    int own_address;
    int port; // do I need this?    
    int number_of_connections;
    Connection *connections;

    int distance;

} Node;


#endif
