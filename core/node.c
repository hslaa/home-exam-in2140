/*
 *
 *  Main implementation of the Node
 *
 *
 *
 */
#include <stdlib.h>
#include <stdio.h>

#include "../util/logger.h"
#include "types/networktypes.h"

int main(int argc, char *argv[]) {
    
    struct Node this;
    this.port = atoi(argv[1]);
    this.own_address = atoi(argv[2]);
    this.connections = malloc(sizeof(struct Connection)*(argc-3));
    logger("DEBUG", "Node starting");
    free(this.connections);
}
