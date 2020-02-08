#ifndef ARTNET
#define ARTNET

#define ARTNET_PORT 6454      
#define ARTNET_MAX_PACKET_SIZE 530 // 18 + 512

// Byte offsets in UDP packet
#define ARTNET_LENGTH_LOW 17
#define ARTNET_LENGTH_HIGH 16
#define ARTNET_UNIVERSE_LOW 14
#define ARTNET_UNIVERSE_HIGH 15
#define ARTNET_DATA 18

#endif
