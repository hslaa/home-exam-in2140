/*
 *
 *  Main implementation of the Node
 *
 *
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


#include "types/networktypes.h"
#include "protocol.h"
#include "network.h"
#include "../util/print_lib.h"
#include "../util/logger.h"
#include "../util/helpers.h"
#include "../util/transmission.h"

int receive_packet(int fdsock); 
int send_packet(int destination_address, unsigned char* packet, int length); 
int get_next_hop(int destination);
int create_receiving_socket(int base_port, int own_address); 
int create_test_hops(struct Node* node); 
int parse_connection(struct Node* node, char c[]);
int process_file(char* file_name);
int handle_packet(unsigned char *packet);

int base_port;

struct Node this;
int recv_socket;

int main(int argc, char *argv[]) {
    int number_of_connections;
    int i;
    unsigned char packet[2048];

    int recv_size;
    
    logger("DEBUG", "Node starting");

    printf("Node starting with %d arguments\n", argc);

    number_of_connections = argc - 3;

   
    
    this.own_address = atoi(argv[2]);
    base_port = atoi(argv[1]);  

    
    int nodesocket = create_node_socket(base_port);
    
    if (nodesocket < 0) { 
        exit(-2);
    }
    
    
    initialize_node_connections(&this, number_of_connections); 
    


    printf("Initializing node %d\n", this.own_address);
    printf("Connections (%d): \n", number_of_connections);
    for (i = 3; i < argc; i++) {
        printf("\t %s \n", argv[i]);
        parse_connection(&this, argv[i]);
    } 
   
    unsigned char* this_buf;
    int size_of_buf;
    this_buf =  malloc(2048);
    
    size_of_buf = serialize_node(this_buf, &this);

    send_node(nodesocket, this_buf, size_of_buf);
    
    free(this_buf); 
    
    this_buf = receive_node(nodesocket);
    
    struct routing_table* rt = (routing_table*) malloc(sizeof(rt)); 
    
    initialize_routing_table(&this, 10); 
    
    deserialize_routing_table(this_buf, rt, &this); 
    
    free(this_buf); 
    
    if (this.own_address == 1) {
        
    
        
        recv_socket = create_receiving_socket(base_port, this.own_address);
        

        if (recv_socket == -1) {
            perror("had some trouble opening socket");
            exit(-1);
        }  
        
        sleep(1);

        process_file("data.txt");
        


    } else {
        recv_socket = create_receiving_socket(base_port, this.own_address);
 
        if (recv_socket == -1) {
            exit(-1);
        }

        while(1) {
            
            recv_size = recv(recv_socket, (char *)packet, 2048, MSG_WAITALL);
            packet[recv_size] = '\0';
            
            if (handle_packet(packet) == -1) {
                break;
            } 
        }
        close(recv_socket); 
    }

    /* Freeing memory */

    free(rt); 
    free_routing_table(this); 
    free_connections(this);
  
    printf("Quitting...\n");

    return 0;

}

int receive_packet(int fdsock) {
    int recv_size;
    unsigned char packet[2048];

    recv_size = recv(fdsock, (char *)packet, 2048, 0);
         
    printf("Received size was %d\n", recv_size);

    if (recv_size > 0) {
        packet[recv_size] = '\0';
        handle_packet(packet);
        return 0;
    }
    
    if (recv_size == -1) {
       perror("receive_packet"); 
    }
    return -1;
}

int handle_packet(unsigned char* packet) {
    struct packet* p; 
    //printf("Node received: %s\n", packet);
    p = (struct packet*) malloc(sizeof(struct packet)); 
    deserialize_packet(p, packet);

    printf("received packet with destination %d\n", p->destination_address);

    if (p->destination_address == this.own_address) {
        print_received_pkt(this.own_address, packet);
        
        if (!strcmp((char*) p->message, " QUIT")) { 
            free(p);
            return -1; 
        }

    } else {

        print_forwarded_pkt(this.own_address, packet);
        send_packet(p->destination_address, packet, p->packet_length);
    }     
    
    free(p); 
  
    return 0;
}

