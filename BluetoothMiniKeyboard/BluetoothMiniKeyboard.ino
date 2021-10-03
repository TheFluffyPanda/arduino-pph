#include "heltec.h"

#define USE_NIMBLE
#include <BleKeyboard.h> // https://github.com/T-vK/ESP32-BLE-Keyboard

// Pin definitions
#define KEY_1_1 25
#define KEY_1_2 37
#define KEY_1_3 38
#define KEY_1_4 39
#define KEY_2_1 34
#define KEY_2_2 35
#define KEY_2_3 32
#define KEY_2_4 33
#define KEY_3_1 22
#define KEY_3_2 19
#define KEY_3_3 23
#define KEY_3_4 18

// Name, manufacturer, initial battery level
BleKeyboard bleKeyboard("PandaBoard", "PHowie", 100);

void draw(const String& keyPressed){
  Heltec.display -> clear();
  Heltec.display -> drawString(0, 0, "Keyboard Mode");
  Heltec.display -> drawString(0, 20, keyPressed);
  Heltec.display -> display();
}

// Button helper class for handling press/release and debouncing
class button {
  public:
  const char key;

  button(uint8_t k) : key(k){}

  void press(boolean state){
    if(state == pressed || (millis() - lastPressed  <= debounceTime)){
      return; // Nothing to see here, folks
    }

    lastPressed = millis();
    // Only do something with the keypress if we
    // are connected to something via bluetooth
    if (bleKeyboard.isConnected() && state){
      Serial.println(key);
      switch (key) {
        case KEY_1_1:
          // cmd-e (gmeet cam toggle)
          bleKeyboard.print("Button 1.1");
          //bleKeyboard.press(KEY_LEFT_GUI);
          //bleKeyboard.press('e');
          break;
        case KEY_1_2:
          // cmd-d (gmeet mic toggle)
          bleKeyboard.print("Button 1.2");
          //bleKeyboard.press(KEY_LEFT_GUI);
          //bleKeyboard.press('d');
          break;
        case KEY_1_3:
          // Show / Hide ScreenBrush
          bleKeyboard.print("Button 1.3");
          //bleKeyboard.press(KEY_LEFT_ALT);
          //bleKeyboard.press(KEY_TAB);
          break;
        case KEY_1_4:
          // ctrl-shft-cmd-4 (mac capture part of screen to clipboard)
          bleKeyboard.print("Button 1.4");
          //bleKeyboard.press(KEY_LEFT_CTRL);
          //bleKeyboard.press(KEY_LEFT_SHIFT);
          //bleKeyboard.press(KEY_LEFT_GUI);
          //bleKeyboard.press('4');
          break;
        case KEY_2_1:
          // Type Password
          bleKeyboard.print("Button 2.1");
          //bleKeyboard.print("Saraiswonderful08");
          break;
        case KEY_2_2:
          // cmd-v (mac paste)
          bleKeyboard.print("Button 2.2");
          //bleKeyboard.press(KEY_LEFT_GUI);
          //bleKeyboard.press('v');
          break;
        case KEY_2_3:
          // Full Screen Chrome Tabs Toggle
          bleKeyboard.print("Button 2.3");
          //bleKeyboard.press(KEY_LEFT_SHIFT);
          //bleKeyboard.press(KEY_LEFT_GUI);
          //bleKeyboard.press('f');
          break;
        case KEY_2_4:
          // shft-cmd-5 (mac capture screen utility)
          bleKeyboard.print("Button 2.4");
          //bleKeyboard.press(KEY_LEFT_SHIFT);
          //bleKeyboard.press(KEY_LEFT_GUI);
          //bleKeyboard.press('5');
          break;
        case KEY_3_1:
          //
          bleKeyboard.print("Button 3.1");
          break;
        case KEY_3_2:
          //
          bleKeyboard.print("Button 3.2");
          break;
        case KEY_3_3:
          //
          bleKeyboard.print("Button 3.3");
          break;
        case KEY_3_4:
          //
          bleKeyboard.print("Button 3.4");
          break;
        default:
          // Should never reach here
          bleKeyboard.press(key);
          break;
      }
    }
    else{
      bleKeyboard.releaseAll();
    }
    pressed = state;
  }

  void update(){
    press(!digitalRead(key));
  }

  private:
  const long debounceTime = 30;
  unsigned long lastPressed;
  boolean pressed = 0;
} ;

button buttons[] = {
  {KEY_1_1},
  {KEY_1_2},
  {KEY_1_3},
  {KEY_1_4},
  {KEY_2_1},
  {KEY_2_2},
  {KEY_2_3},
  {KEY_2_4},
  {KEY_3_1},
  {KEY_3_2},
  {KEY_3_3},
  {KEY_3_4}
};

const uint8_t NumButtons = sizeof(buttons) / sizeof(button);
const uint8_t ledPin = 25;

void setup() {
  Serial.begin(115200);
  Heltec.begin(true /*Display Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
  Serial.println("Heltec initialised");
  bleKeyboard.begin();
  bleKeyboard.setBatteryLevel(80);
  Serial.println("Bluetooth initialised");

  // Set LEDs Off.
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  for(int i = 0; i < NumButtons; i++){
    pinMode(buttons[i].key, INPUT_PULLUP);
  }


  Serial.println("Setup Complete");
  draw("Welcome");
}

void loop() {
  for(int i = 0; i < NumButtons; i++){
    buttons[i].update();
  }
}
