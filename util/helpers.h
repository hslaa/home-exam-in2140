#include "../core/types/networktypes.h"

int get_index_of_node(int own_address, int size_of_array, struct Node *node_array);
struct Node* get_pointer_to_node(int own_address, int size_of_array, struct Node *node_array);
void free_connections(struct Node n);
void free_nodes(struct Node *n, int number_of_nodes);
struct Node* create_test_nodes();
int set_connection(struct Node* node, int dst, int weight);
int initialize_node_connections(struct Node* node, int number_of_connections);

int free_routing_table(struct Node node); 
int free_hops(struct Node* node, int size); 
int initialize_routing_table(struct Node*n, int size);
int initialize_routing_tables(struct Node* n, int size);
int insert_hop_in_routing_table(struct Node* node, int dst, int n_hop);
int free_routing_tables(struct Node *n, int size);
int test_routing_tables(struct Node* node);
int create_routing_tables(struct Node *n, int size);
