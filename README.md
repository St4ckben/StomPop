# PopStompbox

**Hey ! Welcome to this DIY Stompbox project.**

First of all, what is a stompbox ? According to lexico.com, there are several definitions :
> * A foot-operated device that produces a sound effect on an electric guitar.
> * A wooden box used as a percussion instrument, sounded by being struck with the feet or hands.

Here, I am talking about the second one. Basically, I just want something to hit with the foot producing a "clap! clap!" to give us the rhythm while I play guitar. :-)

If you are in, follow me !

## Table of contents

1. [Main features](https://github.com/St4ckben/PopStompbox/blob/master/README.md#1-main-features)
2. [Well, what does the PopStompbox look like ?](https://github.com/St4ckben/PopStompbox/blob/master/README.md#2-well-what-does-the-popstompbox-look-like-)
3. [Basic usage](https://github.com/St4ckben/PopStompbox/blob/master/README.md#3-basic-usage)
4. [How to change the onboarded sounds ?](https://github.com/St4ckben/PopStompbox/blob/master/README.md#4-how-to-change-the-onboarded-sounds-)
5. [How to build PopStompbox ?](https://github.com/St4ckben/PopStompbox/blob/master/README.md#5-how-to-build-popstompbox-)

## 1. Main features

- Active (9V battery powered) or passive (unpowered) mode
- Sound selection in active mode (persistent accross reboots as selected sound is stored in memory)
- Volume ajustment for both active and passive mode
- Input 6.35mm jack for optional guitar pluging
- Support of mono 8-bits 32000 Hz (best results achieved with 22050 Hz)

## 2. Well, what does the PopStompbox look like ?

## 3. Basic usage

### Active or passive mode

PopStompbox can be used in several ways.

The easiest way to use PopStombox is in passive mode. In such unpowered mode, the stompbox only needs do be plugged to an amplifier and that's it. 
It consists in a piezoelectric microphone connected to the output jack as shown below (simplified scheme). The produced sound is the amplified sound of the foot hitting the wood box.

<img src="https://raw.githubusercontent.com/St4ckben/PopStompbox/master/resources/passive_mode.png" width="500" title="Passive mode">

The active mode, one the other hand, requires a 9V battery to work. Instead of hearing an amplified wooden sound, the piezoelectric microphone is only used as a sensor and the arduino is producing a numeric sound from a mono 8-bit wav file. 

<img src="https://raw.githubusercontent.com/St4ckben/PopStompbox/master/resources/active_mode.png" width="500" title="Active mode">

**Switching from passive mode to active mode is done easily by powering on the PopStompbox.**
An internal relay is diverting the electrical circuit towards the arduino microcontroller.

### How to plug my guitar and my amp ? 

If the amplifier is equiped with several inputs, the guitar and the stompbox can be both plugged directly onto the amplifier as shown below.

<img src="https://raw.githubusercontent.com/St4ckben/PopStompbox/master/resources/parallel_plugging.png" width="450" title="Parallel plugging">

As the stompbox is equiped with an input 6.35mm jack, it is also possible to plug the guitar, the stompbox and the amp in series as shown below. The main advantage of this solution is that only one input is required on the amplifier. 

<img src="https://raw.githubusercontent.com/St4ckben/PopStompbox/master/resources/series_plugging.png" width="450" title="In-series plugging">

## 4. How to change the onboarded sounds ?

**The sounds must be converted to mono unsigned 8-bit PCM 22050 Hz. Frequencies up to 32000Hz are supported but best results are achieved with 22050 Hz.**

1. Open the stompbox case and remove the Micro-SD card from the Micro-SD card reader.
2. Connect the Micro-SD card to a computer
3. Make a copy of the Micro-SD card content
4. Format the Micro-SD card in FAT32 (formating will prevent bugs as shadow files can be seen by the arduino)
5. Rename the new set of sounds by stricly following this convention : each filename must match the "SOUNDXXX.wav" pattern where XXX is the 3-digit number of the sound (i.e SOUND001.wav, SOUND002.wav, SOUND003.wav...). Moreover, the numbers must follow each other. If there is a file missing (i.e. SOUND001.wav, SOUND002.wav, SOUND005) then the arduino will come back to the first sound file and will never play the next ones (i.e. SOUND005.wav will never be played and the arduino will loop on 1 and 2 only).   
6. Copy the new set of sounds on the Micro-SD card
7. Eject the Micro-SD card and put it back on the Micro-SD card reader
8. Close the stompbox case.
9. Enjoy !

## 5. How to build PopStompbox ?

### You will need...

This is the shop list of what I used, for some of them, they can be replaced by other references.

- 1x (wooden) box (I did mine myself but you can use whatever you want to use)
- 1x piezoelectric sensor
- 1x Arduino Nano
- 1x Micro-SD card reader for arduino
- 1x 9V battery
- 2x female 6.35mm jack adaptor
- 1x normally-open monostable switch for sound selection
- 1x bi-stable switch for power
- 1x led 
- 4x IN4007-like diodes
- 1x 6.8 ohms resistor
- 2x 220 ohms resistor
- 1x 1K ohms resistor
- 1x 5K ohms resistor
- 2x 10K ohms resistor
- 1x 55K ohms resistor
- 1x 100K ohms resistor
- 1x 3M ohms resistor
- 1x 1M ohms linear potentiometer for volume
- 1x Panasonic TQ2-5VDC DPDT relay
- 2x 2N3904 transistor
- 1x 100nF capacitor
- 2x 1uF capacitor
- 1x LM358N amplifier
- Several wires

### Electronical wiring layout

![Electronic circuit](https://raw.githubusercontent.com/St4ckben/PopStompbox/master/resources/electronics.PNG)
