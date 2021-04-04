#include <stdint.h>
#include <math.h>
#include "stm8.h"
#include "config.h"
#include "clock.h"
#include "timer.h"
#include "adc.h"
#include "gpio.h"
#include "display_7seg.h"
#include "eeprom.h"

/* required per SDCC Compiler User Guide */
ISR(ADC1_EOC_IRQHandler, ITC_IRQ_ADC1);
ISR(TIM2_UPD_OVF_IRQHandler, ITC_IRQ_TIM2_OVF);

enum display_set_align
{
    DISPLAY_ALIGN_LEFT = 0,
    DISPLAY_ALIGN_RIGHT = 1,
};

/**
 * Default settings to be applied when the EEPROM contains
 * invalid data.
 * Data is being pulled from the appropriate config file for
 * the selected target.
 */
static const eeprom_settings_t default_settings =
{
    .adc_amps =
    {
        .scaling = GAIN_FOR_AMPS,
        .offset = 0,
    },
    .adc_volts =
    {
        .scaling = GAIN_FOR_VOLTAGE,
        .offset = 0,
    },
};

static void do_calibration(void)
{
    eeprom_settings_t new_settings;

    /* Use the default settings as a starting point */
    new_settings = default_settings;

    /* This should enable the ADC interrupts */
    __enable_interrupt();

    /* Wait a moment so the ADC settles */
    wait_adc_newsets();
    //delay(100000);

    /**
     * Current ADC values should correspond to an absolute zero,
     * so store whatever its read as the offset.
     */
    new_settings.adc_amps.offset = get_adc_amps();
    new_settings.adc_volts.offset = get_adc_volts();

    /* And finally store the data to the EEPROM */
    eeprom_load_defaults(&new_settings);
    eeprom_store_settings();

    /* Disable the interrupts, which should stop the ADC ints */
    __disable_interrupt();
}

static void set_display_from_double(
  HIGH_RES_FLOAT value,
  const uint8_t pos,
  const enum display_set_align align
)
{
    if (align == DISPLAY_ALIGN_LEFT)
    {
        /* Clamp to zero */
        if (value < 0.0)
        {
            set_display_from_int(
                0,
                pos,
                SEVEN_SEG_DP_LEFTMOST,
                SEVEN_SEG_DIGITS_ALL
            );
        }
        else if (value >= 100.0)
        {
            /* 100. - 999. */
            value = roundf(value);
            set_display_from_int(
                (uint16_t)(value),
                pos,
                SEVEN_SEG_DP_RIGHTMOST,
                SEVEN_SEG_DIGITS_ALL
            );
        }
        else if (value >= 10.0)
        {
            /* 10.0 - 99.9 */
            value = roundf(value * 10.0);
            if(value<1000.0)
                set_display_from_int(
                    (uint16_t)(value),
                    pos,
                    SEVEN_SEG_DP_MIDDLE,
                    SEVEN_SEG_DIGITS_ALL
                );
            else
                set_display_from_int(
                    (uint16_t)(value/10.0),
                    pos,
                    SEVEN_SEG_DP_RIGHTMOST,
                    SEVEN_SEG_DIGITS_ALL
                );
        }
        else if (value >= 1.0)
        {
            /* 1.00 - 9.99 */
            value = roundf(value * 100.0);
            if(value<1000.0)
                set_display_from_int(
                    (uint16_t)(value),
                    pos,
                    SEVEN_SEG_DP_LEFTMOST,
                    SEVEN_SEG_DIGITS_ALL
                );
            else
                set_display_from_int(
                    (uint16_t)(value/10.0),
                    pos,
                    SEVEN_SEG_DP_MIDDLE,
                    SEVEN_SEG_DIGITS_ALL
                );
        }
        else
        {
            /* .000 - .999 */
            value = roundf(value * 1000.0);
            if(value<1000.0)
                set_display_from_int(
                    (uint16_t)(value),
                    pos,
                    SEVEN_SEG_DP_NONE,
                    SEVEN_SEG_DIGITS_ALL
                );
            else
                set_display_from_int(
                    (uint16_t)(value/10.0),
                    pos,
                    SEVEN_SEG_DP_LEFTMOST,
                    SEVEN_SEG_DIGITS_ALL
                );
        }
    }
    else
    {
        /* Clamp to zero */
        if (value < 0.0)
        {
            set_display_from_int(
                0,
                pos,
                SEVEN_SEG_DP_LEFTMOST,
                SEVEN_SEG_DIGITS_ALL
            );
        }
        else if (value >= 100.0)
        {
            /* 100. - 999. */
            value = roundf(value);
            set_display_from_int(
                (uint16_t)(value),
                pos,
                SEVEN_SEG_DP_RIGHTMOST,
                SEVEN_SEG_DIGITS_ALL
            );
        }
        else if (value >= 10.0)
        {
            /* 10.0 - 99.9 */
            value = roundf(value * 10.0);
            if(value<1000.0)
                set_display_from_int(
                    (uint16_t)(value),
                    pos,
                    SEVEN_SEG_DP_MIDDLE,
                    SEVEN_SEG_DIGITS_ALL
                );
            else
                set_display_from_int(
                    (uint16_t)(value/10.0),
                    pos,
                    SEVEN_SEG_DP_RIGHTMOST,
                    SEVEN_SEG_DIGITS_ALL
                );
        }
        else
        {
            /* 0.0 - 9.9 */
            value = roundf(value * 100.0);
            if(value<1000.0)
                set_display_from_int(
                    (uint16_t)(value),
                    pos,
                    SEVEN_SEG_DP_MIDDLE,
                    SEVEN_SEG_DIGITS_MIDDLE | SEVEN_SEG_DIGITS_RIGHTMOST
                );
            else
                set_display_from_int(
                    (uint16_t)(value/10.0),
                    pos,
                    SEVEN_SEG_DP_MIDDLE,
                    SEVEN_SEG_DIGITS_ALL
                );
        }
    }
}

