#ifndef __7SEGDISPLAY_H
#define __7SEGDISPLAY_H

#include <stdint.h>

void set_display_from_int(uint16_t number, 
                          uint8_t row);

#endif /* __7SEGDISPLAY_H */