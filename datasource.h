#pragma once
#include <Arduino.h>

enum DataSource {
  SOURCE_BLE = 0,
  SOURCE_TTL = 1
};

extern DataSource activeSource;

/* Battery data shared with UI */
struct BatteryData {
  float V;
  float Vs;
  float I;
  float P;
  float soc;
  float usedAh;
  int   ttg;
};

extern BatteryData battery;

void datasourceInit();
void datasourcePoll();
void datasourceStop();
