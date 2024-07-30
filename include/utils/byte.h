#ifndef BYTE_UTILS
#define BYTE_UTILS

#define CLEAR_BYTE(byte) (byte & 0xFF)
#define INSERT_BYTE(byte, byte_position) (CLEAR_BYTE(byte) << (byte_position << 3))
#define EXTRACT_BYTE(Value4Bytes, byte_position) ((Value4Bytes >> (byte_position << 3) & 0xFF))

#endif