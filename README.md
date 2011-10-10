MSP430 ShiftBrite Library
=========================

A small C library that makes it easy to use the Texas Instruments [MSP430](http://www.ti.com/lsds/ti/microcontroller/16-bit_msp430/overview.page)
microcontroller with the
[ShiftBrite](http://docs.macetech.com/doku.php/shiftbrite) RGB LED module.

Quick Start
-----------

Include shiftbrite.c and shiftbrite.h in your project.

Connect the ground and V+ pins to your power supply. If you want to
power the ShiftBrite from a separate power source to the MSP430, that's
fine, so long as you connect the grounds together.

Connect the ShiftBrite 'Enable', 'Clock', 'Latch' and 'Data' pins to
free pins on the MSP430. Assuming these are connected to pins 1.0, 1.1,
1.2 and 1.3 respectively. Initialize the library:

    shiftbrite sb;
    sb.enable_pin = BIT0; // Pin 1.0
    sb.clock_pin  = BIT1; // Pin 1.1
    sb.latch_pin  = BIT2; // Pin 1.2
    sb.data_pin   = BIT3; // Pin 1.3
    shiftbrite_init(&sb);

To enable or disable the LED:

    shiftbrite_enable(&sb);
    shiftbrite_disable(&sb);

Then to set the color of the RGB, call:

    shiftbrite_rgb(&sb, RED, GREEN, BLUE);
    // Where RED/GREEN/BLUE are uint8_t in range 0-1023

That's it.


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

**A:** Sure you can. But you have to configure timers for
[PWM](http://en.wikipedia.org/wiki/Pulse-width_modulation) and you'll
probably want to separate the power supply from the MSP430 (which
involves a power regulator, some transistors, resistors and capacitors).
The ShiftBrite (well, the Allegro A6281) takes care of that for you.

**Q:** Do I have to use the enable pin and `shiftbrite_enable()` call?

**A:** Nope. If you want to can wire the ShiftBrite enable pin directly
to the ground. Then you don't need to call enable()/disable().
