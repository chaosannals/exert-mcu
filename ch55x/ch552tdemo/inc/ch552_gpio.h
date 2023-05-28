#ifndef CH552_GPIO_H
#define CH552_GPIO_H

#include <compiler.h>

// P1 输出模式寄存器  复位： 0xff    0 - 推挽  1 - 开漏
SFR(P1_MOD_OC, 0x92);

// P1 端口方向控制和上拉使能寄存器  复位： 0xff   
// 推挽下： 0 - 输入  1 - 输出
// 开漏下： 0 禁止上拉  1 使能上拉
SFR(P1_DIR_PU, 0x93);

// P3 输入输出模式寄存器  复位： 0xff    0 - 推挽  1 - 开漏
SFR(P3_MOD_OC, 0x96);

// P3 端口方向控制和上拉使能寄存器  复位： 0xff   
// 推挽下： 0 - 输入  1 - 输出 
// 开漏下： 0 禁止上拉  1 使能上拉
SFR(P3_DIR_PU, 0x97);

// 引脚功能选择寄存器  复位： 0x80
SFR(PIN_FUNC, 0xC6);

// 总线辅助设置寄存器  复位： 0x00
SFR(XBUS_AUX, 0xA2);

#endif
