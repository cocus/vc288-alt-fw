#include "config.h"
#include "clock.h"
#include <stdint.h>

static uint32_t f_CPU = DEFAULT_SYSTEM_CORE_CLOCK;
static uint32_t f_master = DEFAULT_SYSTEM_CORE_CLOCK;

//
//  Setup the system clock to run at the requested speed using the internal RC.
//
void setup_clock(stm8s_core_clocks speed)
{
    CLK_ICKR = 0;                       //  Reset the Internal Clock Register.
    CLK_ICKR_HSIEN = 1;                 //  Enable the HSI.
    CLK_ECKR = 0;                       //  Disable the external clock.
    while (CLK_ICKR_HSIRDY == 0);       //  Wait for the HSI to be ready for use.

    CLK_CKDIVR = speed;                 //  Set the clock at the selected speed.

    CLK_PCKENR1 = 0x00;                 //  Disable all peripheral clocks.
    CLK_PCKENR2 = 0x00;                 //  Ditto.

    CLK_CCOR = 0;                       //  Turn off CCO.
    CLK_HSITRIMR = 0;                   //  Turn off any HSIU trimming.
    CLK_SWIMCCR = 0;                    //  Set SWIM to run at clock / 2.
    CLK_SWR = 0xe1;                     //  Use HSI as the clock source.

    CLK_SWCR = 0;                       //  Reset the clock switch control register.
    CLK_SWCR_SWEN = 1;                  //  Enable switching.

    while (CLK_SWCR_SWBSY != 0);        //  Pause while the clock switch is busy.

    /* CLK_CKDIVR[4:3] sets the HSI prescaler (1, 2, 4, 8) */
    f_master = HSI_RC_CLOCK_SPEED >> ((speed & 0x18) >> 3);
    /* CLK_CKDIVR[2:0] sets the CPU prescaler (1, 2, ... , 128) */
    f_CPU = f_master >> (speed & 0x07);
}

const uint32_t clock_get_f_master(void)
{
    return f_master;
}

const uint32_t clock_get_f_cpu(void)
{
    return f_CPU;
}

//
// Delay loop
//
// Actual delay depends on clock settings
// and compiler optimization settings.
//
void delay(uint32_t n)
{
    while (n-- > 0);
}