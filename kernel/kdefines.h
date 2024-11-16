#ifndef _KDEFFS_H_
#define _KDEFFS_H_

typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;

#if KARCH_X86_64
typedef unsigned long long u64;
typedef          long long s64;

typedef u64 kptr_t;
#endif

#if KARCH_X86_32
typedef u32 kptr_t;
#endif

#define L16(address) (u16)((address) & 0xFFFF)
#define H16(address) (u16)(((address) >> 16) & 0xFFFF)

#define PACKED __attribute__((packed))

#endif /* _KDEFFS_H_ */
