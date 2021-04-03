#include "config.h"
#include "gpio.h"
#include "timer.h"
#include "display_7seg.h"
#include <stdint.h>

/* Private variables */
static const uint8_t seven_seg_lut[] = {
  /*0*/ SEG_MASK_F | SEG_MASK_E | SEG_MASK_D | SEG_MASK_C | SEG_MASK_B | SEG_MASK_A,
  /*1*/ SEG_MASK_C | SEG_MASK_B,
  /*2*/ SEG_MASK_D | SEG_MASK_E | SEG_MASK_G | SEG_MASK_B | SEG_MASK_A,
  /*3*/ SEG_MASK_G | SEG_MASK_D | SEG_MASK_C | SEG_MASK_B | SEG_MASK_A,
  /*4*/ SEG_MASK_G | SEG_MASK_F | SEG_MASK_C | SEG_MASK_B,
  /*5*/ SEG_MASK_G | SEG_MASK_F | SEG_MASK_D | SEG_MASK_C | SEG_MASK_A,
  /*6*/ SEG_MASK_G | SEG_MASK_F | SEG_MASK_E | SEG_MASK_D | SEG_MASK_C | SEG_MASK_A,
  /*7*/ SEG_MASK_C | SEG_MASK_B | SEG_MASK_A,
  /*8*/ SEG_MASK_G | SEG_MASK_F | SEG_MASK_E | SEG_MASK_D | SEG_MASK_C | SEG_MASK_B | SEG_MASK_A,
  /*9*/ SEG_MASK_G | SEG_MASK_F | SEG_MASK_D | SEG_MASK_C | SEG_MASK_B | SEG_MASK_A,  
  /*a*/ SEG_MASK_G | SEG_MASK_F | SEG_MASK_E | SEG_MASK_C | SEG_MASK_B | SEG_MASK_A,//0x77,
  /*b*/ SEG_MASK_G | SEG_MASK_F | SEG_MASK_E | SEG_MASK_D | SEG_MASK_A,//0x1F
  /*c*/ SEG_MASK_F | SEG_MASK_E | SEG_MASK_D | SEG_MASK_A,//0x4E
  /*d*/ SEG_MASK_G | SEG_MASK_E | SEG_MASK_D | SEG_MASK_C | SEG_MASK_B,//0x3D
  /*E*/ SEG_MASK_G | SEG_MASK_F | SEG_MASK_E | SEG_MASK_D | SEG_MASK_A,//0x4F
  /*F*/ SEG_MASK_G | SEG_MASK_F | SEG_MASK_E | SEG_MASK_A,//0x47
  /*off*/ 0x00
  };

static volatile uint8_t display_data[6] = { 0 };
static volatile uint8_t display_pos     = 0;

//
//  Timer 2 Overflow handler.
//
ISR(TIM2_UPD_OVF_IRQHandler, ITC_IRQ_TIM2_OVF)
{
    if (++display_pos == 7)
    {
        display_pos = 0;
    }

    select_digit(-1);                  /* off all digit */
    set_segments(display_data[display_pos]);    /* And set the data */
    select_digit(display_pos);                  /* Select the digit */

    // Reset the interrupt, otherwise it will fire again straight away.
    CLRBIT(TIM2_SR1, TIM_SR1_UIF);
}

void set_display_from_int(uint16_t number,
                          uint8_t row,
                          uint8_t decimal_dots,
                          uint8_t digits)
{
    // Note: 8th bit controls the decimal place dot
    display_data[row+2] = (digits & 1 ? seven_seg_lut[number % 10] : 0) |
                          (decimal_dots & 1 ? SEG_MASK_DP : 0);
    number /= 10;
    decimal_dots >>= 1;
    display_data[row+1] = (digits & 1 ? seven_seg_lut[number % 10] : 0) |
                          (decimal_dots & 1 ? SEG_MASK_DP : 0);
    number /= 10;
    decimal_dots >>= 1;
    display_data[row+0] = (digits & 1 ? seven_seg_lut[number % 10] : 0) |
                          (decimal_dots & 1 ? SEG_MASK_DP : 0);
}