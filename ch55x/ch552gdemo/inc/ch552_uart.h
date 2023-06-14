#ifndef CH552_UART_H
#define CH552_UART_H

#include <compiler.h>

// B7 SM0  0: 8bit    1: 9bit
// B6 SM1  0: �̶�������  1: �ɱ䲨���� �� T1 �� T2 ����
// B5 SM2  ���ͨ��λ
// B4 REN  0: ��ֹ����   1: �������
// B3 TB8  �������ݵ�9λ
// B2 RB8  �������ݵ�9λ
// B1 TI   �����жϱ�־λ��Ӳ����λ���������
// B0 RI   �����жϱ�־λ��Ӳ����λ���������
// UART0 ���ƼĴ��� ��λֵ�� 0x00
SFR(UART_SCON, 0x98);

// UART0 ���ݼĴ���
SFR(UART_SBUF, 0x99);

// B7  U1SM0  0: 8bit    1: 9bit
// B6  ����
// B5  U1SMOD  UART1  0: ����ģʽ  1: ����ģʽ
// B4  U1REN   UART1  0: ��ֹ����  1: �������
// B3  U1TB8   UART1  9bit ʱ�������ݵ�9λ
// B2  U1RB8   UART1  9bit ʱ�������ݵ�9λ
// B1  U1TI   �����жϱ�־λ��Ӳ����λ���������
// B0  U1RI   �����жϱ�־λ��Ӳ����λ���������
SFR(UART_SCON1, 0xC0); // UART1 ���ƼĴ��� ��λֵ��0x40
SFR(UART_SBUF1, 0xC1); // UART1 ���ݼĴ���
SFR(UART_SBAUD1, 0xC2); // UART1 ���������üĴ���

#endif
