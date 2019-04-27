#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

#include "types/networktypes.h"
#include "../util/helpers.h"







//#include <netinet/in.h>
//#include <arpa/inet.h>


#include "../util/print_lib.h"






int parse_hops(unsigned char* data, int size_of_rt, struct Node* n);
struct Connection* parse_connections(unsigned char* data, int number_of_connections); 
int serialize_node(unsigned char* packet_buf, struct Node* n);
struct Node* deserialize_node(struct Node* n, unsigned char* packet_buf);


int serialize_node(unsigned char* packet_buf, struct Node* n) {

    char* tmp_buf; /* used to byte-by-byte copy output from sprintf to data_buf */ 
    int i, d, w;
   
    int bytes_written; 
    int total_bytes;
    int buf_size;
    
    /* declaring variables to be embedded in the serialized char array */
    uint16_t length;
    uint16_t own_address;
    uint16_t number_of_connections;
    char* connections; /* keeping the serialized connections */   
    

    /*
     *  | {HEADER} |                    {PAYLOAD}                      |
     *  ----------------------------------------------------------------
     *  |  length  | own_address | number_of_connections | connections |
     *  ---------------------------------------------------------------- 
     *    2 bytes      2 bytes           2 bytes             X bytes
     */


    /* mallocing "enough" space for serializing connections*/
    connections = (char*) malloc(1024);
    tmp_buf = (char*) malloc(1024);

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

    length = ( sizeof(uint16_t) *3 ) + total_bytes + 1;
    own_address = n->own_address;
    number_of_connections = n->number_of_connections;
     

    memcpy(&packet_buf[0], &length, sizeof(uint16_t));
    memcpy(&packet_buf[2], &own_address, sizeof(uint16_t));
    memcpy(&packet_buf[4], &number_of_connections, sizeof(uint16_t));
    memcpy(&packet_buf[6], connections, length + 1); 
    
    printf("Serialized node with own_address %d and connections %s\n", own_address, connections); 
    
    

    free(connections);
    free(tmp_buf);
    
    buf_size = ( sizeof(uint16_t) * 3 ) + total_bytes;

    printf("serialize_node: returning %d bytes as size for packet_buf\n", buf_size);
    return buf_size;
}


int serialize_routing_table(unsigned char* packet_buf, struct routing_table* rt) {
    char* tmp_buf;
    char* hops;
    int i, d, n; // counter, destination and next_hop
    int bytes_written, total_bytes;
    
    uint16_t length, size_of_rt;
    
    total_bytes = 0;
    bytes_written = 0;
    
    tmp_buf = (char*) malloc(1024);
    hops = (char*) malloc(1024);
    
    for (i = 0; i < rt->size_of_rt; i++) {
        printf("taking on hop %d\n", i);
        d = rt->hops[i]->destination;
        n = rt->hops[i]->next_hop;
        bytes_written = sprintf(tmp_buf, "%d:%d;", d, n);
        memcpy(hops + total_bytes, tmp_buf, bytes_written);
        total_bytes += bytes_written;

    }   
    hops[total_bytes] = '\0';

    length = total_bytes + 4 + 1;
    size_of_rt = (uint16_t) rt->size_of_rt;
    memcpy(&packet_buf[0], &length, sizeof(uint16_t));
    memcpy(&packet_buf[2], &size_of_rt, sizeof(uint16_t));
    memcpy(&packet_buf[4], hops, length + 1);
    
    packet_buf[length] = '\0'; 
    
    printf("serialize_routing_table()\n");
    printf("\tlength: %d\n", length);
    printf("\tsize_of_rt: %d\n", size_of_rt);
    printf("\tnon-parse hops: %s\n", &packet_buf[4]);
    
    free(tmp_buf);
    free(hops);

    return length;
} 

int deserialize_routing_table(unsigned char* packet_buf, struct routing_table* rt, struct Node* n) {
    
    unsigned char* data;
    uint16_t length;
    //int i;

    length = *((uint16_t *) &packet_buf[0]);
    rt->size_of_rt = *((uint16_t *) &packet_buf[2]);

    data = (unsigned char*) malloc(length + 1);
    strcpy((char*) data, (char*) &packet_buf[4]);

    printf("deserialized_rt:\n\n");
    printf("\t length: %d\n", length);
    printf("\t size_of_rt: %d\n", rt->size_of_rt);
    printf("\t non-parsed hops: %s\n", data);

    
    parse_hops(data, rt->size_of_rt, n);
    
    free(data);
    return 0; 

    
}

struct Node* deserialize_node(struct Node* n, unsigned char* packet_buf) {
    unsigned char* data;
    uint16_t length, data_length;
    int i;
     
    length = *((uint16_t *) &packet_buf[0]); 
    n->own_address =  *((uint16_t *) &packet_buf[2]); 
    n->number_of_connections =  *((uint16_t *) &packet_buf[4]); 
    
    printf("length: %d\n", length);  
    
    data_length = length - ( 3 * sizeof(uint16_t) );   
   
    data = (unsigned char*) malloc(data_length);
    strcpy((char*) data, (char*) &(packet_buf[6]));


    printf("deserialized_node:\n\n");
    printf("\t length: %d\n", length);
    printf("\t own_address: %d\n", n->own_address);
    printf("\t number_of_connections: %d\n", n->number_of_connections);
    printf("\t non-parsed connections: %s\n", data); 
    


    n->connections = parse_connections(data, n->number_of_connections);
    

    for (i = 0; i < n->number_of_connections; i++) { 
        printf("\t parsed connections:\n");
        printf("\t\t me -> %d (%d) \n", n->connections[i].destination, n->connections[i].weight);
    }
    
