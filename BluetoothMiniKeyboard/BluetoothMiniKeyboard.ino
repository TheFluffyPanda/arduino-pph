#include "heltec.h"
#include <BleKeyboard.h> // https://github.com/T-vK/ESP32-BLE-Keyboard

// Name, manufacturer, initial battery level
BleKeyboard bleKeyboard("PandaBoard", "PHowie", 100);
void sendSMS(const String& thisIsAString)

void draw(const String& keyPressed){
  Heltec.display -> clear();
  Heltec.display -> drawString(0, 0, "Keyboard Mode");
  Heltec.display -> drawString(0, 20, KeyPressed);
  Heltec.display -> display();
}

void setup() {
  Serial.begin(9600);
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
  bleKeyboard.begin();
  bleKeyboard.setBatteryLevel(80);
}

void loop() {
  char key = keypad.getKey();

  draw("Welcome");
 
  // Only do something with the keypress if we
  // are connected to something via bluetooth
  
  if (bleKeyboard.isConnected() && key) {
    Serial.println(key);
    switch (key) {
      case '1_1':
        draw("");
        break;
      case '1_2':
        draw("");
        break;
      case '1_3':
        draw("");
        break;
      case '1_4':
        draw("");
        break;
      case '2_1':
        draw("Row 2 Button ");
        break;
      case '2_2':
        draw("Row 2 Button ");
        break;
      case '2_3':
        draw("Row 2 Button ");
        break;
      case '2_4':
        draw("Row 2 Button 4");
        break;
      case '3_1':
        draw("Row 3 Button 1");
        break;
      case '3_2':
        draw("Row 3 Button 2");
        break;
      case '3_3':
        draw("Row 3 Button 3");
        break;
      case '3_4':
        draw("Row 3 Button 4");
        break; 
    }

    delay(100);
    bleKeyboard.releaseAll(); // this releases the buttons
  }
}
