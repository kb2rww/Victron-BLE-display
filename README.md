seting up the ESP32-display for BLE/TTL input with data entry for mac addres and Key for any smart shunt device.


✅ Big Picture (Important First)
Arduino IDE works like this:

Every project is a folder
The folder must contain one .ino file
The folder name must match that .ino file
You can add unlimited .h and .cpp files
Arduino will compile everything together

✅ What we built already follows Arduino rules
✅ You are not doing anything advanced or unsupported

✅ Step 1: Create the Project Folder

Open Arduino IDE
Go to:
File → Sketchbook → Open Sketchbook Folder


Inside your sketchbook folder, create a new folder:

VictronDisplay

⚠️ This folder name matters.

✅ Step 2: Create main.ino (Required)
Inside the VictronDisplay folder:

Create a new file named:

main.ino

✅ Folder name and main file name must match
Arduino rule — non‑negotiable.
Your structure now:
VictronDisplay/
 └── main.ino


✅ Step 3: Add the Supporting Files
Now add the other files we created:
Inside the same folder, add:
ui.h
ui.cpp
keypad.h
keypad.cpp
datasource.h
datasource.cpp
storage.h
storage.cpp

Your final folder structure:
VictronDisplay/
│
├── main.ino
├── ui.h
├── ui.cpp
├── keypad.h
├── keypad.cpp
├── datasource.h
├── datasource.cpp
├── storage.h
├── storage.cpp

✅ Arduino automatically compiles .cpp
✅ Arduino automatically includes .h

✅ Step 4: Open the Project Correctly
⚠️ This is a very common mistake—avoid it
✅ Do this:

In Arduino IDE → File → Open
Select main.ino
Arduino will load all files in the folder

❌ Do NOT:

Open individual .cpp files
Copy code into one giant file
Rename main.ino


✅ Step 5: Install Required Libraries
In Arduino IDE:
Go to:
Sketch → Include Library → Manage Libraries

Install these exact libraries:

✅ Step 6: Configure TFT_eSPI (Critical)
This step must be done manually, once.
Open:
Arduino/libraries/TFT_eSPI/User_Setup.h
Make sure only these are enabled:
#define ILI9341_DRIVER

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  -1

#define TFT_WIDTH  240
#define TFT_HEIGHT 320
``
✅ This is correct for ESP32‑2432S028R

✅ Step 7: Select the Correct Board & Settings
In Arduino IDE:
Tools → Board
ESP32 Arduino → ESP32 Dev Module

Tools → Settings

Flash Frequency: 40 MHz
Flash Size: 4MB
Partition Scheme: Default
PSRAM: Disabled
Upload Speed: 921600 (or 460800 if unstable)


✅ Step 8: Compile First (Before Upload)
Click:
✔ Verify

✅ If everything is correct:

You should see “Done compiling”
No undefined references
No missing headers

If you see errors:

They usually point to a missing library
Or a typo in a filename


✅ Step 9: Upload to the ESP32‑2432S028R

Plug in USB
Click Upload
If needed:

Hold BOOT button
Release when upload begins



✅ After upload:

Screen will turn black
Text will appear (“Main Display”)
Touch will cycle pages (temporary behavior)






























LibraryAuthorTFT_eSPIBodmerXPT2046_TouchscreenPaul StoffregenNimBLE-Arduinoh2zeroAESLibDavy LandmanPreferences(Built-in with ESP32 core)
✅ Restart Arduino IDE after installing
