// MightyMacro Code Template
// ESP32-Enabled Macro Keyboard
// Ruth Carraway || 9/12/22                 <------ UPDATE THIS

// Buttons
#include <Bounce2.h>                      // Bounce2 Library
const uint8_t buttonPins[9] = {23,22,21,19,18,17,16,25,26};// Fill in { } with list of GPIO pins **done
Bounce * buttons = new Bounce[9];         // Creates an array of Bounce objects

int testPin = 26;
boolean testState;
// Bluetooth
// Additional documentation available here:  https://github.com/T-vK/ESP32-BLE-Keyboard
#include <BleKeyboard.h>                                      // BleKeyboard Library          
BleKeyboard bleKeyboard("MightyMash", "Ruth Carraway", 100);  // Replace Device Name / Manufacturer w/ your info **done

void setup() {
  Serial.begin(115200);
 
 
  initButtons();                      // Initialize Buttons on Startup
  initBattery();                      // Initialize Battery on Startup
  bleKeyboard.begin();                // Begin Bluetooth Connection
}

void loop() {
 

  if(bleKeyboard.isConnected()){      // If Bluetooth is Connected
    readButtons();                    // Read State of Buttons and Perform Functions
    updateBattery();                  // Update Battery Status if Needed
  }
}