static void do_measure(void)
{
    HIGH_RES_FLOAT value;
    const eeprom_settings_t * settings;

    /* Read the ADC settings */
    settings = eeprom_get_settings();

    /* Raw value from ADC */
    value = get_adc_volts();
    /* Offset */
    value -= settings->adc_volts.offset;
    if (value < 0) { value = 0; }
    /* Scale */
    value *= settings->adc_volts.scaling;
#ifdef VOLTS_DISPLAY_ALIGN_LEFT
    set_display_from_double(value, SEVEN_SEG_FIRST_ROW, DISPLAY_ALIGN_LEFT);
#else
    set_display_from_double(value, SEVEN_SEG_FIRST_ROW, DISPLAY_ALIGN_RIGHT);
#endif
    /* Raw value from ADC */
    value = get_adc_amps();
    /* Offset */
    value -= settings->adc_amps.offset;
    if (value < 0) { value = 0; }
    /* Scale */
    value *= settings->adc_amps.scaling;
#ifdef VOLTS_DISPLAY_ALIGN_LEFT
    set_display_from_double(value, SEVEN_SEG_SECOND_ROW, DISPLAY_ALIGN_LEFT);
#else
    set_display_from_double(value, SEVEN_SEG_SECOND_ROW, DISPLAY_ALIGN_RIGHT);
#endif
}

void main()
{
    __disable_interrupt();

    /* Switch to 16MHz */
    setup_clock(CORE_16MHz);

    /* Set the internal state of all segments to off by default */
    set_segments(0);
    /* And no digit selected */
    select_digit(0xff);

    /* Load a default calibration if the EEPROM's content is not valid */
    if (eeprom_load_settings() != 0)
    {
        eeprom_load_defaults(&default_settings);
        eeprom_store_settings();
    }

    /* At this stage the ADC is only needed for the calibration */
    setup_adc();
    setup_timer1(); // this is the trigger needed for ADC sampling

    /**
     * Check if the user wants to calibrate the device by checking the
     * programming input pin before running the main code.
     */
    programming_pin_control(1);

    if (read_programming_pin() == 0)
    {
        /* wait until the user stops removes the jumper on the programming pin */
        while(!read_programming_pin());
        /* execute the calibration routine */
        do_calibration();
        /* Calibration done, continue */
    }
    else{
#if !defined(SWIM_DEBUG_ENABLED) || defined(NDEBUG)
      //swim disable
      swim_set_as_gpio();
#endif
    }
    
    /* Set the outputs (except the programming input pin) */
    setup_gpios();

    /* Leave programming pin as output (normal operation) */
    programming_pin_control(0);

    /* Timer2 can be enabled now, so the 7 seg display gets updated */
    setup_timer2();

    __enable_interrupt();

    //
    // Main loop
    //
    while (1)
    {
      wait_adc_newsets();  
      do_measure();
    }
}
