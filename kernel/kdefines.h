#ifndef _KDEFFS_H_
#define _KDEFFS_H_

typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;

#define L16(address) (u16)((address) & 0xFFFF)
#define H16(address) (u16)(((address) >> 16) & 0xFFFF)

#endif /* _KDEFFS_H_ */
