/*
 *
 *  Header file for q.c (Priority Queue)
 *
 *
 */

int free_queue(struct Node **q);
struct Node** initialize_queue(struct Node *n, int size_q);
struct Node* extract_min(struct Node **q);
int is_empty();
