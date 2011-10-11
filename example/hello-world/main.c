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
 * P1.4    DI (Data In)
 * P1.5    LI (Latch In)
 * P1.6    EI (Enable In)
 * P1.7    CI (Clock In)
 *
 * The ShiftBrite V+ and Ground should be connected to a DC 5.5-9V power supply.
 * The Ground should be connected to the MSP430 Ground.
 *
 * Joe Walnes <joe@walnes.com>
 */
int main(void) {
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer. Standard MSP430 setup.

  shiftbrite sb;
  sb.data_pin   = BIT4; // Pin 1.4
  sb.latch_pin  = BIT5; // Pin 1.5
  sb.enable_pin = BIT6; // Pin 1.6
  sb.clock_pin  = BIT7; // Pin 1.7

  shiftbrite_quick_rgb(&sb, 0, 1023, 0); // Green

  for(;;) { /* spin forever */ }
}
 
