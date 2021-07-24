/*
 * ISR_PWM.c
 *
 *  Created on: 2021年7月24日
 *      Author: ZY
 */
#include "main.h"
extern interrupt void ISRTimer0(void);
void ISRTimer0()
{

    // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; //0x0001赋给12组中断ACKnowledge寄存器，对其全部清除，不接受其他中断
    CpuTimer0Regs.TCR.bit.TIF=1;  // 定时到了指定时间，标志位置位，清除标志
    CpuTimer0Regs.TCR.bit.TRB=1;  // 重载Timer0的定时数据
    LED1=~LED1;
    LED2=~LED2;
    LED3=~LED3;
    LED4=~LED4;
    LED5=~LED5;

}



