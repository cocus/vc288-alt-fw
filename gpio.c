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
    /* Note: PD1 is also used for SWIM. You cant use the segment A while using SWIM */
    PD_DDR_bit.DDR1 = 1; /* PD1 = out */
    PD_CR1_bit.C11 = 1;  /* push pull */
    PD_CR2_bit.C21 = 0;  /* speed 2MHz*/
#endif

    /* B */
    PA_DDR_bit.DDR3 = 1; /* PA3 = out */
    PA_CR1_bit.C13 = 1;  /* push pull */
    PA_CR2_bit.C23 = 0;  /* speed 2MHz*/

    /* C */
    PC_DDR_bit.DDR3 = 1; /* PC3 = out */
    PC_CR1_bit.C13 = 1;  /* push pull */
    PC_CR2_bit.C23 = 0;  /* speed 2MHz*/
    
    /* D */
    PC_DDR_bit.DDR6 = 1; /* PC6 = out */
    PC_CR1_bit.C16 = 1;  /* push pull */
    PC_CR2_bit.C26 = 0;  /* speed 2MHz*/

    /* E */
    PC_DDR_bit.DDR7 = 1; /* PC7 = out */
    PC_CR1_bit.C17 = 1;  /* push pull */
    PC_CR2_bit.C27 = 0;  /* speed 2MHz*/

    /* F */
    PC_DDR_bit.DDR4 = 1; /* PC4 = out */
    PC_CR1_bit.C14 = 1;  /* push pull */
    PC_CR2_bit.C24 = 0;  /* speed 2MHz*/

    /* G */
    PA_DDR_bit.DDR2 = 1; /* PA2 = out */
    PA_CR1_bit.C12 = 1;  /* push pull */
    PA_CR2_bit.C22 = 0;  /* speed 2MHz*/

    /* Decimal point */
    PC_DDR_bit.DDR5 = 1; /* PC5 = out */
    PC_CR1_bit.C15 = 1;  /* push pull */
    PC_CR2_bit.C25 = 0;  /* speed 2MHz*/

    /**
     * First row of LEDs (common anodes)
     * (by default, every LED digit is off)
     */   
    PD_DDR_bit.DDR5 = 1; /* PD5 = out */
    PD_CR1_bit.C15 = 1;  /* push pull */
    PD_CR2_bit.C25 = 0;  /* speed 2MHz*/

    PD_DDR_bit.DDR4 = 1; /* PD4 = out */
    PD_CR1_bit.C14 = 1;  /* push pull */
    PD_CR2_bit.C24 = 0;  /* speed 2MHz*/

    /**
     * Second row of LEDs (common anodes)
     * (by default, every LED digit is off)
     */    
    PB_DDR_bit.DDR4 = 1; /* PB4 = out */
    PB_CR1_bit.C14 = 1;  /* push pull */
    PB_CR2_bit.C24 = 0;  /* speed 2MHz*/

    PA_DDR_bit.DDR1 = 1; /* PA1 = out */
    PA_CR1_bit.C11 = 1;  /* push pull */
    PA_CR2_bit.C21 = 0;  /* speed 2MHz*/
    
    PB_DDR_bit.DDR5 = 1; /* PB5 = out */
    PB_CR1_bit.C15 = 1;  /* push pull */
    PB_CR2_bit.C25 = 0;  /* speed 2MHz*/
}

uint8_t read_programming_pin(void)
{
    return PD_IDR_bit.IDR6;
}

void programming_pin_control(uint8_t is_input)
{
    if (is_input == 1)
    {
        PD_DDR_bit.DDR6 = 0; /* PD6 = in        */
        PD_CR1_bit.C16 = 1;  /* Pull-up         */
        PD_CR2_bit.C26 = 0;  /* No intrerrupt   */
    }
    else
    {
        PD_DDR_bit.DDR6 = 1; /* PD6 = out       */
        PD_CR1_bit.C16 = 1;  /* push pull       */
        PD_CR2_bit.C26 = 0;  /* speed 2MHz      */
    }
}


void set_segments(uint8_t data)
{
    PA_ODR_bit.ODR2 = data & 1; data >>= 1;     // G
    PC_ODR_bit.ODR4 = data & 1; data >>= 1;     // F
    PC_ODR_bit.ODR7 = data & 1; data >>= 1;     // E
    PC_ODR_bit.ODR6 = data & 1; data >>= 1;     // D
    PC_ODR_bit.ODR3 = data & 1; data >>= 1;     // C
    PA_ODR_bit.ODR3 = data & 1; data >>= 1;     // B
#ifndef SWIM_DEBUG_ENABLED
    PD_ODR_bit.ODR1 = data & 1; data >>= 1;     // A (same pin of SWIM)
#else
    data >>= 1;
#endif
    
    PC_ODR_bit.ODR5 = data & 1; data >>= 1;     // Dp
}

void select_digit(uint8_t digit)
{
    PD_ODR_bit.ODR4 = digit != 0;
    PD_ODR_bit.ODR6 = digit != 1;
    PD_ODR_bit.ODR5 = digit != 2;
   
    PB_ODR_bit.ODR5 = digit != 3;
    PB_ODR_bit.ODR4 = digit != 4;
    PA_ODR_bit.ODR1 = digit != 5;   
}
