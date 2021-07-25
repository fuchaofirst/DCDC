// TI File $Revision: /main/9 $
// Checkin $Date: August 10, 2007   09:05:08 $
//###########################################################################
//
// FILE:	Example_EpwmSetup.c
//
// TITLE:	Frequency measurement using EQEP peripheral
//
// DESCRIPTION:
//
// This file contains source for the ePWM initialization for the
// freq calculation module
//
//###########################################################################
// Original Author: SD
//
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "EPwmSetUp.h"
void EPwm1_ActionCfg()
{
    InitEPwm1Gpio();
    EPwm1Regs.TBPRD=SP;    // set prorid
    EPwm1Regs.TBPHS.half.TBPHS=0;
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/dn
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;     //master module
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Pass through
    //TBCLK=SYSCLKOUT/(HSPCLKDIV * CLKDIV)=SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;     //Timebase clock pre-scale
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;  //High speed time pre-scale
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO; // Select INT on Zero event
    EPwm1Regs.ETSEL.bit.INTEN = 0;            // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;       // Generate INT on 1st event
    EPwm1Regs.TBSTS.all=0;  //timeBase status clear
    EPwm1Regs.TBCTR=0;     //timeBase counter clear


    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;   // Set PWM1A on event : ctr = zero
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR; // Clear PWM1A on ctr = cmpa(up)
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;
    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;

    //Next is the dead Band config
    //EPwm1Regs.DBCTL.bit.MODE = DB_FULL_ENABLE; // enable Dead-band module
    //EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
    //EPwm1Regs.DBFED = 50; // FED = 50 TBCLKs
    //EPwm1Regs.DBRED = 50; // RED = 50 TBCLKs

    EPwm1Regs.CMPA.half.CMPA =SP/4;
    EPwm1Regs.CMPB=SP/4;

//---------------------------------------------------------
    EPwm1Regs.TZSEL.all=0;
    EPwm1Regs.TZCTL.all=0;
    EPwm1Regs.TZEINT.all=0;
    EPwm1Regs.TZFLG.all=0;
    EPwm1Regs.TZCLR.all=0;
    EPwm1Regs.TZFRC.all=0;
    EPwm1Regs.ETSEL.all=0;            // Interrupt when TBCTR = 0x0000
    EPwm1Regs.ETFLG.all=0;
    EPwm1Regs.ETCLR.all=0;
    EPwm1Regs.ETFRC.all=0;
    EPwm1Regs.PCCTL.all=0;
}
void EPwm2_ActionCfg()
{
    InitEPwm2Gpio();
    EPwm2Regs.TBPRD=SP;    // set prorid
    EPwm2Regs.TBPHS.half.TBPHS=0;
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/dn
    EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;     //master module
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Pass through
    EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;        //Phase Direction
    //TBCLK=SYSCLKOUT/(HSPCLKDIV * CLKDIV)=SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;     //Timebase clock pre-scale
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;  //High speed time pre-scale

    EPwm2Regs.TBSTS.all=0;  //timeBase status clear
    EPwm2Regs.TBCTR=0;     //timeBase counter clear


    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;   // Set PWM1A on event : ctr = zero
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR; // Clear PWM1A on ctr = cmpa(up)
    EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;
    EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;

    //Next is the dead Band config
    //EPwm2Regs.DBCTL.bit.MODE = DB_FULL_ENABLE; // enable Dead-band module
    //EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
    //EPwm2Regs.DBFED = 50; // FED = 50 TBCLKs
    //EPwm2Regs.DBRED = 50; // RED = 50 TBCLKs

    EPwm2Regs.CMPA.half.CMPA =SP/4;
    EPwm2Regs.CMPB=SP/4;

//--------------------------------------------------------
    EPwm2Regs.TZSEL.all=0;
    EPwm2Regs.TZCTL.all=0;
    EPwm2Regs.TZEINT.all=0;
    EPwm2Regs.TZFLG.all=0;
    EPwm2Regs.TZCLR.all=0;
    EPwm2Regs.TZFRC.all=0;
    EPwm2Regs.ETSEL.all=0;            // Interrupt when TBCTR = 0x0000
    EPwm2Regs.ETFLG.all=0;
    EPwm2Regs.ETCLR.all=0;
    EPwm2Regs.ETFRC.all=0;
    EPwm2Regs.PCCTL.all=0;

}
void EPwm3_ActionCfg()
{
    InitEPwm3Gpio();
    EPwm3Regs.TBPRD=SP;    // set prorid
    EPwm3Regs.TBPHS.half.TBPHS=0;
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/dn
    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;     //master module
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Pass through
    EPwm3Regs.TBCTL.bit.PHSDIR = TB_UP;        //Phase Direction
    //TBCLK=SYSCLKOUT/(HSPCLKDIV * CLKDIV)=SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;     //Timebase clock pre-scale
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;  //High speed time pre-scale
    EPwm3Regs.TBSTS.all=0;  //timeBase status clear
    EPwm3Regs.TBCTR=0;     //timeBase counter clear

    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;   // Set PWM1A on event : ctr = zero
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR; // Clear PWM1A on ctr = cmpa(up)
    EPwm3Regs.AQCTLB.bit.CBU = AQ_SET;
    EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;

    //Next is the dead Band config
    //EPwm3Regs.DBCTL.bit.MODE = DB_FULL_ENABLE; // enable Dead-band module
    //EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
    //EPwm3Regs.DBFED = 50; // FED = 50 TBCLKs
    //EPwm3Regs.DBRED = 50; // RED = 50 TBCLKs

    EPwm3Regs.CMPA.half.CMPA =SP/4;
    EPwm3Regs.CMPB=SP/4;

//---------------------------------------------------------
    EPwm3Regs.TZSEL.all=0;
    EPwm3Regs.TZCTL.all=0;
    EPwm3Regs.TZEINT.all=0;
    EPwm3Regs.TZFLG.all=0;
    EPwm3Regs.TZCLR.all=0;
    EPwm3Regs.TZFRC.all=0;
    EPwm3Regs.ETSEL.all=0;            // Interrupt when TBCTR = 0x0000
    EPwm3Regs.ETFLG.all=0;
    EPwm3Regs.ETCLR.all=0;
    EPwm3Regs.ETFRC.all=0;
    EPwm3Regs.PCCTL.all=0;

}
void EPwm4_ActionCfg()
{
    InitEPwm4Gpio();
    EPwm4Regs.TBPRD=SP;    // set prorid
    EPwm4Regs.TBPHS.half.TBPHS=0;
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/dn
    EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;     //master module
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Pass through
    EPwm4Regs.TBCTL.bit.PHSDIR = TB_UP;        //Phase Direction
    //TBCLK=SYSCLKOUT/(HSPCLKDIV * CLKDIV)=SYSCLKOUT
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;     //Timebase clock pre-scale
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;  //High speed time pre-scale
    EPwm4Regs.TBSTS.all=0;  //timeBase status clear
    EPwm4Regs.TBCTR=0;     //timeBase counter clear


    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;   // Set PWM1A on event : ctr = zero
    EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR; // Clear PWM1A on ctr = cmpa(up)
    EPwm4Regs.AQCTLB.bit.CBU = AQ_SET;
    EPwm4Regs.AQCTLB.bit.CBD = AQ_CLEAR;

    //Next is the dead Band config
    //EPwm4Regs.DBCTL.bit.MODE = DB_FULL_ENABLE; // enable Dead-band module
    //EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
    //EPwm4Regs.DBFED = 50; // FED = 50 TBCLKs
    //EPwm4Regs.DBRED = 50; // RED = 50 TBCLKs

    EPwm4Regs.CMPA.half.CMPA =SP/4;
    EPwm4Regs.CMPB=SP/4;

//---------------------------------------------------------
    EPwm4Regs.TZSEL.all=0;
    EPwm4Regs.TZCTL.all=0;
    EPwm4Regs.TZEINT.all=0;
    EPwm4Regs.TZFLG.all=0;
    EPwm4Regs.TZCLR.all=0;
    EPwm4Regs.TZFRC.all=0;
    EPwm4Regs.ETSEL.all=0;            // Interrupt when TBCTR = 0x0000
    EPwm4Regs.ETFLG.all=0;
    EPwm4Regs.ETCLR.all=0;
    EPwm4Regs.ETFRC.all=0;
    EPwm4Regs.PCCTL.all=0;
}
void EPwmSetup()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0; // Stop all the TB clocks
    EDIS;

    // force all PWM to low
    EPwm1Regs.AQCSFRC.all = 0x05; //PWM1A,PWM1B force low
    EPwm2Regs.AQCSFRC.all = 0x05; //PWM2A,PWM2B force low
    EPwm3Regs.AQCSFRC.all = 0x05; //PWM3A,PWM3B force low
    EPwm4Regs.AQCSFRC.all = 0x05; //PWM4A,PWM4B force low


    EPwm1_ActionCfg();
    EPwm2_ActionCfg();
    EPwm3_ActionCfg();
    EPwm4_ActionCfg();

}


