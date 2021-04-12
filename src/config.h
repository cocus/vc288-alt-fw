#ifndef __CONFIG_H
#define __CONFIG_H

/**
 * Leaves the SWIM pin enabled for debug (since its shared with the 7seg mux.)
 * Define this symbol to debug the code. As a side effect, one segment will be
 * garbled with the SWIM data.
 */
//#define SWIM_DEBUG_ENABLED

/**
 * Measured network frequency
 * Частота измеряемой сети
 */
#define FREQ_AVERAGE_NETWORK    50 /*Hz*/

/**
 * Defines how many samples are going to be averaged.
 * Note: the resulting number of samples is 2^ADC_AVERAGE_SAMPLES_BASE_2
*        Number of averaging measurement points per period for calculating the root-mean-square value
*        Количество точек измерения усреднения за период для вычисления средне квадратичного значения
 */
#define ADC_AVERAGE_SAMPLES_BASE_2      7

/**
 * Set to float or double, depending on compiler availability
 */
#define HIGH_RES_FLOAT float

/**
 * Define VOLTS_DISPLAY_ALIGN_LEFT and/or AMPS_DISPLAY_ALIGN_LEFT if the value
 * should be always aligned to the left of the display. This causes the decimal
 * place separator (the dot) to move according to the measured value.
 */
//#define VOLTS_DISPLAY_ALIGN_LEFT
//#define AMPS_DISPLAY_ALIGN_LEFT

#ifdef STM8S003
#include "config_8s003.h"
#else
#error "No suitable processor selected"
#endif

#endif /* __CONFIG_H */