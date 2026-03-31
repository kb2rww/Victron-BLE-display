#include "ui.h"
#include "datasource.h"
#include "storage.h"

void setup() {
  Serial.begin(115200);

  uiInit();            // Display, touch, backlight
  storageInit();       // NVS init
  loadSettings();      // Load saved config

  datasourceInit();    // Start BLE or TTL based on config

  uiDrawCurrentPage();
}

void loop() {
  uiHandleTouch();     // Navigation & keypad
  datasourcePoll();    // BLE or VE.Direct
  uiUpdate();          // Redraw on page change
}
