#ifndef network
#define network

int send_node(int fdsock, unsigned char* buf, int size_of_buf);
unsigned char* receive_node(int fdsock);
int create_server_socket(int base_port, int number_of_nodes);
int create_node_socket(int base_port); 

#endif
