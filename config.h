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

#ifdef STM8S003
#include "config_8s003.h"
#else
#error "No suitable processor selected"
#endif

#endif /* __CONFIG_H */