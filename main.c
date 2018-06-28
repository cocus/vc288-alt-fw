#include <intrinsics.h>
#include "config.h"
#include "clock.h"
#include "timer.h"
#include "adc.h"
#include "gpio.h"
#include "display_7seg.h"

#include <stdint.h>


int16_t cal             = 0;

int main(void)
{
    int16_t value = 0;
    float fvalue = 0;
    
    __disable_interrupt();

    /* Switch to 16MHz */
    setup_clock(CORE_16MHz);
    
    /* All segments off by default */
    set_segments(0);
    /* And no digit selected */
    select_digit(0xFF);
    
    /* Set the outputs (except the programming input pin) */
    setup_gpios();
    
    /**
     * Check if the user wants to calibrate the device by checking the
     * programming input pin before running the main code.
     */
    programming_pin_control(1);
    
    setup_adc();
    
    setup_timer1();
    setup_timer2();

    if (read_programming_pin() == 1)
    {
        __enable_interrupt();
        while(read_programming_pin() == 0);
        delay(80000);
        cal = -get_adc_amps();
        __disable_interrupt();
        
        /* Calibration done, continue */
    }
    
    /* Leave programming pin as output (normal operation) */
    programming_pin_control(0);

    __enable_interrupt();

    //
    // Main loop
    //
    while (1)
    {
        value = get_adc_amps();
        value+= cal;
        if (value < 0)
        {
            value = 0;
        }
        set_display_from_int(value, 3);
        
        fvalue = (float)3.179f;
        fvalue *= get_adc_volts();
        value = fvalue + 11.614f;
        
        set_display_from_int(value, 0);
        delay(20000);
    }
}
