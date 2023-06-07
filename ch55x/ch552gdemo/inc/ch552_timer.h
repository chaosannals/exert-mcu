#ifndef CH552_TIMER_H
#define CH552_TIMER_H

#include <compiler.h>

SFR(TH1, 0x8D); // Timer1 计数高字节
SFR(TH0, 0x8C); // Timer0 计数高字节
SFR(TL1, 0x8B); // Timer1 计数低字节
SFR(TL0, 0x8A); // Timer0 计数低字节

// B7   bT1_GATE   0: Timer1 与 INT 1 无关    1: 只有 INT1 高电平且TR1 = 1 启动 Timer1
// B6   bT1_CT     0: Timer1 定时方式         1: Timer1 计数方式     T1 引脚下降沿为时钟
// B5   bT1_M1     Timer1  模式高位
// B4   bT1_MO     Timer1  模式低位
// B3   bT0_GATE   0: Timer0 与 INT 0 无关    1: 只有 INT0 高电平且TR0 = 1 启动 Timer0
// B2   bT0_CT     0: Timer0 定时方式         1: Timer0 计数方式     T1 引脚下降沿为时钟
// B1   bT0_M1     Timer0  模式高位
// B0   bT0_MO     Timer0  模式低位
// 
// bTn_M1  bTnM0
// 0       0        模式0： 13位   TLn 低 5 位（高 3 位无效）  和 THn 组成， 13位 全1 变 全0 设置溢出 TFn,需重置初值
// 0       1        模式1： 16位   全1 变 全0 设置溢出 TFn,需重置初值
// 1       0        模式2： 8位重载， TLn 计数   THn 重载计数，全 1 变 全0 设置溢出 TFn,自动从 THn 加载初值
// 1       1        模式3： TL0 和 TH0 双 8位 TH0 占用 Timer1 的 TR1 TF1 和中断资源，Time1 可用
SFR(TMOD, 0x89); // Timer0/1 方法寄存器

// B7  TF1  Timer1 溢出中断标志位
// B6  TR1  Timer1 1: 启动   0:停止
// B5  TF0  Timer0 溢出中断标志位
// B4  TR0  Timer0 1: 启动   0:停止
// B3  IE1  INT1 外部中断 1 请求标志位，进入中断自动清零
// B2  IT1  INT1 外部中断 1 触发方式控制位， 0: 低电平触发  1: 高电平触发
// B1  IE0  INT1 外部中断 0 请求标志位，进入中断自动清零
// B0  IT0  INT1 外部中断 0 触发方式控制位， 0: 低电平触发  1: 高电平触发
SFR(TCON, 0x88); // Timer0/1 控制寄存器


SFR(TH2, 0xCD); // Timer2 计数器高字节
SFR(TL2, 0xCC); // Timer2 计数器低字节
SFR(T2COUNT, 0xCC); // TH2 和 TH1 合并
SFR(T2CAP1H, 0xCF); // Timer2 捕捉 1 数据高字节 只读
SFR(T2CAP1L, 0xCE); // Timer2 捕捉 1 数据低字节 只读
SFR(T2CAP1, 0xCE); // T2CAP1H 和 T2CAP1L 合并
SFR(RCAP2H, 0xCB); // 计数重载/捕捉 2 数据寄存器高字节
SFR(RCAP2L, 0xCA); // 计数重载/捕捉 2 数据寄存器低字节
SFR(RCAP2, 0xCA); // RCAP2H 和 RCAP2L 合并
SFR(T2MOD, 0xC9); // Timer2 方式寄存器

// B7  bT2_CAP1_EN = 0 时为 TF2   bT2_CAP1_EN = 1 时为 CAP1F
// B6  EXF2  当 EXEN2=1 T2EX 有效触发置位，软件清零
// B5  
SFR(T2CON, 0xC8); // Timer2 控制寄存器



#endif
