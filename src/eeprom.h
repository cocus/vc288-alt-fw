#ifndef __EEPROM_H
#define __EEPROM_H

#include "config.h"
#include <stdint.h>

typedef struct
{
    uint16_t                            offset;
    HIGH_RES_FLOAT                      scaling;
} adc_calibration_values_t;

typedef struct
{
    adc_calibration_values_t            adc_amps;
    adc_calibration_values_t            adc_volts;
} eeprom_settings_t;

const eeprom_settings_t * eeprom_get_settings(void);

int8_t eeprom_load_settings(void);

void eeprom_load_defaults(const eeprom_settings_t * defaults);

void eeprom_store_settings(void);

#endif /* __EEPROM_H */