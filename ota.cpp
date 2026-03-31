#include "ota.h"
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <TFT_eSPI.h>

// Access the global TFT object from ui.cpp
extern TFT_eSPI tft;

// 🔁 CHANGE THESE
static const char* WIFI_SSID = "YOUR_WIFI_SSID";
static const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";

void otaInit() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait for Wi‑Fi (non-blocking style)
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
    delay(100);
  }

  ArduinoOTA.setHostname("VictronDisplay");

  ArduinoOTA.onStart( {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(2);
    tft.setCursor(40, 100);
    tft.println("OTA Update");
    tft.setCursor(40, 130);
    tft.println("Do not power off");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    int percent = (progress * 100) / total;
    tft.fillRect(40, 170, 240, 20, TFT_BLACK);
    tft.setCursor(40, 170);
    tft.printf("Progress: %d%%", percent);
  });

 uinoOTA.onEnd( {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(40, 120);
    tft.println("Update Complete");
    delay(1000);
  });

  ArduinoOTA.onError([](ota_error_t error) {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 120);
    tft.printf("OTA Error: %d", error);
  });

  ArduinoOTA.begin();
}

void otaHandle() {
  ArduinoOTA.handle();
}
``
