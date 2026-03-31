#pragma once
#include <Arduino.h>

enum Page {
  PAGE_MAIN,
  PAGE_MENU,
  PAGE_SOURCE,
  PAGE_BLE_SETUP,
  PAGE_KEYPAD,
  PAGE_DIAG
};

extern Page currentPage;

void uiInit();
void uiDrawCurrentPage();
void uiHandleTouch();
void uiUpdate();
