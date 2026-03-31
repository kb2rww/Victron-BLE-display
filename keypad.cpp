#include "keypad.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

KeypadMode keypadMode = KP_NONE;
bool keyVisible = false;

void drawKeypad() {
  tft.setTextFont(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.setCursor(10, 30);
  tft.print("Hex Keypad");

  tft.setCursor(10, 60);
  tft.print(keyVisible ? "KEY VISIBLE" : "KEY HIDDEN");

  tft.drawRect(240, 50, 70, 30, TFT_WHITE);
  tft.setCursor(255, 60);
  tft.print(keyVisible ? "HIDE" : "SHOW");
}
