#ifndef protocol
#define protocol

int serialize_node(unsigned char* packet_buf, struct Node* n);
struct Node* deserialize_node(struct Node* n, unsigned char* packet_buf);
struct Connection* parse_connections(unsigned char* data, int number_of_connections);

int deserialize_routing_table(unsigned char* packet_buf, struct routing_table* rt, struct Node* n);
int serialize_routing_table(unsigned char* packet_buf, struct routing_table* rt);

#endif
