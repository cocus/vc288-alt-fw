#include "config.h"
#include "timer.h"

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

    TIM1_PSCRH = 0;                     //  Prescaler = 4
    TIM1_PSCRL = 3;

    TIM1_ARRH = 0x9c;                   //  High byte of 40,000.
    TIM1_ARRL = 0x40;                   //  Low byte of 40,000.

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

    TIM2_PSCR = 0x00;                   //  Prescaler = 1.
    TIM2_ARRH = 0x9c;                   //  High byte of 40,000.
    TIM2_ARRL = 0x40;                   //  Low byte of 40,000.

    SETBIT(TIM2_IER, TIM_IER_UIE);      //  Enable the update interrupts.
    SETBIT(TIM2_CR1, TIM_CR1_CEN);      //  Finally enable the timer.
}