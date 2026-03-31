#pragma once
#include <Arduino.h>

enum DataSource {
  SOURCE_BLE,
  SOURCE_TTL
};

extern DataSource activeSource;

struct BatteryData {
  float V;
  float I;
  float soc;
};

extern BatteryData battery;

void datasourceInit();
void datasourcePoll();
``
