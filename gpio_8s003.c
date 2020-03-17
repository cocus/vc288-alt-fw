#include "config.h"
#include "gpio.h"

void setup_gpios(void)
{
    // Data Direction Register
    //
    // 0: Input
    // 1: Output

    /* A */
#ifndef SWIM_DEBUG_ENABLED
    /* Note: PD1 is also used for SWIM. You can't use the segment A while using SWIM */
    PD_DDR_DDR1 = 1; /* PD1 = out */
    PD_CR1_C11 = 1;  /* push pull */
    PD_CR2_C21 = 0;  /* speed 2MHz*/
#endif

    /* B */
    PA_DDR_DDR3 = 1; /* PA3 = out */
    PA_CR1_C13 = 1;  /* push pull */
    PA_CR2_C23 = 0;  /* speed 2MHz*/

    /* C */
    PC_DDR_DDR3 = 1; /* PC3 = out */
    PC_CR1_C13 = 1;  /* push pull */
    PC_CR2_C23 = 0;  /* speed 2MHz*/

    /* D */
    PC_DDR_DDR6 = 1; /* PC6 = out */
    PC_CR1_C16 = 1;  /* push pull */
    PC_CR2_C26 = 0;  /* speed 2MHz*/

    /* E */
    PC_DDR_DDR7 = 1; /* PC7 = out */
    PC_CR1_C17 = 1;  /* push pull */
    PC_CR2_C27 = 0;  /* speed 2MHz*/

    /* F */
    PC_DDR_DDR4 = 1; /* PC4 = out */
    PC_CR1_C14 = 1;  /* push pull */
    PC_CR2_C24 = 0;  /* speed 2MHz*/

    /* G */
    PA_DDR_DDR2 = 1; /* PA2 = out */
    PA_CR1_C12 = 1;  /* push pull */
    PA_CR2_C22 = 0;  /* speed 2MHz*/

    /* Decimal point */
    PC_DDR_DDR5 = 1; /* PC5 = out */
    PC_CR1_C15 = 1;  /* push pull */
    PC_CR2_C25 = 0;  /* speed 2MHz*/

    /**
     * First row of LEDs (common anodes/cathodes)
     */
    PD_DDR_DDR5 = 1; /* PD5 = out */
    PD_CR1_C15 = 1;  /* push pull */
    PD_CR2_C25 = 0;  /* speed 2MHz*/

    PD_DDR_DDR4 = 1; /* PD4 = out */
    PD_CR1_C14 = 1;  /* push pull */
    PD_CR2_C24 = 0;  /* speed 2MHz*/

    /* PD6 needs to be controlled with programming_pin_control() */
    
    /**
     * Second row of LEDs (common anodes/cathodes)
     */
    PB_DDR_DDR4 = 1; /* PB4 = out */
    PB_CR1_C14 = 1;  /* push pull */
    PB_CR2_C24 = 0;  /* speed 2MHz*/

    PA_DDR_DDR1 = 1; /* PA1 = out */
    PA_CR1_C11 = 1;  /* push pull */
    PA_CR2_C21 = 0;  /* speed 2MHz*/

    PB_DDR_DDR5 = 1; /* PB5 = out */
    PB_CR1_C15 = 1;  /* push pull */
    PB_CR2_C25 = 0;  /* speed 2MHz*/
}

uint8_t read_programming_pin(void)
{
    return PD_IDR_IDR6 == 0;
}

void programming_pin_control(uint8_t is_input)
{
    if (is_input == 1)
    {
        PD_DDR_DDR6 = 0; /* PD6 = in        */
        PD_CR1_C16 = 1;  /* Pull-up         */
        PD_CR2_C26 = 0;  /* No intrerrupt   */
    }
    else
    {
        PD_DDR_DDR6 = 1; /* PD6 = out       */
        PD_CR1_C16 = 1;  /* push pull       */
        PD_CR2_C26 = 0;  /* speed 2MHz      */
    }
}


void set_segments(uint8_t data)
{
    PA_ODR_ODR2 = data & 1; data >>= 1;     // G
    PC_ODR_ODR4 = data & 1; data >>= 1;     // F
    PC_ODR_ODR7 = data & 1; data >>= 1;     // E
    PC_ODR_ODR6 = data & 1; data >>= 1;     // D
    PC_ODR_ODR3 = data & 1; data >>= 1;     // C
    PA_ODR_ODR3 = data & 1; data >>= 1;     // B
#ifndef SWIM_DEBUG_ENABLED
    PD_ODR_ODR1 = data & 1; data >>= 1;     // A (same pin of SWIM)
#else
    data >>= 1;
#endif

    PC_ODR_ODR5 = data & 1; data >>= 1;     // Dp
}

void select_digit(uint8_t digit)
{
    PD_ODR_ODR4 = digit != 0;
    PD_ODR_ODR6 = digit != 1;
    PD_ODR_ODR5 = digit != 2;

    PB_ODR_ODR5 = digit != 3;
    PB_ODR_ODR4 = digit != 4;
    PA_ODR_ODR1 = digit != 5;
}
