/*
 * ISR_PWM.c
 *
 *  Created on: 2021��7��24��
 *      Author: ZY
 */
#include "main.h"
extern interrupt void ISRTimer0(void);
void ISRTimer0()
{

    // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; //0x0001����12���ж�ACKnowledge�Ĵ���������ȫ������������������ж�
    CpuTimer0Regs.TCR.bit.TIF=1;  // ��ʱ����ָ��ʱ�䣬��־λ��λ�������־
    CpuTimer0Regs.TCR.bit.TRB=1;  // ����Timer0�Ķ�ʱ����
    LED1=~LED1;
    LED2=~LED2;
    LED3=~LED3;
    LED4=~LED4;
    LED5=~LED5;

}



