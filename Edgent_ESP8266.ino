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

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

//Use File/Example/Blynk/Blynk.Edgent/Edgent_ESP8266 to include lib
#include "BlynkEdgent.h"

//Install 'DHT sensor library' + 'Adafruit Unified Sensor' in lib manager to use dht sensor
#include <DHT.h>

//Initialisation of DHT11 Sensor
DHT dht(0, DHT11);
float temp;
float hum;

//Initialisation of Rain Sensor
int rainSensorPin = 2;
int rainSensorData;

//Buzzer pin
int buzzerPin = 16;


//Initialisation of Voltage Sensor
float volt;
int voltSensorPin = A0;
int voltSensorData;


void setup() {
  pinMode(rainSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  dht.begin();
  BlynkEdgent.begin();
  delay(1000);
}

void loop() {

  voltSensorData = analogRead(voltSensorPin);
  volt = voltSensorData / 5.0 * 20.0;

  rainSensorData = digitalRead(rainSensorPin);

  hum = dht.readHumidity();
  temp = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Voltage: ");
  Serial.println(volt);
  Serial.print("Rain Sensor: ");
  Serial.println(rainSensorData);

  Blynk.virtualWrite(V0, hum);
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, volt);

  if(hum > 50.0) {

    Blynk.logEvent("humidity", "Humidity is too high");
    digitalWrite(buzzerPin,HIGH);

  }else{
    digitalWrite(buzzerPin,LOW);
  }

  if(temp > 30.0) {

    Blynk.logEvent("temperature", "Temperature is too high");
    digitalWrite(buzzerPin,HIGH);

  }else{
    digitalWrite(buzzerPin,LOW);
  }
  
  if(rainSensorData == 0) {

    Blynk.logEvent("israiny", "It is raining");
    digitalWrite(buzzerPin,HIGH);

  }else{
    digitalWrite(buzzerPin,LOW);
  }
}
