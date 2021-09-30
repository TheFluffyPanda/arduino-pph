#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define STICKMAN_HEIGHT   16
#define STICKMAN_WIDTH    8

static const unsigned char PROGMEM stickman_bmp[] =
{ 0b01111110,
0b10000001,
0b10100101,
0b10000001,
0b10000001,
0b10100001,
0b10011101,
0b01000010,
0b00111100,
0b10011001,
0b01011010,
0b00111100,
0b00011000,
0b00111100,
0b01000010,
0b10000001};

int guy_xpos=0;
int guy_dir=0;
int buttonpin=7;
int val;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initialise"));

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  pinMode(buttonpin,INPUT);
  display.display();
  delay(500); // Pause for 0.5 seconds
  display.clearDisplay();
}

void loop() {  

  val=digitalRead(buttonpin);
    
  if (val==HIGH) {
    Serial.println(F("Button Down"));
    if (guy_xpos < display.width()-9) {
      guy_xpos++;
    }
  }
  else {  
    if (guy_xpos > 0) {
      guy_xpos--;
    }
  }
  
  display.clearDisplay();
  //display.drawLine(guy_xpos, 53, guy_xpos, 63, SSD1306_WHITE);
  display.drawBitmap(guy_xpos,47,stickman_bmp,STICKMAN_WIDTH, STICKMAN_HEIGHT,1);
  display.display(); // Update screen with each newly-drawn line
  //delay(5);
}
