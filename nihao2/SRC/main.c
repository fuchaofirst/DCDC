#include "main.h"

interrupt void ISRTimer0(void);  // interrupt for timer0
void InitGPIO_LED(void);

/*@author: ZY
 *@date  : 2021-07-24
 *@method: InitDSP_PieVector
 *@param : none
 *@return: none
*/
void InitDSP_PieVector()
{
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    InitSysCtrl();

    // Step 2. Initalize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    // InitGpio();  // Skipped for this example
    InitXintf16Gpio();  //zq

    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    DINT;

    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    InitPieVectTable();

}

/*@author: ZY
 *@date  : 2021-07-24
 *@method: Defalut_InitLed_Staus
 *@param : none
 *@return: none
*/

void Defalut_InitLed_Staus()
{
    LED1=0;
    DELAY_US(10);
    LED2=0;
    DELAY_US(10);
    LED3=0;
    DELAY_US(10);
    LED4=0;
    DELAY_US(10);
    LED5=0;
    DELAY_US(10);
}
void main(void)
{
    InitDSP_PieVector();
    InitGPIO_LED();
    EALLOW;
    PieVectTable.TINT0 = &ISRTimer0;  // resgister timer0 as the interupt function
    EDIS;
    InitCpuTimers();   // init the timer0
    //calculate:£ºthe ¡÷T= Freq * Period /150000000£¨s£©: 150000000 is the osc_freq
    ConfigCpuTimer(&CpuTimer0, 150, 500000);
    StartCpuTimer0();

    IER |= M_INT1;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    EINT;   // enable INTM
    ERTM;   // enable runtime Iner
    Defalut_InitLed_Staus();
    while(1){

    }

}




void InitGPIO_LED(void)
{
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // SET GPIO0 AMUX
   GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;  // GPIO0 IS OUTPUT MODE

   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0; // GPIO1 = GPIO1
   GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;

   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0; // SET GPIO2 AMUX
   GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;  // GPIO2 IS OUTPUT MODE

   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0; // SET GPIO3 AMUX
   GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;  // GPIO3 IS OUTPUT MODE

   GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0; // SET GPIO3 AMUX
   GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;  // GPIO4 IS OUTPUT MODE
   EDIS;
}
//===========================================================================
// No more.
//===========================================================================
