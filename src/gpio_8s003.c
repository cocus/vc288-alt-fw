#include "config.h"
#include "gpio.h"
#include "display_7seg.h"


#if DISPLAY_TYPE == SEVEN_SEG_COMMON_ANODE
 #define SEGDATASETS(data,mask)  ((data&mask) == 0)  
 #define SEGROWSELECT(digit,row)  (digit == row)  
#else
 #define SEGDATASETS(data,mask)  ((data&mask) != 0)
 #define SEGROWSELECT(digit,row)  (digit != row)
#endif


void swim_set_as_gpio(void)
{
#if !defined(SWIM_DEBUG_ENABLED)
    SETBIT(PORT(PD,DDR), PIN1);   /* out */
    SETBIT(PORT(PD,CR1), PIN1);   /* push pull */
    CLRBIT(PORT(PD,CR2), PIN1);   /* speed 2MHz*/
    //CFG_GCR = CFG_GCR_SWD;// disable SWIM interface
#endif
}


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
#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_A))
    /* Note: PD1 is also used for SWIM. You can't use the segment A while using SWIM */
    SETBIT(PORT(MCD_A_PORT,DDR), MCD_A_PIN);   /* out */
    SETBIT(PORT(MCD_A_PORT,CR1), MCD_A_PIN);   /* push pull */
    CLRBIT(PORT(MCD_A_PORT,CR2), MCD_A_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_B))
    /* B */
    SETBIT(PORT(MCD_B_PORT,DDR), MCD_B_PIN);   /* out */
    SETBIT(PORT(MCD_B_PORT,CR1), MCD_B_PIN);   /* push pull */
    CLRBIT(PORT(MCD_B_PORT,CR2), MCD_B_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_C))
    /* C */
    SETBIT(PORT(MCD_C_PORT,DDR), MCD_C_PIN);   /* out */
    SETBIT(PORT(MCD_C_PORT,CR1), MCD_C_PIN);   /* push pull */
    CLRBIT(PORT(MCD_C_PORT,CR2), MCD_C_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_D))
    /* D */
    SETBIT(PORT(MCD_D_PORT,DDR), MCD_D_PIN);   /* out */
    SETBIT(PORT(MCD_D_PORT,CR1), MCD_D_PIN);   /* push pull */
    CLRBIT(PORT(MCD_D_PORT,CR2), MCD_D_PIN);   /* speed 2MHz*/

#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_E))
    /* E */
    SETBIT(PORT(MCD_E_PORT,DDR), MCD_E_PIN);   /* out */
    SETBIT(PORT(MCD_E_PORT,CR1), MCD_E_PIN);   /* push pull */
    CLRBIT(PORT(MCD_E_PORT,CR2), MCD_E_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_F))
    /* F */
    SETBIT(PORT(MCD_F_PORT,DDR), MCD_F_PIN);   /* out */
    SETBIT(PORT(MCD_F_PORT,CR1), MCD_F_PIN);   /* push pull */
    CLRBIT(PORT(MCD_F_PORT,CR2), MCD_F_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_G))
    /* G */
    SETBIT(PORT(MCD_G_PORT,DDR), MCD_G_PIN);   /* out */
    SETBIT(PORT(MCD_G_PORT,CR1), MCD_G_PIN);   /* push pull */
    CLRBIT(PORT(MCD_G_PORT,CR2), MCD_G_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_DP))
    /* Decimal point */
    SETBIT(PORT(MCD_DP_PORT,DDR), MCD_DP_PIN);   /* out */
    SETBIT(PORT(MCD_DP_PORT,CR1), MCD_DP_PIN);   /* push pull */
    CLRBIT(PORT(MCD_DP_PORT,CR2), MCD_DP_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD1_AD1))
    /**
     * First row of LEDs (common anodes/cathodes)
     */
    SETBIT(PORT(MCD1_AD1_PORT,DDR), MCD1_AD1_PIN);   /* out */
    SETBIT(PORT(MCD1_AD1_PORT,CR1), MCD1_AD1_PIN);   /* push pull */
    CLRBIT(PORT(MCD1_AD1_PORT,CR2), MCD1_AD1_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD1_AD2))
    SETBIT(PORT(MCD1_AD2_PORT,DDR), MCD1_AD2_PIN);   /* out */
    SETBIT(PORT(MCD1_AD2_PORT,CR1), MCD1_AD2_PIN);   /* push pull */
    CLRBIT(PORT(MCD1_AD2_PORT,CR2), MCD1_AD2_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD1_AD3))
    SETBIT(PORT(MCD1_AD3_PORT,DDR), MCD1_AD3_PIN);   /* out */
    SETBIT(PORT(MCD1_AD3_PORT,CR1), MCD1_AD3_PIN);   /* push pull */
    CLRBIT(PORT(MCD1_AD3_PORT,CR2), MCD1_AD3_PIN);   /* speed 2MHz*/
#endif

    /* PD6 needs to be controlled with programming_pin_control() */
#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD2_AD1))
    /**
     * Second row of LEDs (common anodes/cathodes)
     */
    SETBIT(PORT(MCD2_AD1_PORT,DDR), MCD2_AD1_PIN);   /* out */
    SETBIT(PORT(MCD2_AD1_PORT,CR1), MCD2_AD1_PIN);   /* push pull */
    CLRBIT(PORT(MCD2_AD1_PORT,CR2), MCD2_AD1_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD2_AD2))
    SETBIT(PORT(MCD2_AD2_PORT,DDR), MCD2_AD2_PIN);   /* out */
    SETBIT(PORT(MCD2_AD2_PORT,CR1), MCD2_AD2_PIN);   /* push pull */
    CLRBIT(PORT(MCD2_AD2_PORT,CR2), MCD2_AD2_PIN);   /* speed 2MHz*/
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD2_AD3))
    SETBIT(PORT(MCD2_AD3_PORT,DDR), MCD2_AD3_PIN);   /* out */
    SETBIT(PORT(MCD2_AD3_PORT,CR1), MCD2_AD3_PIN);   /* push pull */
    CLRBIT(PORT(MCD2_AD3_PORT,CR2), MCD2_AD3_PIN);   /* speed 2MHz*/
