#include "config.h"
#include "gpio.h"

void setup_gpios(void)
{
    /**
     * Data Direction Register:
     * 0: Input
     * 1: Output
     *
     * Input Register:
     * each bit corresponds to the pins value.
     *
     * Output Register:
     * each bit corresponds to the pins value.
     *
     * Control Register 1:
     * 0: Floating Input    \ in input
     * 1: Pull-up           / mode
     * 0: Pseudo open drain \ in output
     * 1: Push-pull         / mode
     *
     * Control Register 2:
     * 0: Ext. Int disabled \ in input
     * 1: Ext. int enabled  / mode
     * 0: Out speed 2MHz    \ in output
     * 1: Out speed 10MHz   / mode
     */

    /* A */
#ifndef SWIM_DEBUG_ENABLED
    /* Note: PD1 is also used for SWIM. You can't use the segment A while using SWIM */
    SETBIT(PD_DDR, PIN1);   /* PD1 = out */
    SETBIT(PD_CR1, PIN1);   /* push pull */
    CLRBIT(PD_CR2, PIN1);   /* speed 2MHz*/
#endif

    /* B */
    SETBIT(PA_DDR, PIN3);   /* PA3 = out */
    SETBIT(PA_CR1, PIN3);   /* push pull */
    CLRBIT(PA_CR2, PIN3);   /* speed 2MHz*/

    /* C */
    SETBIT(PC_DDR, PIN3);   /* PC3 = out */
    SETBIT(PC_CR1, PIN3);   /* push pull */
    CLRBIT(PC_CR2, PIN3);   /* speed 2MHz*/

    /* D */
    SETBIT(PC_DDR, PIN6);   /* PC6 = out */
    SETBIT(PC_CR1, PIN6);   /* push pull */
    CLRBIT(PC_CR2, PIN6);   /* speed 2MHz*/

    /* E */
    SETBIT(PC_DDR, PIN7);   /* PC7 = out */
    SETBIT(PC_CR1, PIN7);   /* push pull */
    CLRBIT(PC_CR2, PIN7);   /* speed 2MHz*/

    /* F */
    SETBIT(PC_DDR, PIN4);   /* PC4 = out */
    SETBIT(PC_CR1, PIN4);   /* push pull */
    CLRBIT(PC_CR2, PIN4);   /* speed 2MHz*/

    /* G */
    SETBIT(PA_DDR, PIN2);   /* PA2 = out */
    SETBIT(PA_CR1, PIN2);   /* push pull */
    CLRBIT(PA_CR2, PIN2);   /* speed 2MHz*/

    /* Decimal point */
    SETBIT(PC_DDR, PIN5);   /* PC5 = out */
    SETBIT(PC_CR1, PIN5);   /* push pull */
    CLRBIT(PC_CR2, PIN5);   /* speed 2MHz*/

    /**
     * First row of LEDs (common anodes/cathodes)
     */
    SETBIT(PD_DDR, PIN5);   /* PD5 = out */
    SETBIT(PD_CR1, PIN5);   /* push pull */
    CLRBIT(PD_CR2, PIN5);   /* speed 2MHz*/

    SETBIT(PD_DDR, PIN4);   /* PD4 = out */
    SETBIT(PD_CR1, PIN4);   /* push pull */
    CLRBIT(PD_CR2, PIN4);   /* speed 2MHz*/

    /* PD6 needs to be controlled with programming_pin_control() */

    /**
     * Second row of LEDs (common anodes/cathodes)
     */
    SETBIT(PB_DDR, PIN4);   /* PB4 = out */
    SETBIT(PB_CR1, PIN4);   /* push pull */
    CLRBIT(PB_CR2, PIN4);   /* speed 2MHz*/

    SETBIT(PA_DDR, PIN1);   /* PA1 = out */
    SETBIT(PA_CR1, PIN1);   /* push pull */
    CLRBIT(PA_CR2, PIN1);   /* speed 2MHz*/

    SETBIT(PB_DDR, PIN5);   /* PB5 = out */
    SETBIT(PB_CR1, PIN5);   /* push pull */
    CLRBIT(PB_CR2, PIN5);   /* speed 2MHz*/
}

uint8_t read_programming_pin(void)
{
    return (PD_IDR & PIN6) == 0;
}

void programming_pin_control(uint8_t is_input)
{
    if (is_input == 1)
    {
        CLRBIT(PD_DDR, PIN6);   /* PD6 = in        */
        SETBIT(PD_CR1, PIN6);   /* Pull-up         */
        CLRBIT(PD_CR2, PIN6);   /* No intrerrupt   */
    }
    else
    {
        SETBIT(PD_DDR, PIN6);   /* PD6 = out       */
        SETBIT(PD_CR1, PIN6);   /* push pull       */
        CLRBIT(PD_CR2, PIN6);   /* speed 2MHz      */
    }
}


void set_segments(uint8_t data)
{
    // G
    if (data & 1) { SETBIT(PA_ODR, PIN2); } else { CLRBIT(PA_ODR, PIN2); }
    data >>= 1;

    // F
    if (data & 1) { SETBIT(PC_ODR, PIN4); } else { CLRBIT(PC_ODR, PIN4); }
    data >>= 1;

    // E
    if (data & 1) { SETBIT(PC_ODR, PIN7); } else { CLRBIT(PC_ODR, PIN7); }
    data >>= 1;

    // D
    if (data & 1) { SETBIT(PC_ODR, PIN6); } else { CLRBIT(PC_ODR, PIN6); }
    data >>= 1;

    // C
    if (data & 1) { SETBIT(PC_ODR, PIN3); } else { CLRBIT(PC_ODR, PIN3); }
    data >>= 1;

    // B
    if (data & 1) { SETBIT(PA_ODR, PIN3); } else { CLRBIT(PA_ODR, PIN3); }
    data >>= 1;

#ifndef SWIM_DEBUG_ENABLED
    // A (same pin of SWIM)
    if (data & 1) { SETBIT(PD_ODR, PIN1); } else { CLRBIT(PD_ODR, PIN1); }
#endif
    data >>= 1;

    // Dp
    if (data & 1) { SETBIT(PC_ODR, PIN5); } else { CLRBIT(PC_ODR, PIN5); }
    data >>= 1;
}

void select_digit(uint8_t digit)
{
    if (digit != 0) { SETBIT(PD_ODR, PIN4); } else { CLRBIT(PD_ODR, PIN4); }
    if (digit != 1) { SETBIT(PD_ODR, PIN6); } else { CLRBIT(PD_ODR, PIN6); }
    if (digit != 2) { SETBIT(PD_ODR, PIN5); } else { CLRBIT(PD_ODR, PIN5); }

    if (digit != 3) { SETBIT(PB_ODR, PIN5); } else { CLRBIT(PB_ODR, PIN5); }
    if (digit != 4) { SETBIT(PB_ODR, PIN4); } else { CLRBIT(PB_ODR, PIN4); }
    if (digit != 5) { SETBIT(PA_ODR, PIN1); } else { CLRBIT(PA_ODR, PIN1); }
}