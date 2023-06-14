#ifndef CH552_SYS_H
#define CH552_SYS_H

#include <compiler.h>

// B7 bOSC_EN_INT 0: ����  1: �ڲ�ʱ�ӣ�Ĭ�ϣ�
// B6 bOSC_EN_XT 0: �رվ��� 1: P1.2 �� P1.3 ���ŽӾ���
// B5 bWDOG_IF_TO  ���Ź� 0: ���ж� 1:���ж�
// B4 bROM_CLK_FAST flash-ROM �ο�ʱ��Ƶ�� 0: ����(Fosc >= 16MHz) 1: �ӿ�(Fosc < 16MHz)
// B3 bRST rst ����״̬����λ
// B[2:0] MASK_SYS_CK_SEL ʱ��Ƶ��
// MASK_SYS_CK_SEL		ϵͳ��Ƶ Fsys      �뾧��Ƶ�� Fxt ��ϵ       �� Fosc=24MHz ʱ Fsys
// 000					Fpll / 512			Fxt / 128					187.5KHz
// 001					Fpll / 128			Fxt / 32					750KHz
// 010					Fpll / 32			Fxt / 8						3MHz
// 011					Fpll / 16			Fxt / 4						6MHz
// 100					Fpll / 8			Fxt / 2						12MHz
// 101					Fpll / 6			Fxt / 1.5					16MHz
// 110					Fpll / 4			Fxt / 1						24MHz
// 111					Fpll / 3			Fxt / 0.75					����������
//
// Fosc = bOSC_EN_INT ? 24MHz : Fxt
// Fpll = Fosc * 4 = 96MHz
// ��λ�� Fosc=24MHz Fpll=96MHz Fusb4x=48MHz Fsys=6MHz
SFR(CLOCK_CFG, 0xB9);

#endif
