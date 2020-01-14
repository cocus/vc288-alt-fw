#ifndef __CONFIG_8S003_H
#define __CONFIG_8S003_H

#include <iostm8s003f3.h>

#define EEPROM_START_PTR                0x4000

#define HSI_RC_CLOCK_SPEED              16000000UL  // 16MHz
#define DEFAULT_SYSTEM_CORE_CLOCK       2000000UL   // 2MHz

/* TBD */
#define GAIN_FOR_AMPS                   1.0

/* Resistance value for the combined elements R2 and RV1 from the sch */
#define VOLTS_R2_RV1                    290000.0
/* Resistance value for R1 from the sch */
#define VOLTS_R1                        8200.0
/* TBD */
#define GAIN_FOR_VOLTAGE                (((VOLTS_R1 + VOLTS_R2_RV1) / VOLTS_R1) * 33.0 / 1024.0)


#endif /* __CONFIG_8S003_H */