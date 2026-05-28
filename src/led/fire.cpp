#include "fire.h"
#include "matrix.h"

#include <FastLED.h>

#define FIRE_WIDTH MATRIX_WIDTH
#define FIRE_HEIGHT MATRIX_HEIGHT

static uint8_t matrixValue[FIRE_HEIGHT][FIRE_WIDTH];
static uint8_t line[FIRE_WIDTH];

static uint8_t pcnt = 0;

const uint8_t valueMask[FIRE_HEIGHT][FIRE_WIDTH] = {
    {32, 0, 0, 0, 0, 0, 0, 32},
    {64, 0, 0, 0, 0, 0, 0, 64},
    {96, 32, 0, 0, 0, 0, 32, 96},
    {128, 64, 32, 0, 0, 32, 64, 128},
    {160, 96, 64, 32, 32, 64, 96, 160},
    {192, 128, 96, 64, 64, 96, 128, 192},
    {255, 160, 128, 96, 96, 128, 160, 255},
    {255, 192, 160, 128, 128, 160, 192, 255},
    {255, 220, 185, 150, 150, 185, 220, 255},
    {255, 255, 220, 185, 185, 220, 255, 255},
    {255, 255, 255, 220, 220, 255, 255, 255},
    {255, 255, 255, 255, 255, 255, 255, 255},
    {255, 255, 255, 255, 255, 255, 255, 255},
    {255, 255, 255, 255, 255, 255, 255, 255},
    {255, 255, 255, 255, 255, 255, 255, 255}
};

const uint8_t hueMask[FIRE_HEIGHT][FIRE_WIDTH] = {
    {1, 8, 16, 24, 24, 16, 8, 1},
    {1, 8, 16, 20, 20, 16, 8, 1},
    {1, 8, 13, 19, 19, 13, 8, 1},
    {1, 5, 11, 13, 13, 11, 5, 1},
    {1, 5, 11, 11, 11, 11, 5, 1},
    {0, 1, 5, 8, 8, 5, 1, 0},
    {0, 0, 1, 5, 5, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

void generateLine() {

    for (uint8_t x = 0; x < FIRE_WIDTH; x++) {

        line[x] = random8(120, 255);
    }
}

void shiftUp() {

    for (int y = FIRE_HEIGHT - 1; y > 0; y--) {

        for (int x = 0; x < FIRE_WIDTH; x++) {

            matrixValue[y][x] = matrixValue[y - 1][x];
        }
    }

    for (int x = 0; x < FIRE_WIDTH; x++) {

        matrixValue[0][x] = line[x];
    }
}

void drawFrame(uint8_t pcnt) {

    for (int y = FIRE_HEIGHT - 1; y > 0; y--) {

        for (int x = 0; x < FIRE_WIDTH; x++) {

            int value =
                (
                    (100 - pcnt) * matrixValue[y][x]
                    +
                    pcnt * matrixValue[y - 1][x]
                ) / 100;

            value -= valueMask[y][x];

            value = max(0, value);

            leds[XY(x, y)] = CHSV(
                8 + hueMask[y][x],
                255,
                value
            );
        }
    }

    for (int x = 0; x < FIRE_WIDTH; x++) {

        leds[XY(x, 0)] = CHSV(
            8 + hueMask[0][x],
            255,
            (
                (100 - pcnt) * matrixValue[0][x]
                +
                pcnt * line[x]
            ) / 100
        );
    }
}

void renderFire() {

    if (pcnt >= 100) {

        shiftUp();

        generateLine();

        pcnt = 0;
    }

    drawFrame(pcnt);

    FastLED.show();

    pcnt += 25;

    delay(30);
}