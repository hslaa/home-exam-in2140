#ifndef transmission
#define transmission

struct packet* create_packet(uint16_t destination_address, uint16_t source_address, char* message, int message_length);
int serialize_packet(struct packet* p, int message_length);
#endif
