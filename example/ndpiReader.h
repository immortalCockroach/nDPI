
void transmit_packet(char* ip_packet, bpf_u_int32 len);
void store_unknown_packet(char* key, u_char* ip_packet);
void transmit_old_packets(char* key);
int get_transmit_protocol_identifier();
