Debug/Exe/stm8.out: main.c gpio.c adc.c clock.c display_7seg.c eeprom.c timer.c
	iarbuild stm8.ewp -make Debug -parallel 8

Release/Exe/stm8.out: main.c gpio.c adc.c clock.c display_7seg.c eeprom.c timer.c
	iarbuild stm8.ewp -make Release -parallel 8

debug: Debug/Exe/stm8.out

release: Release/Exe/stm8.out

all: debug release

clean:
	iarbuild stm8.ewp -clean Debug
	iarbuild stm8.ewp -clean Release
