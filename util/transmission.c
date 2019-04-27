#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../core/types/networktypes.h"
#include "print_lib.h"



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

    // Magic number 5 comes from 3*2 - 1 for the \0-byte
    message_length = p->packet_length;
    printf("deserialize_packet: trying to deserialize message of packet with length %d\n", p->packet_length);   
    
    printf("trying to memcpy(p->message, &(buf[6]), %d) on buffer of size 2048(?)\n", message_length); 
    memcpy(p->message, &(buf[6]), message_length);
    
    return 0; 
        

}









