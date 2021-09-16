/*
 * HelTec Automation(TM) WIFI_Kit_32 factory test code, witch includ
 * follow functions:
 *
 * - Basic OLED function test;
 *
 * - Basic serial port test(in baud rate 115200);
 *
 * - LED blink test;
 *
 * - WIFI join and scan test;
 *
 * - Timer test and some other Arduino basic functions.
 *
 * by Aaron.Lee from HelTec AutoMation, ChengDu, China
 * 成都惠利特自动化科技有限公司
 * www.heltec.cn
 *
 * this project also realess in GitHub:
 * https://github.com/HelTecAutomation/Heltec_ESP32
*/

#include "heltec.h"
#include "WiFi.h"
#include "images.h"
#include <HTTPClient.h>

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 21;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void logo(){
	Heltec.display -> clear();
	Heltec.display -> drawXbm(0,5,logo_width,logo_height,(const unsigned char *)logo_bits);
	Heltec.display -> display();
}

void WIFISetUp(void)
{
	// Set WiFi to station mode and disconnect from an AP if it was previously connected
	WiFi.disconnect(true);
	delay(1000);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoConnect(true);
	WiFi.begin("PandaNetExt","Muad'Dib");
	delay(100);

	byte count = 0;
	while(WiFi.status() != WL_CONNECTED && count < 10)
	{
		count ++;
		delay(500);
		Heltec.display -> drawString(0, 0, "Connecting...");
		Heltec.display -> display();
	}

	Heltec.display -> clear();
	if(WiFi.status() == WL_CONNECTED)
	{
		Heltec.display -> drawString(0, 0, "Connecting...OK.");
		Heltec.display -> display();
//		delay(500);
	}
	else
	{
		Heltec.display -> clear();
		Heltec.display -> drawString(0, 0, "Connecting...Failed");
		Heltec.display -> display();
		while(1);
	}
	Heltec.display -> drawString(0, 10, "WIFI Setup done");
	Heltec.display -> display();
	delay(500);
}

void WIFIScan(void)
{
	Heltec.display -> drawString(0, 20, "Scan start...");
	Heltec.display -> display();

	int n = WiFi.scanNetworks();
	Heltec.display -> drawString(0, 30, "Scan done");
	Heltec.display -> display();
	delay(500);
	Heltec.display -> clear();

	if (n == 0)
	{
		Heltec.display -> clear();
		Heltec.display -> drawString(0, 0, "no network found");
		Heltec.display -> display();
		while(1);
	}
	else
	{
		Heltec.display -> drawString(0, 0, (String)n);
		Heltec.display -> drawString(14, 0, "networks found:");
		Heltec.display -> display();
		delay(500);

		for (int i = 0; i < n; ++i) {
		// Print SSID and RSSI for each network found
			Heltec.display -> drawString(0, (i+1)*9,(String)(i + 1));
			Heltec.display -> drawString(6, (i+1)*9, ":");
			Heltec.display -> drawString(12,(i+1)*9, (String)(WiFi.SSID(i)));
			Heltec.display -> drawString(90,(i+1)*9, " (");
			Heltec.display -> drawString(98,(i+1)*9, (String)(WiFi.RSSI(i)));
			Heltec.display -> drawString(114,(i+1)*9, ")");
			//            display.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
			delay(10);
		}
	}

	Heltec.display -> display();
	delay(800);
	Heltec.display -> clear();

}

void writeToGoogleSheet(void)
{
  HTTPClient http;
  
  http.begin("https://maker.ifttt.com/trigger/button_pressed/with/key/ckBrVpLIyIzFDFQXeEuAE_"); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            //USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
            //    String payload = http.getString();
            //    USE_SERIAL.println(payload);
            }
        } else {
        //    USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
}

void setup()
{
	pinMode(LED,OUTPUT);
	digitalWrite(LED,LOW);
  pinMode(buttonPin, INPUT);

	Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

	logo();
	delay(300);
	Heltec.display->clear();

  //Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  //Heltec.display->setFont(ArialMT_Plain_16);

	WIFISetUp();
	
	//writeToGoogleSheet();
}

void loop()
{
	//WIFIScan();
	//delay(2000);

  Heltec.display -> clear();
  //Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  //Heltec.display->setFont(ArialMT_Plain_16);
  
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    //digitalWrite(LED, HIGH);
    Heltec.display -> drawString(20, 30, "Don't press again.");
  } else {
    //digitalWrite(LED, LOW);
    Heltec.display -> drawString(30, 30, "Don't press.");
  }
  
  //Heltec.display -> drawString(0, 0, "Don't press.");
  Heltec.display -> display();
  //delay(500);
}
