#ifndef CH552_UART_H
#define CH552_UART_H

#include <compiler.h>

// B7 SM0  0: 8bit    1: 9bit
// B6 SM1  0: 固定波特率  1: 可变波特率 由 T1 或 T2 产生
// B5 SM2  多机通信位
// B4 REN  0: 禁止接收   1: 允许接收
// B3 TB8  发送数据第9位
// B2 RB8  接收数据第9位
// B1 TI   发送中断标志位，硬件置位，软件清零
// B0 RI   接收中断标志位，硬件置位，软件清零
// UART0 控制寄存器 复位值： 0x00
SFR(UART_SCON, 0x98);

// UART0 数据寄存器
SFR(UART_SBUF, 0x99);

// B7  U1SM0  0: 8bit    1: 9bit
// B6  保留
// B5  U1SMOD  UART1  0: 慢速模式  1: 快速模式
// B4  U1REN   UART1  0: 禁止接收  1: 允许接收
// B3  U1TB8   UART1  9bit 时发送数据第9位
// B2  U1RB8   UART1  9bit 时接收数据第9位
// B1  U1TI   发送中断标志位，硬件置位，软件清零
// B0  U1RI   接收中断标志位，硬件置位，软件清零
SFR(UART_SCON1, 0xC0); // UART1 控制寄存器 复位值：0x40
SFR(UART_SBUF1, 0xC1); // UART1 数据寄存器
SFR(UART_SBAUD1, 0xC2); // UART1 波特率设置寄存器

#endif
