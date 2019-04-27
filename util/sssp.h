#include "../core/types/networktypes.h"


void sssp(struct Node *n, int size);
void generate_routing_tables(struct Node* n, int size);

int free_queue(struct Node **q);
struct Node** initialize_queue(struct Node *n, int size_q);
struct Node* extract_min(struct Node **q);
int is_empty();


