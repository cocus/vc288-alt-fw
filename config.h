#ifndef __CONFIG_H
#define __CONFIG_H

/**
 * Leaves the SWIM pin enabled for debug (since its shared with the 7seg mux.)
 * Define this symbol to debug the code. As a side effect, one segment will be
 * garbled with the SWIM data.
 */
#define SWIM_DEBUG_ENABLED

/**
 * Defines how many samples are going to be averaged.
 * Note: the resulting number of samples is 2^ADC_AVERAGE_SAMPLES_BASE_2
 */
#define ADC_AVERAGE_SAMPLES_BASE_2      5

#include <stdint.h>

typedef struct
{
    uint16_t                            offset;
    float                               scaling;
} adc_calibration_values_t;

typedef struct
{
    adc_calibration_values_t            adc_amps;
    adc_calibration_values_t            adc_volts;
} eeprom_settings_t;



#include <iostm8s003f3.h>

#define EEPROM_START_PTR                0x4000

#define HSI_RC_CLOCK_SPEED              16000000UL
#define DEFAULT_SYSTEM_CORE_CLOCK       2000000UL

#define GAIN_FOR_VOLTAGE                (((8200.0f + 290000.0f) / 8200.0f) * 33.0f / 1024.0f)

#endif /* __CONFIG_H */