#ifndef __7SEGDISPLAY_H
#define __7SEGDISPLAY_H

#include <stdint.h>

#define SEG_MASK_A    0x40
#define SEG_MASK_B    0x20
#define SEG_MASK_C    0x10
#define SEG_MASK_D    0x08
#define SEG_MASK_E    0x04
#define SEG_MASK_F    0x02
#define SEG_MASK_G    0x01
#define SEG_MASK_DP   0x80


#define SIMBOL_L (SEG_MASK_F | SEG_MASK_E | SEG_MASK_D | SEG_MASK_A)
#define SIMBOL_OFF 0

enum
{
    SEVEN_SEG_DP_NONE = 0,
    SEVEN_SEG_DP_RIGHTMOST = 1,
    SEVEN_SEG_DP_MIDDLE = 2,
    SEVEN_SEG_DP_LEFTMOST = 4,

    SEVEN_SEG_DP_ALL = 7,
};

enum
{
    SEVEN_SEG_DIGITS_NONE = 0,
    SEVEN_SEG_DIGITS_RIGHTMOST = 1,
    SEVEN_SEG_DIGITS_MIDDLE = 2,
    SEVEN_SEG_DIGITS_LEFTMOST = 4,

    SEVEN_SEG_DIGITS_ALL = 7,
};

enum
{
    SEVEN_SEG_FIRST_ROW = 0,
    SEVEN_SEG_SECOND_ROW = 3,
};

void set_display_from_int(uint16_t number,
                          uint8_t row,
                          uint8_t decimal_dots,
                          uint8_t digits);

#endif /* __7SEGDISPLAY_H */