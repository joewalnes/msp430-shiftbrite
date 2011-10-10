#include <msp430x20x2.h>
#include "shiftbrite.h"

/**
 * The 'hello world' of ShiftBrite.
 *
 * Simply makes the RGB turn a single color.
 *
 * Wiring:
 *
 * MSP430  ShiftBrite
 * ------  ----------
 * P1.0    EI (Enable In)
 * P1.1    CI (Clock In)
 * P1.2    LI (Latch In)
 * P1.3    DI (Data In)
 *
 * The ShiftBrite V+ and Ground should be connected to a DC 5-15V power supply.
 * The Ground should be connected to the MSP430 Ground.
 *
 * Joe Walnes <joe@walnes.com>
 */
int main(void) {
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer. Standard MSP430 setup.

  shiftbrite sb;
  sb.enable_pin = BIT0; // Pin 1.0
  sb.clock_pin  = BIT1; // Pin 1.1
  sb.latch_pin  = BIT2; // Pin 1.2
  sb.data_pin   = BIT3; // Pin 1.3

  shiftbrite_init(&sb);
  shiftbrite_enable(&sb);

  shiftbrite_rgb(&sb, 1023, 0, 0); // Green
  //shiftbrite_rgb(&sb, 0, 1023, 0); // Red
  //shiftbrite_rgb(&sb, 0, 0, 1023); // Blue
}
 
