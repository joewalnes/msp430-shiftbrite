#pragma once

/**
 * Joe Walnes <joe@walnes.com>
 */

typedef struct {
  char data_pin;
  char clock_pin;
  char latch_pin;
  char enable_pin;
} shiftbrite;

typedef enum {
  CLOCK_800MHZ,
  CLOCK_400MHZ,
  CLOCK_EXTERNAL,
  CLOCK_200MHZ
} shiftbrite_clock;

/**
 * Should be called at startup, after the pins have been set
 * on the shiftbrite struct. This will configure the pins
 * on the controller.
 */
void shiftbrite_init(shiftbrite *sb);

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

void shiftbrite_rgb(shiftbrite* sb,
                    uint16_t red,
                    uint16_t green,
                    uint16_t blue);

void shiftbrite_commit(shiftbrite* sb);

static inline void shiftbrite_quick_rgb(shiftbrite* sb,
                                        uint16_t red,
                                        uint16_t green,
                                        uint16_t blue) {
  shiftbrite_init(sb);
  shiftbrite_enable(sb);
  shiftbrite_rgb(sb, red, green, blue);
  shiftbrite_commit(sb);
}
