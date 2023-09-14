
//DHT11 Lib
#include <DHT.h>

//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (0=Rx & 1=Tx)
SoftwareSerial nodemcu(0, 1);

//Initialisation of DHT11 Sensor
#define DHTPIN 5
DHT dht(DHTPIN, DHT11);
float temp;
float hum;

//Initialisation of Rain Sensor
int rainSensorPin = 7;
int rainSensorData;

//Buzzer pin
int buzzerPin = 4;


//Initialisation of Voltage Sensor
float volt;
int voltSensorPin = A0;
int voltSensorData;

void setup() {
  pinMode(rainSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  dht.begin();
  nodemcu.begin(9600);
  delay(1000);

}

void loop() {

  StaticJsonDocument<1000> doc;

  voltSensorData = analogRead(voltSensorPin);
  volt = voltSensorData / 5.0 * 20.0;
  Serial.print("Voltage: ");
  Serial.println(volt);
  
  rainSensorData = digitalRead(rainSensorPin);

  //Obtain Temp and Hum data
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);

  //Assign collected data to JSON Object
  doc["humidity"] = hum;
  doc["temperature"] = temp;
  doc["voltage"] = volt;
  doc["isRainy"] = rainSensorData;

  //alert with buzzer and led
  if(rainSensor == 0 || hum > 70 || temp > 40){
    digitalWrite(buzzerPin,HIGH);
  }else{
    digitalWrite(buzzerPin,LOW);
  }
  delay(1000);

  //Send data to NodeMCU
  serializeJson(doc, nodemcu);
  delay(500);
}



