#include <intrinsics.h>

#include <stdint.h>

#include "config.h"
#include "clock.h"
#include "timer.h"
#include "adc.h"
#include "gpio.h"

/* Private variables */
uint8_t seven_seg[] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70,
                        0x7F, 0x7B, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47, 0x00 };

uint8_t display_data[6] = { 0 };
uint8_t display_pos     = 0;

uint16_t adc_meas_cnt   = 0;
uint32_t adc_ch3_avg    = 0;
uint32_t adc_ch4_avg    = 0;
uint16_t adc_ch3        = 0;
uint16_t adc_ch4        = 0;


int16_t cal             = 0;

/* Private functions */
void select_digit(uint8_t digit);
void set_segments(uint8_t data);

//
//  Timer 2 Overflow handler.
//
#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_UPD_OVF_IRQHandler(void)
{
    if (++display_pos == 7)
    {
        display_pos = 0;
    }
    set_segments(0);                            /* Blank first */
    select_digit(display_pos);                  /* Select the digit */
    set_segments(display_data[display_pos]);    /* And set the data */

    // Reset the interrupt, otherwise it will fire again straight away.
    TIM2_SR1_UIF = 0;
}

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

void set_display_from_int(uint16_t number, 
                          uint8_t row)
{
    display_data[row+2] = seven_seg[number % 10];
    number /= 10;
    display_data[row+1] = seven_seg[number % 10];
    number /= 10;
    display_data[row+0] = seven_seg[number % 10];
}

//
// Delay loop
//
// Actual delay depends on clock settings
// and compiler optimization settings.
//
void delay(uint32_t n)
{
    while (n-- > 0);
}

int main(void)
{
    int16_t value = 0;
    float fvalue = 0;
    
    __disable_interrupt();

    /* Switch to 16MHz */
    setup_clock();
    
    /* All segments off by default */
    set_segments(0);
    /* And no digit selected */
    select_digit(0xFF);
    
    /* Set the outputs (except the programming input pin) */
    setup_gpios();
    
    /* Check if the user wants to calibrate the device */
    programming_pin_control(1);
    
    setup_adc();
    
    setup_timer1();
    setup_timer2();

    if (read_programming_pin() == 1)
    {
        __enable_interrupt();
        while(read_programming_pin() == 0);
        delay(80000);
        cal = -adc_ch3;
        __disable_interrupt();
        
        /* Calibration done, continue */
    }
    
    programming_pin_control(0);     //  Programming pin as output (normal operation)

 
    __enable_interrupt();

    //
    // Main loop
    //
    while (1)
    {
        value = adc_ch3;
        value+= cal;
        if (value < 0)
        {
            value = 0;
        }
        set_display_from_int(value, 3);
        
        fvalue = (float)3.179f;
        fvalue *= adc_ch4;
        value = fvalue + 11.614f;
        
        set_display_from_int(value, 0);
        delay(20000);
    }
}
