#include "config.h"
#include "adc.h"
#include <stdint.h>

static uint16_t adc_meas_cnt   = 0;
static uint32_t adc_ch3_avg    = 0;
static uint32_t adc_ch4_avg    = 0;
static uint16_t adc_ch3        = 0;
static uint16_t adc_ch4        = 0;

//
//  ADC1 EOC handler.
//
#pragma vector = ADC1_EOC_vector
__interrupt void ADC1_EOC_IRQHandler()
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

    // Reset the ECO flag, otherwise it will fire again straight away.
    ADC_CSR_EOC = 0;
}

//
//  Setup ADC 1 in the slowest prescaler, scan mode, and buffered data with
//  external trigger (TRG0 output from TIM1).
//
/* From http://blog.mark-stevens.co.uk/2012/09/single-scan-adc-on-the-stm8s/ */
void setup_adc(void)
{
    // Enable the ADC clock
    CLK_PCKENR2 |= 0x08;

    //  Turn ADC on. Note a second set is required to start the conversion.
    ADC_CR1_ADON = 1;       

    ADC_CSR_CH = 0x04;      //  ADC on AIN4 only.

    ADC_CR1_SPSEL = 0x04;   // Prescaler: Fmaster/8

    ADC_TDRH = 0xFF;
    ADC_TDRL = 0xFF;
    
    ADC_CR3_DBUF = 1;
    ADC_CR2_SCAN = 1;
    ADC_CR2_EXTTRIG = 1;    // Conversion on external event enabled.
    ADC_CR2_EXTSEL = 0;     // TIM1 TRG0 event output.
    ADC_CR2_ALIGN = 1;      //  Data is right aligned.
    ADC_CSR_EOCIE = 1;      //  Enable the interrupt after conversion completed.
}

uint16_t get_adc_amps(void)
{
    return adc_ch3;
}

uint16_t get_adc_volts(void)
{
    return adc_ch4;
}