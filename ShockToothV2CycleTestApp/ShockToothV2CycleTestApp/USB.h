#pragma once
/*Types to use*/
#include <basetsd.h>
enum struct _TEST : UINT8 {
    name = 0x0f,
    size = sizeof(name)
};

typedef struct _SYNC {
    //TODO
}SYNC, *PSYNC;
typedef enum class _PACKET_ID_TYPE
{
    //TODO DESC
    RESERVED = 0x0f, //LSb full PID: 0000 1111
    TOKEN_SPLIT = 0x1e, //LSb full PID: 0001 1110
    TOKEN_PING = 0x2d, //LSb full PID: 0010 1101
    SPECIAL_PRE = 0x3c, //LSb full PID: 0011 1100
    HANDSHAKE_ERR = 0x3c, //LSb full PID: 0011 1100
    HANDSHAKE_ACK = 0x4b, //LSb full PID: 0100 1011
    HANDSHAKE_NAK = 0x5a, //LSb full PID: 0101 1010
    HANDSHAKE_NYET = 0x69, //LSb full PID: 0110 1001
    HANDSHAKE_STALL = 0x78, //LSb full PID: 0111 1000
    TOKEN_OUT = 0x87, //LSb full PID: 1000 0111
    TOKEN_IN = 0x96,  //LSb full PID: 1001 0110
    TOKEN_SOF = 0xa5, //LSb full PID: 1010 0101
    TOKEN_SETUP = 0xb4, //LSb full PID: 1011 0100
    DATA0 = 0xc3, //LSb full PID: 1100 0011
    DATA1 = 0xd2, //LSb full PID: 1101 0010
    DATA2 = 0xe1, //LSb full PID: 1110 0001
    MDATA = 0xf0 //LSb full PID: 1111 0000

}PACKET_ID_TYPE;
typedef struct _PACKET_ID {
    //TODO first 4 bits and inverse them to get last 4 (one's compliment/NOT)

}PACKET_ID, *PPACKET_ID;

typedef struct _CRC {
    //USB USES CRC5
    /*CRC-5-USB
USB token packets
0x05 :NORMAL
0x14 :REVERSED
0x09 :RECIPROCAL
0x12 :REVERSED RECIPROCAL
odd : PARITY
x to the 5th + x squared + 1 :EQUATION
*/
/*Function CRC32
   Input:
      data:  Bytes     Array of bytes
   Output:
      crc32: UInt32    32-bit unsigned crc-32 value

Initialize crc-32 to starting value
crc32 ← 0xffffffff

for each byte in data do
   nLookupIndex ← (crc32 xor byte) and 0xFF;
   crc32 ← (crc32 shr 8) xor CRCTable[nLookupIndex] //CRCTable is an array of 256 32-bit constants

Finalize the CRC-32 value by inverting all the bits
crc32 ← crc32 xor 0xFFFFFFFF
return crc32*/
//TODO
}CRC, *PCRC;

typedef struct _ADDR {
    //TODO
}ADDR, *PADDR;

typedef struct _TOKEN_PACKET {
    PACKET_ID pid;
    //TODO
}TOKEN_PACKET, *PTOKEN_PACKET;

typedef struct _SETUP_PACKET
{
    unsigned char bmRequestType;
    unsigned char Request;
    unsigned short Value;
    unsigned short Index;
    unsigned short Count;

}SETUP_PACKET,*PSETUP_PACKET;