#ifndef __CONFIG_H
#define __CONFIG_H

//#define SWIM_DEBUG_ENABLED
#define ADC_AVERAGE_SAMPLES_BASE_2      5




#include <iostm8s003f3.h>

#define DEFAULT_SYSTEM_CORE_CLOCK       2000000UL

#define VOLTAGE_LINEARIZATION_M         

#define GAIN_FOR_VOLTAGE                (((8200.0f + 290000.0f) / 8200.0f) * 33.0f / 1024.0f)

#endif /* __CONFIG_H */