#ifndef CH552_PWM_H
#define CH552_PWM_H

#include <compiler.h>

// PWM ʱ�ӷ�Ƶ���üĴ���
// [7:0] ��Ƶ����
SFR(PWM_CK_SE, 0x9E);

// PWM ���ƼĴ���
// [7] �� 1 ʱ PWM ѭ�����ڽ����� MFM ���������ж�
// [6] PWM2 �������
// [5] PWM1 �������
// [4] �� 1 ʱ PWM ѭ�����ڽ����ж�
// [3] PWM2 ����
// [2] PWM1 ����
// [1] �� 1 ��� PWM1 �� PWM2 ������ FIFO�������� 0
// [0] ����
SFR(PWM_CTRL, 0x9D);

// PWM1 ���ݼĴ���
// [7:0] ռ�ձ�=PWM_DATA1/256
SFR(PWM_DATA1, 0x9C);

// PWM2 ���ݼĴ���
// [7:0] ռ�ձ�=PWM_DATA2/256
SFR(PWM_DATA2, 0x9B);

#endif