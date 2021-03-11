#include "config.h"
#include "adc.h"
#include <stdint.h>

static volatile uint16_t adc_meas_cnt   = 0;
static volatile uint32_t adc_ch3_avg    = 0;
static volatile uint32_t adc_ch4_avg    = 0;
static volatile uint16_t adc_ch3        = 0;
static volatile uint16_t adc_ch4        = 0;

//
//  ADC1 EOC handler.
//
ISR(ADC1_EOC_IRQHandler, ADC1_ISR)
{
    adc_ch3_avg += (ADC_DB3RH << 8) + ADC_DB3RL;
    adc_ch4_avg += (ADC_DB4RH << 8) + ADC_DB4RL;

    if (adc_meas_cnt++ == (1 << ADC_AVERAGE_SAMPLES_BASE_2))
    {
        adc_ch3 = adc_ch3_avg >> ADC_AVERAGE_SAMPLES_BASE_2;
        adc_ch4 = adc_ch4_avg >> ADC_AVERAGE_SAMPLES_BASE_2;

        adc_meas_cnt = 0;
        adc_ch3_avg = 0;
        adc_ch4_avg = 0;
    }

    // Reset the EOC flag, otherwise it will fire again straight away.
    CLRBIT(ADC_CSR, ADC_CSR_EOC);
}

//
//  Setup ADC 1 in a slow prescaler, scan mode on, and buffered data with
//  external trigger (TRG0 output from TIM1).
//
/* From http://blog.mark-stevens.co.uk/2012/09/single-scan-adc-on-the-stm8s/ */
void setup_adc(void)
{
    // Enable the ADC clock
    SETBIT(CLK_PCKENR2, CLK_PCKENR2_ADC);

    // Turn ADC on. A second set is required to start the conversion.
    SETBIT(ADC_CR1, ADC_CR1_ADON);

    CLRBIT(ADC_CSR, ADC_CSR_CH0);   // -
    CLRBIT(ADC_CSR, ADC_CSR_CH1);   // |> ADC samples AIN4 only.
    SETBIT(ADC_CSR, ADC_CSR_CH2);   // |
    CLRBIT(ADC_CSR, ADC_CSR_CH3);   // -

    CLRBIT(ADC_CR1, ADC_CR1_SPSEL0);    // -
    CLRBIT(ADC_CR1, ADC_CR1_SPSEL1);    // |> Prescaler = fmaster/8.
    SETBIT(ADC_CR1, ADC_CR1_SPSEL2);    // -

    ADC_TDRH = 0xFF;
    ADC_TDRL = 0xFF;

    SETBIT(ADC_CR3, ADC_CR3_DBUF);      ///< When DBUF is set, converted values are stored in the ADC_DBxRH and ADC_DBxRL registers instead of the ADC_DRH and ADC_DRL registers.
    SETBIT(ADC_CR2, ADC_CR2_SCAN);      // Scan mode enabled
    SETBIT(ADC_CR2, ADC_CR2_EXTTRIG);   // Conversion on external event enabled.
    CLRBIT(ADC_CR2, ADC_CR2_EXTSEL0);   // - TIM1 TRG0 event output.
    CLRBIT(ADC_CR2, ADC_CR2_EXTSEL1);   // -
    SETBIT(ADC_CR2, ADC_CR2_ALIGN);     //  Data is right aligned.
    SETBIT(ADC_CSR, ADC_CSR_EOCIE);     //  Enable the interrupt after conversion completed.
}

uint16_t get_adc_amps(void)
{
    return adc_ch3;
}

uint16_t get_adc_volts(void)
{
    return adc_ch4;
}