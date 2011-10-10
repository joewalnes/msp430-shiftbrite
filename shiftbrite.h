#pragma once

typedef struct {
  char data_pin;
  char clock_pin;
  char latch_pin;
} shiftbrite;

void shiftbrite_init(shiftbrite *sb);

void shiftbrite_rgb(shiftbrite* sb,
                    uint16_t red,
                    uint16_t green,
                    uint16_t blue);
