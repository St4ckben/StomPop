# PopStompbox

**Hey ! Welcome to this DIY Stompbox project.**

First of all, what is a stompbox ? According to lexico.com, there are several definitions :
> * A foot-operated device that produces a sound effect on an electric guitar.
> * A wooden box used as a percussion instrument, sounded by being struck with the feet or hands.

Here, I am talking about the second one. Basically, I just want something to hit with the foot producing a "clap! clap!" to give us the rhythm while I play guitar. :-)

If you are in, follow me !

## Main features

- Active (9V battery powered) or passive (unpowered) mode
- Sound selection in active mode (persistent accross reboots)
- Volume ajustment for both active and passive mode
- Input 6.35mm jack for optional guitar pluging
- Support of mono 8-bits 32000 Hz (best results achieved with 22050 Hz)

## Well, what's the PopStompbox ?

## Basic usage

### Active or passive mode

PopStompbox can be used in several ways.

The easiest way to use PopStombox is in passive mode. In such unpowered mode, the stompbox only needs do be plugged to an amplifier and that's it. 
It consists in a piezoelectric microphone connected to the output jack as shown below (simplified scheme). The produced sound is the amplified sound of the foot hitting the wood box.

<img src="https://raw.githubusercontent.com/St4ckben/PopStompbox/master/resources/passive_mode.png" width="500" title="Passive mode">

The active mode, one the other hand, requires a 9V battery to work. Instead of hearing an amplified wooden sound, the piezoelectric microphone is only used as a sensor and the arduino is producing a numeric sound from a mono 8-bit wav file. 

<img src="https://raw.githubusercontent.com/St4ckben/PopStompbox/master/resources/active_mode.png" width="500" title="Passive mode">

**Switching from passive mode to active mode is done easily by powering on the PopStompbox.**
An internal relay is diverting the electrical circuit towards the arduino microcontroller.

### How to plug my guitar and my amp ? 

If the amplifier is equiped with several inputs, the guitar and the stompbox can be both plugged directly onto the amplifier as shown below.

As the stompbox is equiped with an input 6.35mm jack, it is also possible to plug the guitar, the stompbox and the amp in series as shown below. The main advantage of this solution is that only one input is required on the amplifier. 



## How to update PopStompbox

### Update of the arduino code

### Change the onboarded sounds 

## How to build PopStompbox

### You will need...

### Electronical wiring layout


