#include <Arduino.h>
#include <WiFi.h>
#include <FastLED.h>

#include "ota.h"
#include "version.h"

#define LED_PIN     2
#define NUM_LEDS    120
#define BRIGHTNESS  80
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// WiFi
const char* ssid = "VirreyTelecentro";
const char* password = "virrey2428644";

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("BOOT START");

  // LED setup
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS); // Яркость (0-255)

  // WiFi
  connectWiFi();
  checkForOTAUpdate();
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green;   // Задаем красный цвет
    FastLED.show();        // Отправляем команду на отображение
    FastLED.delay(50);
    leds[i] = CRGB::Black; // Выключаем светодиод перед следующим шагом
  }
}