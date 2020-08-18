#ifndef PLATFORM_INFO_H
#define PLATFORM_INFO_H

#include <stdint.h>
#define IS_64_BIT (UINTPTR_MAX == 0xFFFFFFFFFFFFFFFFU)
#define IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

// Using 8 here instead of sizeof(size_t) to ensure compatibility
#define SIZEOF_POINTER (size_t)8
#define DOUBLE_SIZE_ON_64_BIT(size) ((size) * (SIZEOF_POINTER / 4))

#endif
