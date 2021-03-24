#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>

void wait_adc_newsets(void);
void setup_adc(void);
uint16_t get_adc_amps(void);
uint16_t get_adc_volts(void);

#endif /* __ADC_H */