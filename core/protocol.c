#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "types/networktypes.h"

unsigned char* serialize_node(struct Node* n);
struct Node* deserialize_node(unsigned char* packet_buf);
struct Connection* parse_connections(unsigned char* data, int number_of_connections);

int main() {
    
    struct Node test_node;
    unsigned char* serialized_node;
    struct Node* deserialized_node;

    test_node.own_address = 11;
    test_node.number_of_connections = 2;
    test_node.connections = malloc(sizeof(struct Connection) * 2);

    test_node.connections[0].destination = 13;
    test_node.connections[0].weight = 7;

    test_node.connections[1].destination = 19;
    test_node.connections[1].weight = 2;

    serialized_node = serialize_node(&test_node);
    deserialized_node = deserialize_node(serialized_node);

   
    free(deserialized_node);
    free(test_node.connections);
  
    return 0;
}

unsigned char* serialize_node(struct Node* n) {

    unsigned char* tmp_buf; /* used to bit-by-bit copy output from sprintf to data_buf */
    unsigned char* packet_buf; /* buffer to contain all the serialized data */
    int i, d, w;
   
    int bytes_written; 
    int total_bytes;

    /* declaring variables to be embedded in the serialized char array */
    uint16_t length;
    uint16_t own_address;
    uint16_t number_of_connections;
    unsigned char* connections; /* keeping the serialized connections */   
    

    /*
     *  | {HEADER} |                    {PAYLOAD}                      |
     *  ----------------------------------------------------------------
     *  |  length  | own_address | number_of_connections | connections |
     *  ---------------------------------------------------------------- 
     *    2 bytes      2 bytes           2 bytes             X bytes
     */


    /* mallocing "enough" space for serializing connections*/
    connections = (unsigned char*) malloc(1024);
    tmp_buf = (unsigned char*) malloc(1024);

    bytes_written = 0;
    total_bytes = 0;

    for (i = 0; i < n->number_of_connections; i++) {
        
        /* for every connection in a struct Node*/
        d = n->connections[i].destination;
        w = n->connections[i].weight;
        
        /* copies connection data on the format destination:weight; into tmp_buf */
        bytes_written = sprintf(tmp_buf, "%d:%d;", d, w);

        memcpy(connections + total_bytes, tmp_buf, bytes_written);
        total_bytes += bytes_written;
    }
    
    /* making sure to set a null byte after the last character we copied to data_buf */
    connections[total_bytes] = '\0';

    length = total_bytes + 1;
    own_address = n->own_address;
    number_of_connections = n->number_of_connections;
    
    packet_buf = (unsigned char*) malloc(1024);

    memcpy(&packet_buf[0], &length, sizeof(uint16_t));
    memcpy(&packet_buf[2], &own_address, sizeof(uint16_t));
    memcpy(&packet_buf[4], &number_of_connections, sizeof(uint16_t));
    memcpy(&packet_buf[6], connections, length); 
    
  
    
 
    free(connections);
    free(tmp_buf);

    return packet_buf;
}


struct Node* deserialize_node(unsigned char* packet_buf) {
    struct Node* n;
    unsigned char* data;
    int length;
    
    n = (struct Node*) malloc(sizeof(struct Node));
    
    length = *((uint16_t *) &packet_buf[0]); 
    n->own_address =  *((uint16_t *) &packet_buf[2]); 
    n->number_of_connections =  *((uint16_t *) &packet_buf[2]); 
    printf("length: %d\n", length);  
    
    
    data = (unsigned char*) malloc(length +1);
    strcpy(data, &(packet_buf[6]));


    printf("deserialized_node:\n\n");
    printf("\t length: %d\n", length);
    printf("\t own_address: %d\n", n->own_address);
    printf("\t number_of_connections: %d\n", n->number_of_connections);
    printf("\t non-parsed connections: %s\n", data); 
    
    parse_connections(data, n->number_of_connections);

    free(data);
    free(packet_buf);
     
    return n;

}

struct Connection* parse_connections(unsigned char* data, int number_of_connections) {
    int i;
    char *conn_token; /* used to split the connections */
    
    struct connection_string {
        unsigned char string[64];
    }
    
    struct connection_string* c_strings;
    c_strings = (struct connection_string *) malloc(sizeof(c_strings) * number_of_connections);
    

    conn_token = strtok_r(data, ";", &edge_token);
    
    while (conn_token != NULL) {
        
    }

}




















/*
struct node_packet* create_node_packet(struct Node* n) {
    struct node_packet* np;
    unsigned char* data_buf;
    unsigned char* tmp_buf; 

    int i, d, w;
    int total_bytes;
    int bytes_written;

    np = (struct node_packet*) malloc(sizeof(n));

    data_buf = (unsigned char*) malloc(1024);

    tmp_buf = (unsigned char*) malloc(1024); 


    bytes_written = 0;
    total_bytes = 0;
    
    // Connections are written into a buffer in the format
    // destination:weight;destination:weight;
    for (i = 0; i < n->number_of_connections; i++) { 
        
        d = n->connections[i].destination;
        w = n->connections[i].weight;
        
        bytes_written = sprintf(tmp_buf, "%d:%d;", d, w);
        
        memcpy(data_buf + total_bytes , tmp_buf, bytes_written);
        
        total_bytes += bytes_written;
    }

    data_buf[total_bytes] = '\0';
    
    np->own_address = n->own_address;
    np->length_of_data = total_bytes;
    
    np->data = (char *) malloc(strlen(data_buf) + 1);
    strcpy(np->data, data_buf);
}
*/
/*
struct node_packet* deserialize_node_packet(unsigned char* buf) {
    struct node_packet* np;
    int length_of_data;

    np = (struct node_packet*) malloc(sizeof(buf));

    memcpy(&np->own_address, &(buf[0]), sizeof(uint16_t));
    memcpy(&np->length_of_data, &(buf[2]), sizeof(uint16_t));

    return np;

}

*/
