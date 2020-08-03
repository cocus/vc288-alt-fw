#ifndef __CONFIG_8S003_H
#define __CONFIG_8S003_H

#include <iostm8s003f3.h>

#define EEPROM_START_PTR                0x4000

#define HSI_RC_CLOCK_SPEED              16000000UL  // 16MHz
#define DEFAULT_SYSTEM_CORE_CLOCK       2000000UL   // 2MHz


/**
 * PDF from UpcycleElectronics states a common anode display, but
 * mine is a common cathode.
 * Use either COMMON_CATHODE or COMMON_ANODE.
 */
#define DISPLAY_TYPE                    SEVEN_SEG_COMMON_CATHODE


#define ADC_SCALE                       (3.3 / 1024.0)

/* Resistance value for the combined elements R3 and RV2 from the sch */
#define AMPS_R3_RV2                     200000.0
/* Resistance value for R4 from the sch */
#define AMPS_R4                         8200.0
/* Resistance value for the on-board shunt */
#define AMPS_SHUNT                      0.02
/* Non-inverting OpAmp formula */
#define GAIN_FOR_AMPS                   (((1 + (AMPS_R3_RV2 / AMPS_R4)) / AMPS_SHUNT) * ADC_SCALE)

/* Resistance value for the combined elements R2 and RV1 from the sch */
#define VOLTS_R2_RV1                    291000.0
/* Resistance value for R1 from the sch */
#define VOLTS_R1                        8200.0
/* Voltage divider formula */
#define GAIN_FOR_VOLTAGE                (((VOLTS_R1 + VOLTS_R2_RV1) / VOLTS_R1) * ADC_SCALE)


#endif /* __CONFIG_8S003_H */