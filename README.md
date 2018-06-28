# vc288-alt-fw
VC288 Volt-amp meter alternative firware. Targets the cheap DSN-VC288 volt-amp meter that uses the STM8S003F MCU.

# How to compile
You'll need IAR Embedded Workbench for STM8. It's free, you only need to register in their site with your email.
Note: Since this MCU only has 8Kb of flash, the limitations of the compiler will not come into play at all.

Open the workspace (stm8.eww) and then hit F7. The resulting binary will be created in the Debug\ or Release\ folder in the workspace.

# Status
This is still not fully fledged as the original. 

# TODOs:
* Linearize the ADC readings to get a precise value out of it.
* Store the ADC offset calibrations in the EEPROM.
* Move the decimal point dynamically.
* ... other stuff that will come out eventually.
