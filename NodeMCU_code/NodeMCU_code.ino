/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL6-XBeT3Wr"
#define BLYNK_TEMPLATE_NAME "DataTracker"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

//#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
#include <ArduinoJson.h>


SoftwareSerial nodemcu(D6, D5);

//Timer to run Arduino code every 5 seconds
unsigned long previousMillis = 0;
unsigned long currentMillis;
const unsigned long period = 10000;  

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);
  while (!Serial) continue;

  BlynkEdgent.begin();
}

void loop() {
  //Get current time
  currentMillis = millis();

  if ((currentMillis - previousMillis >= period)) {

  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, nodemcu);

  // Test parsing
  while (error) {
    Serial.println("Invalid JSON Object");
    delay(500);
    DeserializationError error = deserializeJson(doc, nodemcu);
  }

  Serial.print("Recieved Humidity:  ");
  float hum = doc["humidity"];
  Serial.println(hum);

  Blynk.virtualWrite(V0, hum);

  Serial.print("Recieved Temperature:  ");
  float temp = doc["temperature"];
  Serial.println(temp);

  Blynk.virtualWrite(V1, temp);

  Serial.print("Recieved RainSensor:  ");
  int rain = doc["isRainy"];
  Serial.println(rain);
  

  if(hum>50) {
    Blynk.logEvent("humidity", "Humidity is too high");
  }
  if(temp>30) {
    Blynk.logEvent("temperature", "Temperature is too high");
  }
  if(rain==0){
    Blynk.logEvent("israiny", "It is raining");
  }


previousMillis = previousMillis + period;
  }
}
