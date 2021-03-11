# vc288-alt-fw
VC288 Volt-amp meter alternative firmware. Targets the cheap DSN-VC288 volt-amp meter that uses the STM8S003F MCU.

# How to compile
1. [Install](https://code.visualstudio.com/download) Visual Studio Code in your system.
2. Install the [PlatformIO](https://platformio.org/install/ide?install=vscode) extension on Visual Studio Code.
3. Once these are installed, open the PlatformIO Home from the extension icon, and install the ST STM8 platform.
4. Open this repository, by either cloning it to a directory, or by unziping the zip archive.
5. Finally, build the code by navigating into the PlatformIO extension icon, and expanding the appropriate `release` build (for instance, `stm8sblue_release`). Select `Build` to build it; then `Upload` to upload the code to the chip using an STLinkV2.

For more info and other tools to upload it, please consult the PlatformIO info page for ST STM8.

# Load the pre-built files
Since this project uses PlatformIO, a simple action can be added later to generate the .elf or .hex file for each pull request (or release) created for the ease of flashing a pre-compiled version.

# Status
This is still not fully fledged as the original.

# TODOs:
* Linearize the ADC readings to get a precise value out of it.
* Support the STM8S103F MCU (other variants of the same voltmeter).
* ... other stuff that will come out eventually.
