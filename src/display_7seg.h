#ifndef __7SEGDISPLAY_H
#define __7SEGDISPLAY_H

#include <stdint.h>

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