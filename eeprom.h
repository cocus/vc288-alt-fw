#ifndef __EEPROM_H
#define __EEPROM_H

#include "config.h"
#include <stdint.h>

eeprom_settings_t * eeprom_get_settings(void);

int8_t eeprom_load_settings(void);

void eeprom_load_defaults(const eeprom_settings_t * defaults);

void eeprom_store_settings(void);

#endif /* __EEPROM_H */