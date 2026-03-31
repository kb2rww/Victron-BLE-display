#include "ui.h"
#include "datasource.h"
#include "keypad.h"

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#define TFT_BL     21
#define TOUCH_CS  33
#define TOUCH_IRQ 36

TFT_eSPI tft;
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);

Page currentPage = PAGE_MAIN;
static Page lastPage = PAGE_DIAG;

/* Simple hit detection */
static bool inside(int x,int y,int rx,int ry,int rw,int rh){
  return x>=rx && x<=rx+rw && y>=ry && y<=ry+rh;
}

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
      tft.setCursor(10, 80);
      tft.print("Source Select");
      tft.setCursor(10, 120);
      tft.print("Diagnostics");
      break;

    case PAGE_SOURCE:
      tft.setCursor(10, 40);
      tft.print("Select Source");
      tft.setCursor(10, 80);
      tft.print("BLE");
      tft.setCursor(10, 120);
      tft.print("TTL");
      break;

    case PAGE_BLE_SETUP:
      tft.setCursor(10, 40);
      tft.print("BLE Setup");
      tft.setCursor(10, 80);
      tft.print("Edit MAC");
      tft.setCursor(10, 120);
      tft.print("Edit KEY");
      break;

    case PAGE_KEYPAD:
      drawKeypad();
      break;

    case PAGE_DIAG:
      tft.setCursor(10, 40);
      tft.printf("Heap: %u", ESP.getFreeHeap());
      tft.setCursor(10, 80);
      tft.printf("Source: %s",
        activeSource == SOURCE_BLE ? "BLE" : "TTL");
      break;
  }
}

void uiHandleTouch() {
  if (!ts.touched()) return;

  TS_Point p = ts.getPoint();
  int x = map(p.x, 200, 3800, 0, 320);
  int y = map(p.y, 200, 3800, 0, 240);

  if (currentPage == PAGE_MAIN) {
    if (inside(x,y,260,0,60,30)) currentPage = PAGE_MENU;
  }
  else if (currentPage == PAGE_MENU) {
    if (inside(x,y,0,70,320,40)) currentPage = PAGE_SOURCE;
    if (inside(x,y,0,110,320,40)) currentPage = PAGE_DIAG;
  }
  else if (currentPage == PAGE_SOURCE) {
    if (inside(x,y,0,70,160,40)) activeSource = SOURCE_BLE;
    if (inside(x,y,160,70,160,40)) activeSource = SOURCE_TTL;
    currentPage = PAGE_MAIN;
  }
  else if (currentPage == PAGE_DIAG) {
    currentPage = PAGE_MAIN;
  }

  uiDrawCurrentPage();
  delay(200);
}

void uiUpdate() {
  if (lastPage != currentPage) {
    lastPage = currentPage;
    uiDrawCurrentPage();
  }
}
