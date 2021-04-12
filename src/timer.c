#include <stdint.h>
#include "config.h"
#include "timer.h"

enum { 
	clockDivider = 0 
	,ticksCountPerS_AVERAGE = (FREQ_AVERAGE_NETWORK*2)*(1<<ADC_AVERAGE_SAMPLES_BASE_2)
	,TIM1_prescaler = 3  
	,TIM1_arr = (HSI_RC_CLOCK_SPEED / (1 << clockDivider )) / ((1*TIM1_prescaler) + 1) / ticksCountPerS_AVERAGE
  ,TIM2_prescaler = 0  
	,TIM2_arr = (HSI_RC_CLOCK_SPEED / (1 << clockDivider )) / (1 << TIM2_prescaler) / 400 /*Hz*/
};

//
//  Setup Timer 1 to generate a 100 Hz TRG0 based upon a 16 MHz timer.
//
/* From http://blog.mark-stevens.co.uk/2012/09/single-pulse-generation-with-the-stm8s/ */
void setup_timer1(void)
{
    // Enable the Timer 1 clock
    SETBIT(CLK_PCKENR1, CLK_PCKENR1_TIM1);

    CLRBIT(TIM1_CR1, TIM_CR1_DIR);      //  Up counter.
    CLRBIT(TIM1_CR1, TIM_CR1_CMSL);     //  Edge aligned counter.
    CLRBIT(TIM1_CR1, TIM_CR1_CMSH);     //  Edge aligned counter.

    CLRBIT(TIM1_CR2, TIM_CR2_MMS0);     //  Update event selected as trigger out.
    SETBIT(TIM1_CR2, TIM_CR2_MMS1);     //  Update event selected as trigger out.
    CLRBIT(TIM1_CR2, TIM_CR2_MMS2);     //  Update event selected as trigger out.

    TIM1_RCR = 0;                       //  No repetition.

    TIM1_PSCRH = (uint8_t)(TIM1_prescaler>>8);   //  Prescaler = 4
    TIM1_PSCRL = (uint8_t)(TIM1_prescaler);

    TIM1_ARRH = (uint8_t)(TIM1_arr>>8);          //  High byte of 40,000.
    TIM1_ARRL = (uint8_t)(TIM1_arr);             //  Low byte of 40,000.

    SETBIT(TIM1_CR1, TIM_CR1_CEN);      //  Finally enable the timer.
}

//
//  Setup Timer 2 to generate a 400 Hz interrupt based upon a 16 MHz timer.
//
/* From http://blog.mark-stevens.co.uk/2012/08/using-timers-on-the-stm8s/ */
void setup_timer2(void)
{
    // Enable the Timer 2 clock
    SETBIT(CLK_PCKENR1, CLK_PCKENR1_TIM2);

    TIM2_PSCR = TIM2_prescaler;         //  Prescaler = 1.
    TIM2_ARRH = (uint8_t)(TIM2_arr>>8); //  High byte of 40,000.
    TIM2_ARRL = (uint8_t)(TIM2_arr);    //  Low byte of 40,000.

    SETBIT(TIM2_IER, TIM_IER_UIE);      //  Enable the update interrupts.
    SETBIT(TIM2_CR1, TIM_CR1_CEN);      //  Finally enable the timer.
}