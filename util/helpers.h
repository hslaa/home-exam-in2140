#include "../core/types/networktypes.h"

int get_index_of_node(int own_address, int size_of_array, struct Node *node_array);
struct Node* get_pointer_to_node(int own_address, int size_of_array, struct Node *node_array);
void free_connections(struct Node n);
void free_nodes(struct Node *n, int number_of_nodes);
