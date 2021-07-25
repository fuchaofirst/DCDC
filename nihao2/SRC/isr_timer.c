/*
 * ISR_PWM.c
 *
 *  Created on: 2021Äê7ÔÂ24ÈÕ
 *      Author: ZY
 */
#include "main.h"
extern interrupt void ISRTimer0(void);
void ISRTimer0()
{
    // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; //timer0 is INT1.7,mask  the other interrupt

    //to be down


    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;  // reset seq to 0
    CpuTimer0Regs.TCR.bit.TIF=1;  // clear the flag of interupt
    CpuTimer0Regs.TCR.bit.TRB=1;  // repload the timer period
}



