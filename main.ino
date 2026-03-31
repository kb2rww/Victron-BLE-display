#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <NimBLEDevice.h>
#include <AESLib.h>
#include <Preferences.h>

/* ===================== UI / HARDWARE ===================== */
#define TFT_BL     21
#define TOUCH_CS  33
#define TOUCH_IRQ 36
#define VEDIRECT_RX 16

TFT_eSPI tft;
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);
Preferences prefs;
AESLib aes;

/* ===================== STATE ===================== */
enum Page { PAGE_MAIN, PAGE_SOURCE, PAGE_BLE_SETUP, PAGE_KEYPAD, PAGE_DIAG };
enum DataSource { SOURCE_BLE, SOURCE_TTL };

Page currentPage = PAGE_MAIN;
DataSource dataSource = SOURCE_BLE;

/* ===================== BLE CONFIG ===================== */
char bleMac[18];
uint8_t bleKey[16];
NimBLEClient* client = nullptr;
NimBLERemoteCharacteristic* notifyChar = nullptr;

/* ===================== DIAGNOSTICS ===================== */
uint32_t blePackets = 0;
uint32_t vedLines = 0;
bool bleConnected = false;

/* ===================== BATTERY DATA ===================== */
struct Battery {
  float V, Vs;
  float I, P;
  float soc;
  float usedAh;
  int   ttg;
} battery;

/* ===================== FORWARD DECL ===================== */
void drawPage();
void handleTouch();
void bleConnect();
void bleDisconnect();
void pollVEDirect();

/* ===================== SETUP ===================== */
void setup() {
  Serial.begin(115200);
  Serial2.begin(19200, SERIAL_8N1, VEDIRECT_RX);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  ledcAttachPin(TFT_BL, 0);
  ledcSetup(0, 5000, 8);

  ts.begin();
  ts.setRotation(1);

  /* ---- Load NVS ---- */
  prefs.begin("victron", false);
  dataSource = (DataSource)prefs.getUChar("source", SOURCE_BLE);
  prefs.getString("blemac", bleMac, sizeof(bleMac));
  prefs.getBytes("blekey", bleKey, 16);
  bool night = prefs.getBool("night", false);
  ledcWrite(0, night ? 40 : 200);

  /* ---- Init BLE if selected ---- */
  if (dataSource == SOURCE_BLE) bleConnect();
}

/* ===================== LOOP ===================== */
void loop() {
  handleTouch();

  if (dataSource == SOURCE_TTL) pollVEDirect();

  drawPage();
}

/* ===================== PAGE DISPATCH ===================== */
void drawPage() {
  static Page lastPage = PAGE_MAIN;
  if (lastPage == currentPage) return;
  lastPage = currentPage;

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  switch (currentPage) {
    case PAGE_MAIN:        drawMain(); break;
    case PAGE_SOURCE:      drawSource(); break;
    case PAGE_BLE_SETUP:   drawBLESetup(); break;
    case PAGE_KEYPAD:      drawKeypad(); break;
    case PAGE_DIAG:        drawDiagnostics(); break;
  }
}