    free(data); 

    return n;

}

int parse_hops(unsigned char* data, int size_of_rt, struct Node* node) {
    int i; 
    //struct routing_table* rt;
    char* hop_token; 
    struct hop* hops;
    
    //rt = (struct routing_table*) malloc(sizeof(struct routing_table));

    printf("==== Trying to parse string: '%s'\n", data);

    struct connection_string {
        char* string;
    };
    
    struct connection_string* c_strings;
    c_strings = (struct connection_string *) malloc( sizeof(c_strings) * size_of_rt);
    

    
    i = 0;   
    hop_token = strtok((char*) data, ";");
    
    while (hop_token != NULL) {
        c_strings[i].string = malloc(strlen(hop_token) + 1);
        printf("==== hop_token: %s\n", hop_token);
        if (hop_token == NULL) {
           perror("possible malformed hop string"); 
        }

        strcpy(c_strings[i].string, hop_token);
       
        hop_token = strtok(NULL, ";");
        
        i += 1;
    }
    

    hops = (struct hop*) malloc(sizeof(struct hop) * size_of_rt);
    printf("==== Allocating space for %d hops\n", size_of_rt);
    for (i = 0; i < size_of_rt; i++) {
        
        printf("trying to decode c_strings[%d]: '%s'\n", i, c_strings[i].string);     
        hops[i].destination = atoi(strtok(c_strings[i].string, ":")); 
        hops[i].next_hop = atoi(strtok(NULL, ":"));
        
        free(c_strings[i].string);

        printf("extracted and inserted %d and %d from hop string\n", 
                    hops[i].destination,
                    hops[i].next_hop);

        insert_hop_in_routing_table(node, hops[i].destination, hops[i].next_hop);
    }
    
    free(c_strings);
    free(hops); 
  
    return 0;
}

struct Connection* parse_connections(unsigned char* data, int number_of_connections) {
    int i;
    struct Connection* connections;
    char *conn_token; /* used to split the connections */

    printf("==== Trying to parse string: '%s'\n", data);

    struct connection_string {
        char* string;
    };
    
    struct connection_string* c_strings;
    c_strings = (struct connection_string *) malloc( sizeof(c_strings) * number_of_connections);
    

    
    i = 0;   
    conn_token = strtok((char*) data, ";");
    
    while (conn_token != NULL) {
        c_strings[i].string = malloc(strlen(conn_token) + 1);
        printf("==== conn_token: %s\n", conn_token);
        if (conn_token == NULL) {
           perror("possible malformed connection string"); 
        }

        strcpy(c_strings[i].string, conn_token);
       
        conn_token = strtok(NULL, ";");
        
        i += 1;
    }
    

    connections = (struct Connection*) malloc(sizeof(struct Connection) * number_of_connections);
    printf("==== Allocating space for %d connections\n", number_of_connections);
    for (i = 0; i < number_of_connections; i++) {
        
        printf("trying to decode c_strings[%d]: '%s'\n", i, c_strings[i].string);     
        connections[i].destination = atoi(strtok(c_strings[i].string, ":")); 
        connections[i].weight = atoi(strtok(NULL, ":"));
        
        free(c_strings[i].string);

        printf("extracted and inserted %d and %d from connection string\n", 
                    connections[i].destination,
                    connections[i].weight);
    }

    free(c_strings);
    
    return connections; 
    
}

int deserialize_packet(struct packet* p, unsigned char *buf); 
 

struct packet* create_packet(uint16_t destination_address, uint16_t source_address, unsigned char* message, int message_length) {
    struct packet* p;
    uint16_t packet_length = sizeof(uint16_t)*3 + message_length;
    
    p = malloc(sizeof(struct packet));
    
    p->packet_length = htons(packet_length);
    p->destination_address = htons(destination_address);
    p->source_address = htons(source_address);  
  
    memcpy(&(p->message), message, message_length+1);

    return p;
}

unsigned char* serialize_packet(struct packet* p, int message_length) {
    unsigned char *buf;
    uint16_t  length;

    //buf = malloc(sizeof(struct packet));
    
    length = (sizeof(uint16_t) * 3) + message_length + 1;
    buf = malloc(length);
    
    length = htons(length);

    printf("Mallocing %d bytes for serialization_buffer\n", length);
    memcpy(&(buf[0]), &(length), sizeof(uint16_t));    
    memcpy(&(buf[2]), &(p->destination_address), sizeof(uint16_t));    
    memcpy(&(buf[4]), &(p->source_address), sizeof(uint16_t));     
    memcpy(&(buf[6]), p->message, message_length); // + 1 
    
     
    buf[ntohs(length)-1] = '\0';
    
    return buf;
}

int deserialize_packet(struct packet* p, unsigned char *buf) {
 
    uint16_t message_length;



    memcpy(&p->packet_length, &(buf[0]), sizeof(uint16_t)); 
    memcpy(&p->destination_address, &(buf[2]), sizeof(uint16_t));
    memcpy(&p->source_address, &(buf[4]), sizeof(uint16_t));
    
    p->packet_length = ntohs(p->packet_length); 
    p->destination_address = ntohs(p->destination_address); 
    p->source_address = ntohs(p->source_address); 


    message_length = p->packet_length;
    printf("deserialize_packet: trying to deserialize message of packet with length %d\n", p->packet_length);   
    
    printf("trying to memcpy(p->message, &(buf[6]), %d) on buffer of size 2048(?)\n", message_length); 
    memcpy(p->message, &(buf[6]), message_length);
    
    return 0; 
        

}









