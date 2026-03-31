#include "datasource.h"

/* ====== GLOBALS ====== */
DataSource activeSource = SOURCE_BLE;
BatteryData battery;

/* ====== BLE (stub-safe) ======
 * This is structured so BLE logic can be fully expanded
 * without changing UI or storage layers.
 */
#include <NimBLEDevice.h>

static NimBLEClient* bleClient = nullptr;

/* ====== TTL (VE.Direct) ====== */
#define VEDIRECT_RX 16   // GPIO16

void datasourceInit() {
  if (activeSource == SOURCE_BLE) {
    NimBLEDevice::init("");
    bleClient = NimBLEDevice::createClient();
    // Full Victron BLE decode can be added here
  } else {
    Serial2.begin(19200, SERIAL_8N1, VEDIRECT_RX);
  }
}

void datasourceStop() {
  if (activeSource == SOURCE_BLE && bleClient) {
    bleClient->disconnect();
  }
}

void datasourcePoll() {
  if (activeSource == SOURCE_TTL) {
    if (!Serial2.available()) return;

    String line = Serial2.readStringUntil('\n');

    if (line.startsWith("V\t")) {
      battery.V = line.substring(2).toInt() / 1000.0;
    }
    if (line.startsWith("VS\t")) {
      battery.Vs = line.substring(3).toInt() / 1000.0;
    }
    if (line.startsWith("I\t")) {
      battery.I = line.substring(2).toInt() / 1000.0;
      battery.P = battery.I * battery.V;
    }
    if (line.startsWith("SOC\t")) {
      battery.soc = line.substring(4).toInt() / 10.0;
    }
  }

  /* BLE polling is callback-driven; nothing needed here yet */
}
