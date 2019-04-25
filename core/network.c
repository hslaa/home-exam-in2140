#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "types/networktypes.h"

int send_node(int fdsock, unsigned char* buf, int size_of_buf) {
    int len_bytes;
   
    len_bytes = size_of_buf + 1;
    
    // First send the length... 
    printf("send_node: preparing to send buf of size %d bytes\n", len_bytes);
    send(fdsock, &len_bytes, sizeof(int), 0);
    
    // then send the actual data..
    send(fdsock, buf, len_bytes, 0); 
    
    return 0; 

}


unsigned char* receive_node(int nodesocket) {
    int len_bytes; 
    unsigned char* node_buf;
    
    // first receive the length
    recv(nodesocket, &len_bytes, sizeof(int), 0);
    
    // then malloc space accordingly
    printf("receive_node: mallocing %d bytes for node_bud\n", len_bytes);
    node_buf = (unsigned char*) malloc(len_bytes + 1);
    
    // and then receive the whole buffer
    recv(nodesocket, node_buf, len_bytes+1, 0);
    
    return node_buf;
}

int create_node_socket(int base_port) {
    int sockfd;
    struct sockaddr_in serveraddr;

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create node socket");
        return -1;
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(base_port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ( (connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr_in))) == -1) {
        perror("failed to connect to server");
        return -1;
    }

    return sockfd;

}

int create_server_socket(int base_port, int number_of_nodes) {
    int sockfd;
    struct sockaddr_in serveraddr;

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create server socket");
        return -1;
    }

    memset(&serveraddr, 0, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(base_port);

    if ( bind(sockfd, (const struct sockaddr*) &serveraddr, sizeof(serveraddr)) < 0) {
        perror("bind failed");
        return -1;
    }

    if ( listen(sockfd, number_of_nodes) < 0) {
        perror("listen failed");
        return -1;
    }

    return sockfd;

}
