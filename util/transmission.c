#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../core/types/networktypes.h"
#include "print_lib.h"

int deserialize_packet(unsigned char *buf, int message_length);



struct packet* create_packet(uint16_t destination_address, uint16_t source_address, unsigned char* message, int message_length) {
    struct packet* p;
    uint16_t packet_length = sizeof(destination_address) + sizeof(source_address) + message_length;
    p = malloc(sizeof(struct packet));
    /* 
    printf("Creating packet with:\n");

    printf("\t length: %d (message length: %zu)\n", packet_length, strlen(message)); 
    printf("\t destination address: %d\n", destination_address);
    printf("\t source address: %d\n", source_address);
   
    */
    //printf("[CREATE_PACKET] message: '%s' (%d)\n", message, message_length);
    p->packet_length = htons(packet_length);
    p->destination_address = htons(destination_address);
    p->source_address = htons(source_address);  
  
    memcpy(&(p->message), message, message_length+1);
    //printf("[CREATE_PACKET] memcpy'd '%s' into packet\n", p->message);


    return p;
}

int serialize_packet(struct packet* p, int message_length) {
    unsigned char *buf;
    
    buf = malloc(sizeof(struct packet));
    printf("Mallocing %zu bytes for serialization_buffer\n", sizeof(struct packet));
    memcpy(&(buf[0]), &(p->packet_length), sizeof(uint16_t));    
    memcpy(&(buf[2]), &(p->destination_address), sizeof(uint16_t));    
    memcpy(&(buf[4]), &(p->source_address), sizeof(uint16_t));     
    memcpy(&(buf[6]), p->message, message_length + 1);
    //printf("[SERIALIZE_PACKET] trying to memcpy message %s (%d)into buf[6]\n", p->message, message_length);
    deserialize_packet(buf, message_length);
    
    print_pkt(buf);
    return 0;
}

int deserialize_packet(unsigned char *buf, int message_length) {
    struct packet* p;
    p = (struct packet*)malloc(sizeof(struct packet));

    memcpy(&p->packet_length, &(buf[0]), sizeof(uint16_t)); 
    memcpy(&p->destination_address, &(buf[2]), sizeof(uint16_t));
    memcpy(&p->source_address, &(buf[4]), sizeof(uint16_t));
    memcpy(p->message, &(buf[6]), message_length + 1);
    printf("Deserialized packet:\n");
    printf("\tpacket_length: %d\n", ntohs(p->packet_length));
    printf("\tdestination_address: %d\n", ntohs(p->destination_address));
    printf("\tsource_address: %d\n", ntohs(p->source_address));   
    printf("\tmessage: %s\n", p->message); 
    
    return 0;
        

}