int send_packet(int destination_address, unsigned char* packet, int length) {
    int sockfd;
    int port;
    struct sockaddr_in destaddr;
    
    port = base_port + get_next_hop(destination_address);
    
    if ( ( sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("create_send_socket failed");
        return -1;
    }

    //printf("This packet should be sent to node %d\n", port);

    memset(&destaddr, 0, sizeof(destaddr));

    destaddr.sin_family = AF_INET;
    destaddr.sin_port = htons(port);
    //destaddr.sin_addr.s_addr = INADDR_ANY; /* remove this maybe???? since wil not recv*/
    
    //sendto(sockfd, packet, length, MSG_CONFIRM, NULL, len);
    printf("Sending packet with length %d (pointer: %p) to localhost:%d on socketfd %d\n",
            length, packet, port, sockfd); 
    
    sendto(sockfd, packet, length, MSG_CONFIRM, (const struct sockaddr *) &destaddr, sizeof(destaddr)); 
    printf("sent packet....\n\n\n\n");
    close(sockfd);
    
    return 0;    
}

int get_next_hop(int destination) {
    int i;
    int size;

    size = this.rt->size_of_rt;
    printf("searching for next_hop: \n");
    for (i = 0; i < size; i++) {
        printf("<%d:%d>?", this.rt->hops[i]->destination, this.rt->hops[i]->next_hop);
        printf("'%d' == '%d'?\n", this.rt->hops[i]->destination, destination);
        if (this.rt->hops[i]->destination == destination) {
            printf(" YES!\n");
            printf("returning %d as next hop\n", this.rt->hops[i]->next_hop);
            return this.rt->hops[i]->next_hop;
        }
        printf(" NO!\n");
    }
    printf("Couldnt find any hop :(\n");
    return -1;

}

int create_receiving_socket(int base_port, int own_address) {
    int sockfd;
    int port;
    struct sockaddr_in nodeaddr;
     
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failed in creating socket.");
        return -1;
    }
    
    /* Making sure the struct is clean */
    memset(&nodeaddr, 0, sizeof(nodeaddr));
    
    
    /* Setting the port */
    port = base_port + own_address;

    nodeaddr.sin_family = AF_INET;
    nodeaddr.sin_addr.s_addr = INADDR_ANY;
    nodeaddr.sin_port = htons(port);


    /* Bind the socket, and be sure
     * to tell main thread it should
     * exit if bind fails
     */
    printf("Attempting to bind port %d\n", port);
    if (bind(sockfd, (const struct sockaddr *)&nodeaddr, sizeof(nodeaddr)) < 0) {
        perror("Bind failed");
        return -1;
    }
    
    if (own_address == 1) {
        printf("own_address == 1\n");
        if (fcntl(sockfd, F_SETFL, O_NONBLOCK) != 0) {
            perror("fcntl failed");
            return -1; 
        }
    }
   
    printf("Created socket\n"); 
    return sockfd;
}

int process_file(char* file_name) {
    FILE *fd;
    char *buf;
    
    struct packet* p;
   
    char *message;
    int destination_address;
    fd = fopen(file_name, "r");
    buf = (char *)malloc(2048);
    
    unsigned char *sendbuf;

    
    if (fd == NULL) {
        perror("read_file(): fopen failed");
        return -1;
    }

    while (fgets(buf, 1024, fd) != NULL) {
        destination_address = strtol(buf, &message, 10);
        printf("\n\n\n");

        // -1 getting rid of the \newline
        message[strlen(message)-1] = '\0';
        printf("message: '%s' (%zu)\n", message, strlen(message));

        p = create_packet(destination_address, this.own_address, message, strlen(message));
        sendbuf = serialize_packet(p, strlen(message));
        
        print_pkt(sendbuf);      
        send_packet(destination_address, sendbuf, ntohs(p->packet_length));
       
        free(sendbuf); 
        free(p); 
        receive_packet(recv_socket);
        
  

      
    }

    free(buf);     
    
    fclose(fd); 
     

    return 0;
}


int parse_connection(struct Node* node, char c[]) {
    int i;
    char *token;
    int connection_parameters[2];

    token = strtok(c, ":");
    
    i = 0;
    while (token != NULL && i < 2) {
        connection_parameters[i] = atoi(token);
        printf("extracted token %d from %s\n", connection_parameters[i], c);
        token = strtok(NULL, ":");
        
        i += 1;
    }

    set_connection(node, connection_parameters[0], connection_parameters[1]);    

    printf("Parsing connection %s\n", c);
    
    return 0;
}
