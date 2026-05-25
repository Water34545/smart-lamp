#include "ota.h"

#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <ArduinoJson.h>

#include "version.h"

String versionURL =
    "https://raw.githubusercontent.com/Water34545/smart-lamp/main/build/version.json";

void checkForOTAUpdate() {

    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure();

    Serial.println("Checking firmware version...");

    http.begin(versionURL);

    int httpCode = http.GET();

    if (httpCode != 200) {
        Serial.println("Failed to fetch version.json");
        http.end();
        return;
    }

    String payload = http.getString();

    Serial.println("PAYLOAD:");
    Serial.println(payload);

    http.end();

    DynamicJsonDocument doc(512);

    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
        Serial.println("JSON parse failed");
        return;
    }

    String latestVersion = doc["version"];
    String firmwareURL = doc["firmware"];

    Serial.print("Current version: ");
    Serial.println(FW_VERSION);

    Serial.print("Latest version: ");
    Serial.println(latestVersion);

    if (latestVersion == FW_VERSION) {
        Serial.println("Already up to date");
        return;
    }

    Serial.println("Starting OTA update...");

    t_httpUpdate_return result = httpUpdate.update(client, firmwareURL);

    switch (result) {

        case HTTP_UPDATE_FAILED:
            Serial.printf(
                "Update failed. Error (%d): %s\n",
                httpUpdate.getLastError(),
                httpUpdate.getLastErrorString().c_str()
            );
            break;

        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("No updates");
            break;

        case HTTP_UPDATE_OK:
            Serial.println("Update success");
            break;
    }
}