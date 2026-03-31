#include "storage.h"
#include "datasource.h"

#include <Preferences.h>

static Preferences prefs;

void storageInit() {
  prefs.begin("victron", false);
}

void loadSettings() {
  activeSource = (DataSource)prefs.getUChar("source", SOURCE_BLE);
}

void saveSourceSetting() {
  prefs.putUChar("source", activeSource);
}
