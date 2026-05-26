#include "matrix.h"

CRGB leds[NUM_LEDS];

uint16_t XY(uint8_t x, uint8_t y) {

    if (x % 2 == 0) {
        return x * MATRIX_HEIGHT + y;
    } else {
        return x * MATRIX_HEIGHT + (MATRIX_HEIGHT - 1 - y);
    }
}