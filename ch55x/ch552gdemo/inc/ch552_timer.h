#ifndef CH552_TIMER_H
#define CH552_TIMER_H

#include <compiler.h>

SFR(TH1, 0x8D); // Timer1 �������ֽ�
SFR(TH0, 0x8C); // Timer0 �������ֽ�
SFR(TL1, 0x8B); // Timer1 �������ֽ�
SFR(TL0, 0x8A); // Timer0 �������ֽ�

// B7   bT1_GATE   0: Timer1 �� INT 1 �޹�    1: ֻ�� INT1 �ߵ�ƽ��TR1 = 1 ���� Timer1
// B6   bT1_CT     0: Timer1 ��ʱ��ʽ         1: Timer1 ������ʽ     T1 �����½���Ϊʱ��
// B5   bT1_M1     Timer1  ģʽ��λ
// B4   bT1_MO     Timer1  ģʽ��λ
// B3   bT0_GATE   0: Timer0 �� INT 0 �޹�    1: ֻ�� INT0 �ߵ�ƽ��TR0 = 1 ���� Timer0
// B2   bT0_CT     0: Timer0 ��ʱ��ʽ         1: Timer0 ������ʽ     T1 �����½���Ϊʱ��
// B1   bT0_M1     Timer0  ģʽ��λ
// B0   bT0_MO     Timer0  ģʽ��λ
// 
// bTn_M1  bTnM0
// 0       0        ģʽ0�� 13λ   TLn �� 5 λ���� 3 λ��Ч��  �� THn ��ɣ� 13λ ȫ1 �� ȫ0 ������� TFn,�����ó�ֵ
// 0       1        ģʽ1�� 16λ   ȫ1 �� ȫ0 ������� TFn,�����ó�ֵ
// 1       0        ģʽ2�� 8λ���أ� TLn ����   THn ���ؼ�����ȫ 1 �� ȫ0 ������� TFn,�Զ��� THn ���س�ֵ
// 1       1        ģʽ3�� TL0 �� TH0 ˫ 8λ TH0 ռ�� Timer1 �� TR1 TF1 ���ж���Դ��Time1 ����
SFR(TMOD, 0x89); // Timer0/1 �����Ĵ���

// B7  TF1  Timer1 ����жϱ�־λ
// B6  TR1  Timer1 1: ����   0:ֹͣ
// B5  TF0  Timer0 ����жϱ�־λ
// B4  TR0  Timer0 1: ����   0:ֹͣ
// B3  IE1  INT1 �ⲿ�ж� 1 �����־λ�������ж��Զ�����
// B2  IT1  INT1 �ⲿ�ж� 1 ������ʽ����λ�� 0: �͵�ƽ����  1: �ߵ�ƽ����
// B1  IE0  INT1 �ⲿ�ж� 0 �����־λ�������ж��Զ�����
// B0  IT0  INT1 �ⲿ�ж� 0 ������ʽ����λ�� 0: �͵�ƽ����  1: �ߵ�ƽ����
SFR(TCON, 0x88); // Timer0/1 ���ƼĴ���


SFR(TH2, 0xCD); // Timer2 ���������ֽ�
SFR(TL2, 0xCC); // Timer2 ���������ֽ�
SFR(T2COUNT, 0xCC); // TH2 �� TH1 �ϲ�
SFR(T2CAP1H, 0xCF); // Timer2 ��׽ 1 ���ݸ��ֽ� ֻ��
SFR(T2CAP1L, 0xCE); // Timer2 ��׽ 1 ���ݵ��ֽ� ֻ��
SFR(T2CAP1, 0xCE); // T2CAP1H �� T2CAP1L �ϲ�
SFR(RCAP2H, 0xCB); // ��������/��׽ 2 ���ݼĴ������ֽ�
SFR(RCAP2L, 0xCA); // ��������/��׽ 2 ���ݼĴ������ֽ�
SFR(RCAP2, 0xCA); // RCAP2H �� RCAP2L �ϲ�
SFR(T2MOD, 0xC9); // Timer2 ��ʽ�Ĵ���

// B7  bT2_CAP1_EN = 0 ʱΪ TF2   bT2_CAP1_EN = 1 ʱΪ CAP1F
// B6  EXF2  �� EXEN2=1 T2EX ��Ч������λ���������
// B5  
SFR(T2CON, 0xC8); // Timer2 ���ƼĴ���



#endif
