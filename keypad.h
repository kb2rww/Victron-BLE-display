#pragma once
#include <Arduino.h>

enum KeypadMode {
  KP_NONE,
  KP_EDIT_MAC,
  KP_EDIT_KEY
};

extern KeypadMode keypadMode;
extern bool keyVisible;

void drawKeypad();
