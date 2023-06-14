#ifndef CH552_SYS_H
#define CH552_SYS_H

#include <compiler.h>

// B7 bOSC_EN_INT 0: 晶振  1: 内部时钟（默认）
// B6 bOSC_EN_XT 0: 关闭晶振 1: P1.2 和 P1.3 引脚接晶振
// B5 bWDOG_IF_TO  看门狗 0: 无中断 1:有中断
// B4 bROM_CLK_FAST flash-ROM 参考时钟频率 0: 正常(Fosc >= 16MHz) 1: 加快(Fosc < 16MHz)
// B3 bRST rst 引脚状态输入位
// B[2:0] MASK_SYS_CK_SEL 时钟频率
// MASK_SYS_CK_SEL		系统主频 Fsys      与晶体频率 Fxt 关系       当 Fosc=24MHz 时 Fsys
// 000					Fpll / 512			Fxt / 128					187.5KHz
// 001					Fpll / 128			Fxt / 32					750KHz
// 010					Fpll / 32			Fxt / 8						3MHz
// 011					Fpll / 16			Fxt / 4						6MHz
// 100					Fpll / 8			Fxt / 2						12MHz
// 101					Fpll / 6			Fxt / 1.5					16MHz
// 110					Fpll / 4			Fxt / 1						24MHz
// 111					Fpll / 3			Fxt / 0.75					保留，禁用
//
// Fosc = bOSC_EN_INT ? 24MHz : Fxt
// Fpll = Fosc * 4 = 96MHz
// 复位后： Fosc=24MHz Fpll=96MHz Fusb4x=48MHz Fsys=6MHz
SFR(CLOCK_CFG, 0xB9);

#endif
