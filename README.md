MSP430 ShiftBrite Library
=========================

A small C library that makes it easy to use the Texas Instruments [MSP430](http://www.ti.com/lsds/ti/microcontroller/16-bit_msp430/overview.page)
microcontroller with the
[ShiftBrite](http://docs.macetech.com/doku.php/shiftbrite) RGB LED module.

Supports a standalone single ShiftBrite, as well as chains of
multiple ShiftBrites.

Quick Start
===========

Include `shiftbrite.c` and `shiftbrite.h` in your project.

Wiring
------

The ShiftBrite module works best when it powered by a 5.5-9V DC
power supply. So typically you'll want to use a different power
source to that powering the MSP430. Ensure the ground of the
ShiftBrite supply and MSP430 supply are connected.

Connecting the ShiftBrite(s) requires 4 free pins on Port 1 of
the MSP430 (Data, Clock, Latch and Enable). The ShiftBrite
contains 'In' and 'Out' versions of these. The MSP430 should
be connected to the 'In' side of the ShiftBrite.

Multiple ShiftBrites can be chained together by connecting the
'Out' pins to the 'In' pins of the next module in the chain.

Usage
-----

1. Create a `shiftbrite` struct, set which pins the first
module in the chain is connected to and call `shiftbrite_init()`.

    shiftbrite sb;
    sb.data_pin   = BIT4; // Pin 1.4
    sb.latch_pin  = BIT5; // Pin 1.5
    sb.enable_pin = BIT6; // Pin 1.6
    sb.clock_pin  = BIT7; // Pin 1.7
    shiftbrite_init(&sb); // Setup MSP430 pins

2. Enable the ShiftBrite:

    shiftbrite_enable(&sb);

3. For each module in the chain, call `shiftbrite_rgb()`, to
load the data into the module. Each call will shift all the
values to the next module in the chain (a FIFO queue), so you
need to load the values of the furthest module first.

If there's only one module, you need only call this once.

The RGB values should be in range 0-1023.

    // Assuming there are 3 modules in the chain
    shiftbrite_rgb(&sb, 1023, 0, 0); // Set furthest to RED
    shiftbrite_rgb(&sb, 0, 1023, 0); // Set middle to GREEN
    shiftbrite_rgb(&sb, 0, 0, 1023); // Set closest to BLUE

4. 'Latch' the data. This sends a signal to each ShiftBrite
that the data has been fully loaded and they should update
the LEDs to the new values.

    shiftbrite_latch(&sb);

5. Yay! Light!

Other things you should know:

*   The ShiftBrite modules can have the overall light levels
    configured (Dot Correction) as well as the PWM clock speed.
    See `shiftbrite_configure()`

*   The ShiftBrite modules can be enabled/disabled quickly
    (i.e. turned on/off without having to reload the buffers).
    See `shiftbrite_enable()` / `shiftbrite_disable()`

*   Plenty of docs in the header file, and check out the examples.

*   If you prefer C++, there's also a C++ wrapper to the C API.
    See header and examples.

Questions
---------

**Q:** Can this be used with the [MSP430
Launchpad](http://ti.com/launchpad)?

**A:** Yes! See the examples directory for an example, complete with
wiring. What a fine way to spend $4.30.

**Q:** Can this work directly with the [Allegro
A6281](http://www.allegromicro.com/en/Products/Part_Numbers/6281/) LED
Driver?

**A:** Yes! This is basically what the ShiftBrite is. Just pre-soldered.
You try soldering one of these ICs - it's really tricky!

**Q:** Can't I just drive an RGB LED directly from the MSP430? What's
the point of the ShiftBrite?

**A:** Sure you can. But you'll need some resistors and have to handle
the [PWM](http://en.wikipedia.org/wiki/Pulse-width_modulation) timers 
yourself. Joby Taffey has a good tutorial on building a
[Launchpad RGB Lamp](http://blog.hodgepig.org/2010/09/30/jam-jar-lamp/)
using the raw components. The benefit you get from the ShiftBrite (well,
the Allegro A6281) is you can easily drive brighter LEDs from a separate
power source (which would involve a power regulator, transistors,
resistors, capacitors, etc) and chains of many indepenently controlled
LEDs from only 4 pins.

**Q:** Do I have to use the enable pin and `shiftbrite_enable()` call?

**A:** Nope. If you want to can wire the ShiftBrite enable pin directly
to the ground. Then you don't need to call enable()/disable().
