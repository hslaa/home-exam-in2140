#ifndef transmission
#define transmission
int deserialize_packet(struct packet* p, unsigned char *buf);
struct packet* create_packet(uint16_t destination_address, uint16_t source_address, char* message, int message_length);
unsigned char* serialize_packet(struct packet* p, int message_length);
#endif
