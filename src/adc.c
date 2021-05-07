#include "config.h"
#include "adc.h"
#include <stdint.h>

//#define VAR_ADC_SCAN

#define ADC_DB(n,ml)   REGVAR(REGVAR(ADC_DB,n), ml);
#define ADC_DB_VOLTS_RL ADC_DB(CANELADC_VOLTS,_RL)
#define ADC_DB_VOLTS_RH ADC_DB(CANELADC_VOLTS,_RH)

#if CANELADC_AMPS < CANELADC_VOLTS
  #define CANELADC_HIGH   CANELADC_VOLTS
#else
  #define CANELADC_HIGH   CANELADC_AMPS
#endif

#define FREQ_ADC_SAMPLING  ((FREQ_AVERAGE_NETWORK*2)*(1<<ADC_AVERAGE_SAMPLES_BASE_2))

//ADC_AVERAGE_SAMPLES_BASE_2      5
#ifdef VAR_ADC_SCAN
#if FREQ_ADC_SAMPLING < 7200
//FREQ_AVERAGE_NETWORK    112 
#define ADC_PRESCALE_DEF (ADC_CR1_SPSEL2) // |> Prescaler = fmaster/8.
#elif FREQ_ADC_SAMPLING < 9600
//FREQ_AVERAGE_NETWORK    150 
#define ADC_PRESCALE_DEF (ADC_CR1_SPSEL0|ADC_CR1_SPSEL1) // |> Prescaler = fmaster/6.
#elif FREQ_ADC_SAMPLING < 28800
//FREQ_AVERAGE_NETWORK    450 
#define ADC_PRESCALE_DEF (ADC_CR1_SPSEL1) // |> Prescaler = fmaster/4.
#else
#error FREQ_ADC_SAMPLING  >  30719 
#endif
#else
#if FREQ_ADC_SAMPLING < 16384
//FREQ_AVERAGE_NETWORK    255 
#define ADC_PRESCALE_DEF (ADC_CR1_SPSEL2) // |> Prescaler = fmaster/8.
#elif FREQ_ADC_SAMPLING < 21845
//FREQ_AVERAGE_NETWORK    341 
#define ADC_PRESCALE_DEF (ADC_CR1_SPSEL0|ADC_CR1_SPSEL1) // |> Prescaler = fmaster/6.
#elif FREQ_ADC_SAMPLING < 32768
//FREQ_AVERAGE_NETWORK    510 
#define ADC_PRESCALE_DEF (ADC_CR1_SPSEL1) // |> Prescaler = fmaster/4.
#else
#error FREQ_ADC_SAMPLING  >  32767 
#endif
#endif



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
  if((ADC_CSR & 0x0F) == CANELADC_AMPS){
    adc_ch3_avg += temp16;
    
    ADC_CSR = (ADC_CSR & 0xF0) | CANELADC_VOLTS;
    
    SETBIT(ADC_CR1, ADC_CR1_ADON);
  }
  else{
    adc_ch4_avg += temp16;
    
    ADC_CSR = (ADC_CSR & 0xF0) | CANELADC_AMPS;
    
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
  templ= ADC_DB(CANELADC_AMPS,RH);
  temp16= ((uint16_t)templ << 8) | ADC_DB(CANELADC_AMPS,RL);
  adc_ch3_avg += temp16;
  templ= ADC_DB(CANELADC_VOLTS,RH);
  temp16= ((uint16_t)templ << 8) | ADC_DB(CANELADC_VOLTS,RL);
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

    ADC_CSR = (ADC_CSR & 0xF0) | CANELADC_AMPS | ADC_CSR_EOCIE;

    ADC_CR1 = (ADC_CR1 & ~(ADC_CR1_SPSEL0|ADC_CR1_SPSEL1|ADC_CR1_SPSEL2)) | ADC_PRESCALE_DEF; //Prescaler = fmaster/ADC_PRESCALE_DEF.
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

    ADC_CSR = (ADC_CSR & 0xF0) | CANELADC_HIGH | ADC_CSR_EOCIE;

    ADC_CR1 = (ADC_CR1 & ~(ADC_CR1_SPSEL0|ADC_CR1_SPSEL1|ADC_CR1_SPSEL2)) | ADC_PRESCALE_DEF; //Prescaler = fmaster/ADC_PRESCALE_DEF.

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
    ADC_TDRL = (1<<CANELADC_AMPS)|(1<<CANELADC_VOLTS);
    
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