#ifndef BYTE_UTILS
#define BYTE_UTILS

#include <stdint.h>

#define CLEAR_BYTE(byte) (byte & 0xFF)
#define INSERT_BYTE(byte, byte_position) (CLEAR_BYTE(byte) << (byte_position << 3))
#define EXTRACT_BYTE(Value4Bytes, byte_position) ((Value4Bytes >> (byte_position << 3) & 0xFF))

#ifndef BYTE
typedef uint8_t BYTE, Byte;
#endif

#ifndef WORD
typedef uint16_t WORD, Word;
#endif

#ifndef DWORD
typedef uint32_t DWORD, Dword;
#endif

#ifndef QWORD
typedef uint64_t QWORD, Qword;
#endif

#endif