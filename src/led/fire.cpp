#include "fire.h"
#include "matrix.h"

#include <FastLED.h>

static byte heat[MATRIX_WIDTH][MATRIX_HEIGHT];

void renderFire() {

    for (int x = 0; x < MATRIX_WIDTH; x++) {

        for (int y = 1; y < MATRIX_HEIGHT; y++) {

            heat[x][y] =
                (heat[x][y] + heat[x][y - 1] + heat[x][y - 1]) / 3;
        }

        heat[x][0] = random8(160, 255);

        for (int y = 0; y < MATRIX_HEIGHT; y++) {

            CRGB color = HeatColor(heat[x][y]);

            leds[XY(x, y)] = color;
        }
    }

    FastLED.show();

    delay(35);
}