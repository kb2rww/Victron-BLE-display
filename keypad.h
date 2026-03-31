#pragma once
#include <Arduino.h>

enum KeypadMode {
  KP_NONE,
  KP_MAC,
  KP_KEY
};

extern KeypadMode keypadMode;
extern bool keyVisible;

void drawKeypad();
