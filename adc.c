#include "config.h"
#include "adc.h"

//
//  Setup ADC 1 in the slowest prescaler, scan mode, and buffered data with
//  external trigger (TRG0 output from TIM1).
//
/* From http://blog.mark-stevens.co.uk/2012/09/single-scan-adc-on-the-stm8s/ */
void setup_adc(void)
{
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