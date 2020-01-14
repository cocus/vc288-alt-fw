#include "config.h"
#include "eeprom.h"
#include <stdint.h>
#include <string.h>

typedef struct
{
    eeprom_settings_t       settings;
    uint16_t                crc;
} eeprom_contents_t;
static eeprom_contents_t           eeprom_contents;

/*
//                                16  12  5
// The CCITT CRC 16 polynomial is X + X + X + 1.
// In binary, this is the bit pattern 1 0001 0000 0010 0001, and in hex it
//  is 0x11021.
// A 17 bit register is simulated by testing the MSB before shifting
//  the data, which affords us the luxury of specifiy the polynomial as a
//  16 bit value, 0x1021.
// Due to the way in which we process the CRC, the bits of the polynomial
//  are stored in reverse order. This makes the polynomial 0x8408.
*/
/* From http://www.drdobbs.com/implementing-the-ccitt-cyclical-redundan/199904926 */
#define POLY 0x8408

uint16_t crc16(char *data_p, uint16_t length)
{
    uint8_t i;
    uint16_t data;
    uint16_t crc;

    crc = 0xffff;

    if (length == 0)
        return (~crc);

    do {
        for (i = 0, data = (unsigned int)0xff & *data_p++;
             i < 8;
             i++, data >>= 1)
        {
            if ((crc & 0x0001) ^ (data & 0x0001))
                crc = (crc >> 1) ^ POLY;
            else
                crc >>= 1;
        }
    } while (--length);

    crc = ~crc;

    data = crc;
    crc = (crc << 8) | (data >> 8 & 0xFF);

    return (crc);
}

const eeprom_settings_t * eeprom_get_settings(void)
{
    return &eeprom_contents.settings;
}

void eeprom_load_defaults(const eeprom_settings_t * defaults)
{
    memcpy(&eeprom_contents.settings,   /* Copy the defaults */
           defaults,                    /* into the current settings */
           sizeof(eeprom_settings_t));
}

int8_t eeprom_load_settings(void)
{
    uint16_t crc;
    char * data = (char*)EEPROM_START_PTR;

    /* Calculate the CRC of the data that should be loaded */
    crc = crc16(data,
                sizeof(eeprom_settings_t));

    /* Check if it matches the stored CRC value */
    if (((eeprom_contents_t*)data)->crc != crc)
    {
        /* Data in EEPROM is not valid */
        return -1;
    }

    /* CRC is valid, so copy the data into the current settings */
    memcpy(&eeprom_contents.settings,
           data,
           sizeof(eeprom_settings_t));

    return 0;
}

/* Code snippets from http://blog.mark-stevens.co.uk/2013/09/storing-data-eeprom-stm8s/ */
void eeprom_store_settings(void)
{
    char * data = (char*)EEPROM_START_PTR;

    //
    //  Check if the EEPROM is write-protected.  If it is then unlock the EEPROM.
    //
    if (FLASH_IAPSR_DUL == 0)
    {
        FLASH_DUKR = 0xae;
        FLASH_DUKR = 0x56;
    }

    /* Update the CRC */
    eeprom_contents.crc = crc16((char*)&eeprom_contents.settings,
                                sizeof(eeprom_settings_t));

    memcpy(data, &eeprom_contents, sizeof(eeprom_contents_t));

    //
    //  Now write protect the EEPROM.
    //
    FLASH_IAPSR_DUL = 0;
}