#include "config.h"
#include "timer.h"

//
//  Setup Timer 1 to generate a 100 Hz TRG0 based upon a 16 MHz timer.
//
/* From http://blog.mark-stevens.co.uk/2012/09/single-pulse-generation-with-the-stm8s/ */
void setup_timer1(void)
{
    // Enable the Timer 1 clock
    CLK_PCKENR1 |= 0x80;

    TIM1_CR1_DIR = 0;                   //  Up counter.
    TIM1_CR1_CMS = 0;                   //  Edge aligned counter.
    TIM1_CR2_MMS = 0x02;                //  Update event selected as trigger out.

    TIM1_RCR = 0;                       //  No repetition.

    TIM1_PSCRH = 0;                     //  Prescaler = 4
    TIM1_PSCRL = 3;

    TIM1_ARRH = 0x9c;                   //  High byte of 40,000.
    TIM1_ARRL = 0x40;                   //  Low byte of 40,000.

    TIM1_CR1_CEN = 1;                   //  Finally enable the timer.
}

//
//  Setup Timer 2 to generate a 400 Hz interrupt based upon a 16 MHz timer.
//
/* From http://blog.mark-stevens.co.uk/2012/08/using-timers-on-the-stm8s/ */
void setup_timer2(void)
{
    // Enable the Timer 2 clock
    CLK_PCKENR1 |= 0x20;

    TIM2_PSCR = 0x00;                   //  Prescaler = 1.
    TIM2_ARRH = 0x9c;                   //  High byte of 40,000.
    TIM2_ARRL = 0x40;                   //  Low byte of 40,000.
    TIM2_IER_UIE = 1;                   //  Enable the update interrupts.
    TIM2_CR1_CEN = 1;                   //  Finally enable the timer.
}