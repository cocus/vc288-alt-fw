#include "config.h"
#include "adc.h"
#include <stdint.h>

#define VAR_ADC_SCAN

static volatile uint16_t adc_meas_cnt   = 0;
static volatile uint32_t adc_ch3_avg    = 0;
static volatile uint32_t adc_ch4_avg    = 0;
static volatile uint16_t adc_ch3        = 0;
static volatile uint16_t adc_ch4        = 0;
static volatile uint8_t adc_complete    = 0;


void wait_adc_newsets(void)
{
  while(adc_complete == 0){
    wfi();
  }
  adc_complete = 0;
}

//
//  ADC1 EOC handler.
//
ISR(ADC1_EOC_IRQHandler, ITC_IRQ_ADC1)
{
  uint16_t temp16;
  uint8_t templ;
#if !defined(VAR_ADC_SCAN)
  templ =  ADC_DRH;
  temp16 = ((uint16_t)templ)<<8 | ADC_DRL;
  // Reset the EOC flag, otherwise it will fire again straight away.
  CLRBIT(ADC_CSR, ADC_CSR_EOC);
  if((ADC_CSR & ADC_CSR_CH2)==0){
    adc_ch3_avg += temp16;
    CLRBIT(ADC_CSR, ADC_CSR_CH0);   // -
    CLRBIT(ADC_CSR, ADC_CSR_CH1);   // |> ADC samples AIN4 only.
    SETBIT(ADC_CSR, ADC_CSR_CH2);   // |
    SETBIT(ADC_CR1, ADC_CR1_ADON);
  }
  else{
    adc_ch4_avg += temp16;
    SETBIT(ADC_CSR, ADC_CSR_CH0);   // -
    SETBIT(ADC_CSR, ADC_CSR_CH1);   // |> ADC samples AIN3 only.
    CLRBIT(ADC_CSR, ADC_CSR_CH2);   // |
    if (adc_meas_cnt++ == (1 << ADC_AVERAGE_SAMPLES_BASE_2))
    {
        adc_ch3 = adc_ch3_avg >> ADC_AVERAGE_SAMPLES_BASE_2;
        adc_ch4 = adc_ch4_avg >> ADC_AVERAGE_SAMPLES_BASE_2;

        adc_meas_cnt = 0;
        adc_ch3_avg = 0;
        adc_ch4_avg = 0;
        adc_complete =1;
    }
  }
#else
  templ= ADC_DB3RH;
  temp16= ((uint16_t)templ << 8) | ADC_DB3RL;
  adc_ch3_avg += temp16;
  templ= ADC_DB4RH;
  temp16= ((uint16_t)templ << 8) | ADC_DB4RL;
  adc_ch4_avg += temp16;
  // Reset the EOC flag, otherwise it will fire again straight away.
  CLRBIT(ADC_CSR, ADC_CSR_EOC);

  if (adc_meas_cnt++ == (1 << ADC_AVERAGE_SAMPLES_BASE_2))
  {
     adc_ch3 = adc_ch3_avg >> ADC_AVERAGE_SAMPLES_BASE_2;
     adc_ch4 = adc_ch4_avg >> ADC_AVERAGE_SAMPLES_BASE_2;

     adc_meas_cnt = 0;
     adc_ch3_avg = 0;
     adc_ch4_avg = 0;
     adc_complete =1;
  }

#endif
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

#if !defined(VAR_ADC_SCAN)
    // Turn ADC on. A second set is required to start the conversion.
    //SETBIT(ADC_CR1, ADC_CR1_ADON);
    CLRBIT(ADC_CR1, ADC_CR1_ADON);

    SETBIT(ADC_CSR, ADC_CSR_CH0);   // -
    SETBIT(ADC_CSR, ADC_CSR_CH1);   // |> ADC samples AIN3 only.
    CLRBIT(ADC_CSR, ADC_CSR_CH2);   // |
    CLRBIT(ADC_CSR, ADC_CSR_CH3);   // |

    SETBIT(ADC_CSR, ADC_CSR_EOCIE);     //  Enable the interrupt after conversion completed.

    CLRBIT(ADC_CR1, ADC_CR1_SPSEL0);    // -
    CLRBIT(ADC_CR1, ADC_CR1_SPSEL1);    // |> Prescaler = fmaster/8.
    SETBIT(ADC_CR1, ADC_CR1_SPSEL2);    // -
    //CLRBIT(ADC_CR1, ADC_CR1_CONT);    // -


    CLRBIT(ADC_CR3, ADC_CR3_DBUF);      ///< When DBUF is set, converted values are stored in the ADC_DBxRH and ADC_DBxRL registers instead of the ADC_DRH and ADC_DRL registers.
    CLRBIT(ADC_CR2, ADC_CR2_SCAN);      // Scan mode enabled
    SETBIT(ADC_CR2, ADC_CR2_EXTTRIG);   // Conversion on external event enabled.
    CLRBIT(ADC_CR2, ADC_CR2_EXTSEL0);   // - TIM1 TRG0 event output.
    CLRBIT(ADC_CR2, ADC_CR2_EXTSEL1);   // -
    SETBIT(ADC_CR2, ADC_CR2_ALIGN);     //  Data is right aligned.
#else
    // Turn ADC on. A second set is required to start the conversion.
    //SETBIT(ADC_CR1, ADC_CR1_ADON);
    CLRBIT(ADC_CR1, ADC_CR1_ADON);

    CLRBIT(ADC_CSR, ADC_CSR_CH0);   // -
    CLRBIT(ADC_CSR, ADC_CSR_CH1);   // |> ADC samples AIN4 only.
    SETBIT(ADC_CSR, ADC_CSR_CH2);   // |
    CLRBIT(ADC_CSR, ADC_CSR_CH3);   // |

    SETBIT(ADC_CSR, ADC_CSR_EOCIE);     //  Enable the interrupt after conversion completed.

    CLRBIT(ADC_CR1, ADC_CR1_SPSEL0);    // -
    CLRBIT(ADC_CR1, ADC_CR1_SPSEL1);    // |> Prescaler = fmaster/8.
    SETBIT(ADC_CR1, ADC_CR1_SPSEL2);    // -
    //CLRBIT(ADC_CR1, ADC_CR1_CONT);    // -

    SETBIT(ADC_CR3, ADC_CR3_DBUF);      ///< When DBUF is set, converted values are stored in the ADC_DBxRH and ADC_DBxRL registers instead of the ADC_DRH and ADC_DRL registers.
    SETBIT(ADC_CR2, ADC_CR2_SCAN);      // Scan mode enabled
    SETBIT(ADC_CR2, ADC_CR2_EXTTRIG);   // Conversion on external event enabled.
    CLRBIT(ADC_CR2, ADC_CR2_EXTSEL0);   // - TIM1 TRG0 event output.
    CLRBIT(ADC_CR2, ADC_CR2_EXTSEL1);   // -
    SETBIT(ADC_CR2, ADC_CR2_ALIGN);     //  Data is right aligned.
#endif
   
    /*------------------TDR configuration ---------------------------*/
    ADC_TDRH = 0x00;
    ADC_TDRL = (1<<4)|(1<<3);

    SETBIT(ADC_CR1, ADC_CR1_ADON);
}

uint16_t get_adc_amps(void)
{
    return adc_ch3;
}

uint16_t get_adc_volts(void)
{
    return adc_ch4;
}