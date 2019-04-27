#ifndef protocol
#define protocol

int serialize_node(unsigned char* packet_buf, struct Node* n);
struct Node* deserialize_node(struct Node* n, unsigned char* packet_buf);
struct Connection* parse_connections(unsigned char* data, int number_of_connections);

int deserialize_routing_table(unsigned char* packet_buf, struct routing_table* rt, struct Node* n);
int serialize_routing_table(unsigned char* packet_buf, struct routing_table* rt);


int deserialize_packet(struct packet* p, unsigned char *buf);
struct packet* create_packet(uint16_t destination_address, uint16_t source_address, char* message, int message_length);
unsigned char* serialize_packet(struct packet* p, int message_length);
#endif
