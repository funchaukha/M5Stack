/****************************************************************************
 
 *  This Sample code Supported M5Stack M5GO
 *  
 * https://www.facebook.com/fun.chaukha/ 
 * http://www.chaukha.com/
 * 
 * This example code is in the public domain.
 * 
 */
#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT

#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>

#include <Adafruit_NeoPixel.h>
#include <M5Stack.h>

// LED Bar There are 10 RGB Leds built in M5GO Base LED Pin  GPIO15
#define PIN            15
#define NUMPIXELS      10
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// get Auth Token in the Blynk App.
char auth[] = "YourAuthToken";

int ledR = 0;
int ledG = 0;
int ledB = 0;


//get ZERRGBA data virtual Pin V0 
BLYNK_WRITE(V0) {
  ledR = param[0].asInt();
  ledG = param[1].asInt();
  ledB = param[2].asInt();
  Serial.print(  "ledR: ");
  Serial.print(ledR);
  Serial.print(  " ledG: ");
  Serial.print(ledG);
  Serial.print(  " ledB: ");
  Serial.println(ledB);
}

void setup()
{
  
  M5.begin();
  M5.Power.begin();
  
  // Debug console
  Serial.begin(115200);
  Serial.println("Waiting for connections...");

  Blynk.setDeviceName("M5Stack Blynk");
  Blynk.begin(auth);
    
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();  // Turn OFF all pixels ASAP
  pixels.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  pixels.clear(); // Set all pixel colors to 'off'
  
  M5.Lcd.setTextFont(4);
  M5.Lcd.setCursor(70, 100, 4);
  M5.Lcd.println(("M5Stack X Blynk"));
  
}

void loop()
{
  Blynk.run();

  //simple setting neopixels
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255    
    pixels.setPixelColor(i, pixels.Color(ledR, ledG, ledB));    
  }
  pixels.show();   // Send the updated pixel colors to the hardware.  
  delay(100);
}
