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

static const uint8_t MAX_CORRECTION = 127;
static const uint16_t MAX_COLOR_VALUE = 1023;

void shiftbrite_init(shiftbrite *sb);

void shiftbrite_configure(shiftbrite *sb,
                          uint8_t red_correction,
                          uint8_t green_correction,
                          uint8_t blue_correction,
                          shiftbrite_clock clock);

void shiftbrite_enable(shiftbrite *sb);
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
