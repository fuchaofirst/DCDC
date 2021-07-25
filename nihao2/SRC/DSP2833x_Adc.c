// TI File $Revision: /main/4 $
// Checkin $Date: July 30, 2007   14:15:53 $
//###########################################################################
//
// FILE:	DSP2833x_Adc.c
//
// TITLE:	DSP2833x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ADC_usDELAY  5000L

// ADC start parameters
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif
#define ADC_CKPS   0x0   // ADC module clock = HSPCLK/1      = 25.5MHz/(1)   = 25.0 MHz
#define ADC_SHCLK  0x1   // S/H width in ADC module periods                  = 2 ADC cycle
#define AVG        1000  // Average sample limit
//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);


    // *IMPORTANT*
	// The ADC_cal function, which  copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	    EALLOW;
		SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
		ADC_cal();
		EDIS;




    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
	// CPU_CLOCK_SPEED define statement in the DSP2833x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.
    AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;    ////ADC work on 25Mhz no
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
    /*  Acquisition window size.
        The width of SOC pulse is ADCTRL1[11:8] + 1 times the ADCLK period.
        Sequential mode: Acquisition window size = (1+ACQ_PS)*ADC clock in ns = 3*80ns =240ns*/
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;           // two 8-SEQ combine a 16-SEQ
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;           // start AD by start-stop Mode
    AdcRegs.ADCMAXCONV.all = 0x0F;
    //  left is the result ,right is the real hard chanel
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x00;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x01;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x02;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x03;

    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x04;
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x05;
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x06;
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x07;

    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x08;
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x09;
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0x0A;
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0x0B;

    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0x0C;
    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0x0D;
    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0x0E;
    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0x0F;



}

//===========================================================================
// End of file.
//===========================================================================
