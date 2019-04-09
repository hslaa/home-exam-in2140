/*
 *
 *  Header file for q.c (Priority Queue)
 *
 *
 */

struct Node** initialize_queue(struct Node *n, int size_q);
struct Node* extract_min(struct Node **q);
int is_empty();
