#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>

void swim_set_as_gpio(void);
void setup_gpios(void);

void set_segments(uint8_t data);
void select_digit(uint8_t digit);

uint8_t read_programming_pin(void);
void programming_pin_control(uint8_t is_input);

#endif /* __GPIO_H */