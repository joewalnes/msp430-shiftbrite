#pragma once

/**
 * MSP430 library for interacting with ShiftBrite RGB LED modules: 
 * http://docs.macetech.com/doku.php/shiftbrite
 *
 * Supports a standalone single ShiftBrite, as well as chains of
 * multiple ShiftBrites.
 *
 * Wiring:
 *
 *   The ShiftBrite module works best when it powered by a 5.5-9V DC
 *   power supply. So typically you'll want to use a different power
 *   source to that powering the MSP430. Ensure the ground of the
 *   ShiftBrite supply and MSP430 supply are connected.
 *
 *   Connecting the ShiftBrite(s) requires 4 free pins on Port 1 of
 *   the MSP430 (Data, Clock, Latch and Enable). The ShiftBrite
 *   contains 'In' and 'Out' versions of these. The MSP430 should
 *   be connected to the 'In' side of the ShiftBrite.
 *
 *   Multiple ShiftBrites can be chained together by connecting the
 *   'Out' pins to the 'In' pins of the next module in the chain.
 *
 * Usage:
 *
 *   1. Allocate a global 'shiftbrite' struct.
 *
 *     shiftbrite sb;
 *
 *   2. At startup, call 'shiftbrite_init()' function, passing in
 *   which pins the first  module in the chain is connected to.
 *
 *     shiftbrite_init(&sb,
 *                     BIT4,  // Data pin   : 1.4
 *                     BIT5,  // Latch pin  : 1.5
 *                     BIT6,  // Enable pin : 1.6
 *                     BIT7); // Clock pin  : 1.7
 *
 *   3. Enable the ShiftBrite:
 *
 *     shiftbrite_enable(&sb);
 *
 *   4. For each module in the chain, call 'shiftbrite_rgb()', to
 *   load the data into the module. Each call will shift all the
 *   values to the next module in the chain (a FIFO queue), so you
 *   need to load the values of the furthest module first.
 *
 *   If there's only one module, you need only call this once.
 *
 *   The RGB values should be in range 0-1023.
 *
 *     // Assuming there are 3 modules in the chain
 *     shiftbrite_rgb(&sb, 1023, 0, 0); // Set furthest to RED
 *     shiftbrite_rgb(&sb, 0, 1023, 0); // Set middle to GREEN
 *     shiftbrite_rgb(&sb, 0, 0, 1023); // Set closest to BLUE
 *
 *   5. 'Latch' the data. This sends a signal to each ShiftBrite
 *   that the data has been fully loaded and they should update
 *   the LEDs to the new values.
 *
 *     shiftbrite_latch(&sb);
 *
 *   6. Yay! Light!
 *
 * Other things you should know:
 *
 *   * The ShiftBrite modules can have the overall light levels
 *     configured (Dot Correction) as well as the PWM clock speed.
 *     See shiftbrite_configure()
 *
 *   * The ShiftBrite modules can be enabled/disabled quickly
 *     (i.e. turned on/off without having to reload the buffers).
 *     See shiftbrite_enable() / shiftbrite_disable()
 *
 * 2011, Joe Walnes <joe@walnes.com>
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char data_pin;
  char latch_pin;
  char enable_pin;
  char clock_pin;
} shiftbrite;

/**
 * Should be called once at startup, to configure the pins
 * on the controller.
 */
void shiftbrite_init(shiftbrite *sb,
                     char data_pin,
                     char latch_pin,
                     char enable_pin,
                     char clock_pin);

/**
 * See shiftbrite_configure().
 */
typedef enum {
  CLOCK_800MHZ, // Default
  CLOCK_400MHZ,
  CLOCK_EXTERNAL,
  CLOCK_200MHZ
} shiftbrite_clock;

/**
 * Optional: configure color correction codes and clock speed.
 *
 * Correction codes allow you to tweak the output current of
 * the LEDs - useful as a global brightness control and also to
 * correct white balance caused by the LEDs not all being the
 * same brightness.
 *
 * The correction values should be in the range 0 (dimmest) to
 * 127 (brightest). Refere to the 'Dot Correction' section of
 * the Allegro A6281 datasheet for details.
 * http://www.allegromicro.com/en/Products/Part_Numbers/6281/6281.pdf
 *
 * The clock speed is also defined in the datasheet.
 *
 * When the system is powered up, the default correction values
 * are all 127, and the clock is CLOCK_800MHZ.
 *
 * After calling shiftbrite_configure(), call shiftbrite_commit().
 *
 * If N modules are wired in a chain, shiftbrite_configure() should
 * be called N times, followed by 1 call to shiftbrite_commit().
 */
void shiftbrite_configure(shiftbrite *sb,
                          uint8_t red_correction,
                          uint8_t green_correction,
                          uint8_t blue_correction,
                          shiftbrite_clock clock);

/**
 * Enable LED module. Enabling/disabling is a useful way to
 * turn it on or off without having to reload the RGB or configuration
 * values.
 */
void shiftbrite_enable(shiftbrite *sb);

/**
 * See shiftbrite_disable().
 */
void shiftbrite_disable(shiftbrite *sb);

/**
 * Load ShiftBrite with RGB values, which should be in
 * range 0-1023. See comments at top of this file for
 * detailed description.
 */
void shiftbrite_rgb(shiftbrite* sb,
                    uint16_t red,
                    uint16_t green,
                    uint16_t blue);

/**
 * 'Latches' the values in to the ShiftBrite(s).
 *
 * After loading the ShiftBrite(s) with data, this signals all of them
 * to apply the changes.
 */
void shiftbrite_latch(shiftbrite* sb);

#ifdef __cplusplus
} // extern "C"

// C++ only....

/**
 * C++ wrapper to ShiftBrite C library.
 * Adds no new functionality, just makes it more C++y.
 */
class ShiftBrite {

public:

  shiftbrite sb;

  ShiftBrite() {}

  /** See shiftbrite_init() */
  void init(char data_pin,
            char latch_pin,
            char enable_pin,
            char clock_pin) {
    shiftbrite_init(&sb,
                    data_pin,
                    latch_pin,
                    enable_pin,
                    clock_pin);
  }

  /** See shiftbrite_configure() */
  void configure(uint8_t red_correction,
                 uint8_t green_correction,
                 uint8_t blue_correction,
                 shiftbrite_clock clock = CLOCK_800MHZ) {
    shiftbrite_configure(&sb,
                         red_correction,
                         green_correction,
                         blue_correction,
                         clock);
  }

  /** See shiftbrite_enable() */
  void enable() {
    shiftbrite_enable(&sb);
  }

  /** See shiftbrite_disable() */
  void disable() {
    shiftbrite_disable(&sb);
  }

  /** See shiftbrite_rgb() */
  void rgb(uint16_t red,
           uint16_t green,
           uint16_t blue) {
    shiftbrite_rgb(&sb, red, green, blue);
  }

  /** See shiftbrite_latch() */
  void latch() {
    shiftbrite_latch(&sb);
  }

};

#endif
