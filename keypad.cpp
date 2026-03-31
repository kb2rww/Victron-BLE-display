#include "keypad.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

KeypadMode keypadMode = KP_NONE;
bool keyVisible = false;

void drawKeypad() {
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextFont(2);

  tft.setCursor(10, 30);
  tft.print("Hex Keypad");

  tft.setCursor(10, 60);
  tft.print(keyVisible ? "KEY VISIBLE" : "KEY HIDDEN");

  tft.drawRect(250, 50, 50, 30, TFT_WHITE);
  tft.setCursor(260, 60);
  tft.print(keyVisible ? "HIDE" : "SHOW");
}