#endif
}

uint8_t read_programming_pin(void)
{
  return (PORT(STPROG_PORT,IDR) & STPROG_PIN);
}

void programming_pin_control(uint8_t is_input)
{
    if (is_input == 1)
    {
        CLRBIT(PORT(STPROG_PORT,DDR), STPROG_PIN);   /* PD6 = in        */
        SETBIT(PORT(STPROG_PORT,CR1), STPROG_PIN);   /* Pull-up         */
        CLRBIT(PORT(STPROG_PORT,CR2), STPROG_PIN);   /* No intrerrupt   */
    }
    else
    {
        SETBIT(PORT(STPROG_PORT,DDR), STPROG_PIN);   /* PD6 = out       */
        SETBIT(PORT(STPROG_PORT,CR1), STPROG_PIN);   /* push pull       */
        CLRBIT(PORT(STPROG_PORT,CR2), STPROG_PIN);   /* speed 2MHz      */
    }
}


void set_segments(uint8_t data)
{
#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_G))
    // G
    if (SEGDATASETS(data, SEG_MASK_G)) { SETBIT(PORT(MCD_G_PORT,ODR), MCD_G_PIN); } else { CLRBIT(PORT(MCD_G_PORT,ODR), MCD_G_PIN); }
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_F))
    // F
    if (SEGDATASETS(data, SEG_MASK_F)) { SETBIT(PORT(MCD_F_PORT,ODR), MCD_F_PIN); } else { CLRBIT(PORT(MCD_F_PORT,ODR), MCD_F_PIN); }
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_E))
    // E
    if (SEGDATASETS(data, SEG_MASK_E)) { SETBIT(PORT(MCD_E_PORT,ODR), MCD_E_PIN); } else { CLRBIT(PORT(MCD_E_PORT,ODR), MCD_E_PIN); }
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_D))
    // D
    if (SEGDATASETS(data, SEG_MASK_D)) { SETBIT(PORT(MCD_D_PORT,ODR), MCD_D_PIN); } else { CLRBIT(PORT(MCD_D_PORT,ODR), MCD_D_PIN); }
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_C))
    // C
    if (SEGDATASETS(data, SEG_MASK_C)) { SETBIT(PORT(MCD_C_PORT,ODR), MCD_C_PIN); } else { CLRBIT(PORT(MCD_C_PORT,ODR), MCD_C_PIN); }
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_B))
    // B
    if (SEGDATASETS(data, SEG_MASK_B)) { SETBIT(PORT(MCD_B_PORT,ODR), MCD_B_PIN); } else { CLRBIT(PORT(MCD_B_PORT,ODR), MCD_B_PIN); }
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_A))
    // A (same pin of SWIM)
    if (SEGDATASETS(data, SEG_MASK_A)) { SETBIT(PORT(MCD_A_PORT,ODR), MCD_A_PIN); } else { CLRBIT(PORT(MCD_A_PORT,ODR), MCD_A_PIN); }
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD_DP))
    // Dp
    if (SEGDATASETS(data, SEG_MASK_DP)) { SETBIT(PORT(MCD_DP_PORT,ODR), MCD_DP_PIN); } else { CLRBIT(PORT(MCD_DP_PORT,ODR), MCD_DP_PIN); }
#endif
}

void select_digit(uint8_t digit)
{
#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD1_AD1))
    if (SEGROWSELECT(digit, 0)) { SETBIT(PORT(MCD1_AD1_PORT,ODR), MCD1_AD1_PIN); } else { CLRBIT(PORT(MCD1_AD1_PORT,ODR), MCD1_AD1_PIN); }
#endif
#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD1_AD2))
    if (SEGROWSELECT(digit, 1)) { SETBIT(PORT(MCD1_AD2_PORT,ODR), MCD1_AD2_PIN); } else { CLRBIT(PORT(MCD1_AD2_PORT,ODR), MCD1_AD2_PIN); }
#endif
#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD1_AD3))
    if (SEGROWSELECT(digit, 2)) { SETBIT(PORT(MCD1_AD3_PORT,ODR), MCD1_AD3_PIN); } else { CLRBIT(PORT(MCD1_AD3_PORT,ODR), MCD1_AD3_PIN); }
#endif

#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD2_AD1))
    if (SEGROWSELECT(digit, 3)) { SETBIT(PORT(MCD2_AD1_PORT,ODR), MCD2_AD1_PIN); } else { CLRBIT(PORT(MCD2_AD1_PORT,ODR), MCD2_AD1_PIN); }
#endif
#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD2_AD2))
    if (SEGROWSELECT(digit, 4)) { SETBIT(PORT(MCD2_AD2_PORT,ODR), MCD2_AD2_PIN); } else { CLRBIT(PORT(MCD2_AD2_PORT,ODR), MCD2_AD2_PIN); }
#endif
#if !(defined(SWIM_DEBUG_ENABLED) && defined(SWIM_DEBUG_MCD2_AD3))
    if (SEGROWSELECT(digit, 5)) { SETBIT(PORT(MCD2_AD3_PORT,ODR), MCD2_AD3_PIN); } else { CLRBIT(PORT(MCD2_AD3_PORT,ODR), MCD2_AD3_PIN); }
#endif
}