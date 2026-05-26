#pragma once

#include <FastLED.h>

#define LED_PIN     2
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 15
#define NUM_LEDS 120

extern CRGB leds[NUM_LEDS];

uint16_t XY(uint8_t x, uint8_t y);