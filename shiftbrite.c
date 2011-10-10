#include <msp430x20x2.h>
#include "shiftbrite.h"

void shiftbrite_init(shiftbrite *sb) {
  P1DIR |= sb->data_pin;
  P1DIR |= sb->clock_pin;
  P1DIR |= sb->latch_pin;
}

static inline void pulse(char pin) {
  P1OUT |= pin;
  P1OUT &= ~pin;
}

static inline void shiftbit(shiftbrite* sb, uint16_t val) {
  if (val) {
    P1OUT |= sb->data_pin;
  } else {
    P1OUT &= ~(sb->data_pin);
  }
  pulse(sb->clock_pin);
}

void shiftbrite_rgb(shiftbrite* sb,
                    uint16_t red,
                    uint16_t green,
                    uint16_t blue) {
  int i;

  for (i = 0; i < 2; i++)  {
    shiftbit(sb, 0);
  }
  for (i = 9; i >= 0; i--) {
    shiftbit(sb, blue & (1 << i));
  }
  for (i = 9; i >= 0; i--) {
    shiftbit(sb, red & (1 << i));
  }
  for (i = 9; i >= 0; i--) {
    shiftbit(sb, green & (1 << i));
  }

  pulse(sb->latch_pin);
}


