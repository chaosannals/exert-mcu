#ifndef _H_COMPILER
#define _H_COMPILER

#ifdef __SDCC

#define SFR(name,addr) __sfr __at(addr) name
#define SFR16(name,addr) __sfr16 __at(addr) name
#define SFR32(name,addr) __sfr32 __at(addr) name
#define SBIT(name,addr,index) __sbit __at(addr+index) name

#else // KEIL_C51

#define SFR(name,addr) sfr name = addr
#define SFR16(name,addr) sfr16 name = addr
#define SFR32(name,addr) sfr32 name = addr
#define SBIT(name,addr,index) sbit name = addr^index

#endif

#endif // !_H_COMPILER
