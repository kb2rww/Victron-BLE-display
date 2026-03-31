#include "datasource.h"

#include <NimBLEDevice.h>

DataSource activeSource = SOURCE_BLE;

BatteryData battery;

void datasourceInit() {
  if (activeSource == SOURCE_BLE) {
    NimBLEDevice::init("");
  } else {
    Serial2.begin(19200, SERIAL_8N1, 16);
  }
}

void datasourcePoll() {
  if (activeSource == SOURCE_TTL) {
    if (Serial2.available()) {
      String line = Serial2.readStringUntil('\n');
      if (line.startsWith("V\t")) {
        battery.V = line.substring(2).toInt() / 1000.0;
      }
    }
  }
}
