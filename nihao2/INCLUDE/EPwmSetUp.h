/*
 * EPwmSetUp.h
 *
 *  Created on: 2021Äê7ÔÂ25ÈÕ
 *      Author: ZY
 */

#ifndef INCLUDE_EPWMSETUP_H_
#define INCLUDE_EPWMSETUP_H_

#if (CPU_FRQ_150MHZ)
  #define CPU_CLK   150e6
#endif
#if (CPU_FRQ_100MHZ)
  #define CPU_CLK   100e6
#endif
#define PWM_CLK   10e3                // If diff freq. desired, change freq here.
#define SP        CPU_CLK/(2*PWM_CLK)
#define TBCTLVAL  0x200E              // Up-down cnt, timebase = SYSCLKOUT

void EPwmSetup();



#endif /* INCLUDE_EPWMSETUP_H_ */
