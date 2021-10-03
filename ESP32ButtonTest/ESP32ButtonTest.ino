#include "heltec.h"

#define USE_NIMBLE
#include <BleKeyboard.h> // https://github.com/T-vK/ESP32-BLE-Keyboard

// Pin definitions
#define KEY_1_1 22
#define KEY_1_2 19
#define KEY_1_3 23
#define KEY_1_4 18
#define KEY_2_1 26
#define KEY_2_2 27
#define KEY_2_3 14
#define KEY_2_4 12
#define KEY_3_1 5
#define KEY_3_2 17
#define KEY_3_3 0
#define KEY_3_4 2

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
    if (bleKeyboard.isConnected() && state){
      Serial.println(key);
      switch (key) {
        case KEY_1_1:
          bleKeyboard.print("1");
          draw("1 Pressed");
          break;
        case KEY_1_2:
          bleKeyboard.print("2");
          draw("2 Pressed");
          break;
        case KEY_1_3:
          bleKeyboard.print("3");
          draw("3 Pressed");
          break;
        case KEY_1_4:
          bleKeyboard.print("4");
          draw("4 Pressed");
          break;
        case KEY_2_1:
          bleKeyboard.print("1");
          draw("2x1 Pressed");
          break;
        case KEY_2_2:
          bleKeyboard.print("2");
          draw("2x2 Pressed");
          break;
        case KEY_2_3:
          bleKeyboard.print("3");
          draw("2x3 Pressed");
          break;
        case KEY_2_4:
          bleKeyboard.print("4");
          draw("2x4 Pressed");
          break;
        case KEY_3_1:
          bleKeyboard.print("1");
          draw("3x1 Pressed");
          break;
        case KEY_3_2:
          bleKeyboard.print("2");
          draw("3x2 Pressed");
          break;
        case KEY_3_3:
          bleKeyboard.print("3");
          draw("3x3 Pressed");
          break;
        case KEY_3_4:
          bleKeyboard.print("4");
          draw("3x4 Pressed");
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
