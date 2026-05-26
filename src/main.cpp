#include <Arduino.h>
#include <WiFi.h>
#include <FastLED.h>

#include "ota.h"
#include "version.h"
#include "./led/fire.h"
#include "./led/matrix.h"

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

  // LED setup
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);

  // WiFi
  connectWiFi();
  checkForOTAUpdate();
}

void loop() {
  renderFire();
}