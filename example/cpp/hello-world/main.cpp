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
 * The ShiftBrite V+ and Ground should be connected to a DC 5.5-9V
 * power supply. The Ground should be connected to the MSP430 Ground.
 *
 * Joe Walnes <joe@walnes.com>
 */

ShiftBrite sb;

int main() {
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer. Standard MSP430 setup.

  // Configure MSP430 pins
  sb.init(BIT4,  // Data pin   : 1.4
          BIT5,  // Latch pin  : 1.5
          BIT6,  // Enable pin : 1.6
          BIT7); // Clock pin  : 1.7

  // At startup, the module is disabled. Enable it.
  sb.enable();

  // Load RGB data into module.
  // This is for a single module - if there were more modules
  // chained together, this should be called for each module
  // with the appropriate color.
  sb.rgb(0, 0, 1023); // Blue

  // Signal ShiftBrite module(s) we're done loading data.
  // This will make the LEDs light the appropriate color(s).
  sb.latch();

  for(;;) { /* spin forever */ }
}

