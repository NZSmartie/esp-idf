#ifndef __ARCH_CC_H__
#define __ARCH_CC_H__

#define EFAULT 14

#define LWIP_ERRNO_INCLUDE "sys/errno.h"

#if (1)
#define BYTE_ORDER LITTLE_ENDIAN
#else
#define BYTE_ORDER BIG_ENDIAN
#endif

typedef int sys_prot_t;

#define S16_F "d"
#define U16_F "d"
#define X16_F "x"

#define S32_F "d"
#define U32_F "d"
#define X32_F "x"

//#define PACK_STRUCT_FIELD(x) x __attribute__((packed))
#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END

#include <stdio.h>

#ifdef LWIP_DEBUG
extern void sys_arch_assert(const char *file, int line);

#define LWIP_PLATFORM_DIAG(x)   do {printf x;} while(0)
#define LWIP_PLATFORM_ASSERT(x) do {printf(x); sys_arch_assert(__FILE__, __LINE__);} while(0)
#else
#define LWIP_PLATFORM_DIAG(x)
#define LWIP_PLATFORM_ASSERT(x)
#endif

#ifndef LWIP_PLATFORM_BYTESWAP
#define LWIP_PLATFORM_BYTESWAP 1
#endif

#define LWIP_PLATFORM_HTONS(_n)  ((u16_t)((((_n) & 0xff) << 8) | (((_n) >> 8) & 0xff)))
#define LWIP_PLATFORM_HTONL(_n)  ((u32_t)( (((_n) & 0xff) << 24) | (((_n) & 0xff00) << 8) | (((_n) >> 8)  & 0xff00) | (((_n) >> 24) & 0xff) ))

#define LWIP_TIMEVAL_PRIVATE 0

#endif /* __ARCH_CC_H__ */