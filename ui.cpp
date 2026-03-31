#include "ui.h"
#include "keypad.h"
#include "datasource.h"

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#define TFT_BL 21
#define TOUCH_CS 33
#define TOUCH_IRQ 36

TFT_eSPI tft;
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);

Page currentPage = PAGE_MAIN;
static Page lastPage = PAGE_DIAG;

void uiInit() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  ledcAttachPin(TFT_BL, 0);
  ledcSetup(0, 5000, 8);
  ledcWrite(0, 200);

  ts.begin();
  ts.setRotation(1);
}

void uiDrawCurrentPage() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextFont(2);

  switch (currentPage) {
    case PAGE_MAIN:
      tft.setCursor(10, 40);
      tft.print("Main Display");
      break;

    case PAGE_MENU:
      tft.setCursor(10, 40);
      tft.print("Menu");
      break;

    case PAGE_SOURCE:
      tft.setCursor(10, 40);
      tft.print("Data Source");
      break;

    case PAGE_BLE_SETUP:
      tft.setCursor(10, 40);
      tft.print("BLE Setup");
      break;

    case PAGE_KEYPAD:
      drawKeypad();
      break;

    case PAGE_DIAG:
      tft.setCursor(10, 40);
      tft.printf("Free Heap: %u", ESP.getFreeHeap());
      break;
  }
}

void uiHandleTouch() {
  if (!ts.touched()) return;

  currentPage = (Page)((currentPage + 1) % 6);
  uiDrawCurrentPage();
  delay(300); // debounce
}

void uiUpdate() {
  if (lastPage != currentPage) {
    lastPage = currentPage;
    uiDrawCurrentPage();
  }
}
