#ifndef __CLOCK_H
#define __CLOCK_H

#include <stdint.h>

#define STM8S_HSI_DIV_1     0x00
#define STM8S_HSI_DIV_2     0x08
#define STM8S_HSI_DIV_4     0x10
#define STM8S_HSI_DIV_8     0x18
#define STM8S_CPU_DIV_1     0x00
#define STM8S_CPU_DIV_2     0x01
#define STM8S_CPU_DIV_4     0x02
#define STM8S_CPU_DIV_8     0x03
#define STM8S_CPU_DIV_16    0x04
#define STM8S_CPU_DIV_32    0x05
#define STM8S_CPU_DIV_64    0x06
#define STM8S_CPU_DIV_128   0x07

typedef enum
{
    CORE_16MHz          = STM8S_HSI_DIV_1 | STM8S_CPU_DIV_1,    /* (HSI / 1) / 1 */
    CORE_8MHz           = STM8S_HSI_DIV_2 | STM8S_CPU_DIV_1,    /* (HSI / 2) / 1 */
    CORE_4MHz           = STM8S_HSI_DIV_4 | STM8S_CPU_DIV_1,    /* (HSI / 4) / 1 */
    CORE_2MHz           = STM8S_HSI_DIV_8 | STM8S_CPU_DIV_1,    /* (HSI / 8) / 1 */
    CORE_1MHz           = STM8S_HSI_DIV_8 | STM8S_CPU_DIV_2,    /* (HSI / 8) / 2 */
    CORE_500kHz         = STM8S_HSI_DIV_8 | STM8S_CPU_DIV_4,    /* (HSI / 8) / 4 */
    CORE_250kHz         = STM8S_HSI_DIV_8 | STM8S_CPU_DIV_8,    /* (HSI / 8) / 8 */
    CORE_125kHz         = STM8S_HSI_DIV_8 | STM8S_CPU_DIV_16,   /* (HSI / 8) / 16 */
    CORE_65k5Hz         = STM8S_HSI_DIV_8 | STM8S_CPU_DIV_32,   /* (HSI / 8) / 32 */
    CORE_31k25Hz        = STM8S_HSI_DIV_8 | STM8S_CPU_DIV_64,   /* (HSI / 8) / 64 */
    CORE_15k625Hz       = STM8S_HSI_DIV_8 | STM8S_CPU_DIV_128,  /* (HSI / 8) / 128 */
} stm8s_core_clocks;

uint32_t clock_get_f_master(void);
uint32_t clock_get_f_cpu(void);

void setup_clock(stm8s_core_clocks speed);
void delay(uint32_t n);

#endif /* __CLOCK_H */