#ifndef CH552_PWM_H
#define CH552_PWM_H

#include <compiler.h>

// PWM 时钟分频设置寄存器
// [7:0] 分频除数
SFR(PWM_CK_SE, 0x9E);

// PWM 控制寄存器
// [7] 置 1 时 PWM 循环周期结束或 MFM 缓冲区空中断
// [6] PWM2 输出极性
// [5] PWM1 输出极性
// [4] 置 1 时 PWM 循环周期结束中断
// [3] PWM2 启用
// [2] PWM1 启用
// [1] 置 1 清空 PWM1 和 PWM2 计数和 FIFO，需软置 0
// [0] 保留
SFR(PWM_CTRL, 0x9D);

// PWM1 数据寄存器
// [7:0] 占空比=PWM_DATA1/256
SFR(PWM_DATA1, 0x9C);

// PWM2 数据寄存器
// [7:0] 占空比=PWM_DATA2/256
SFR(PWM_DATA2, 0x9B);

#endif