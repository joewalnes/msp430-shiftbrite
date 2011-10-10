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

void shiftbrite_init(shiftbrite *sb);

void shiftbrite_enable(shiftbrite *sb);
void shiftbrite_disable(shiftbrite *sb);

void shiftbrite_rgb(shiftbrite* sb,
                    uint16_t red,
                    uint16_t green,
                    uint16_t blue);
