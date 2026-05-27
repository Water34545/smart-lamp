#include "fire.h"
#include "matrix.h"

#include <FastLED.h>

static uint8_t ff_y = 0;
static uint8_t ff_z = 0;

static float sparkX[4];
static float sparkY[4];

static bool initialized = false;

CRGBPalette16 firePalette =
    HeatColors_p;

void initFire() {

    for (uint8_t i = 0; i < 4; i++) {

        sparkY[i] = random8(MATRIX_HEIGHT);
        sparkX[i] = random8(MATRIX_WIDTH);
    }

    initialized = true;
}

void renderFire() {

    if (!initialized) {
        initFire();
    }

    uint8_t scaleX = 40;
    uint8_t scaleY = 80;

    for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {

        for (uint8_t y = 0; y < MATRIX_HEIGHT; y++) {

            uint8_t noise = inoise8(
                x * scaleX,
                (y * scaleY) + ff_y,
                ff_z
            );

            uint8_t fade =
                map(y, 0, MATRIX_HEIGHT - 1, 255, 32);

            uint8_t index =
                qsub8(noise, 255 - fade);

            CRGB color =
                ColorFromPalette(
                    firePalette,
                    index,
                    255,
                    LINEARBLEND
                );

            leds[XY(x, MATRIX_HEIGHT - 1 - y)] = color;
        }
    }

    // Sparks
    for (uint8_t i = 0; i < 4; i++) {

        uint8_t sx = sparkX[i];
        uint8_t sy = sparkY[i];

        if (sy < MATRIX_HEIGHT) {

            leds[XY(sx, sy)] += CRGB(255, 180, 80);

            leds[XY(sx, sy)].fadeToBlackBy(sy * 12);
        }

        sparkY[i] += 0.35;

        if (random8() < 40) {

            int move = random8(3) - 1;

            sparkX[i] =
                (uint8_t)((int)sparkX[i] + move + MATRIX_WIDTH)
                % MATRIX_WIDTH;
        }

        if (sparkY[i] >= MATRIX_HEIGHT) {

            sparkY[i] = random8(3);

            sparkX[i] = random8(MATRIX_WIDTH);
        }
    }

    ff_y += 3;

    if (ff_y & 0x01) {
        ff_z++;
    }

    FastLED.show();

    delay(30);
}