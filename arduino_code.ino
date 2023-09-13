
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

int sensorPin = 7;
int buzzerPin = 4;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  dht.begin();
  nodemcu.begin(9600);
  delay(1000);

  Serial.println("Program started");
}

void loop() {

  int sensorData = digitalRead(sensorPin);
  Serial.println(sensorData);

  if(sensorData == 0){
    digitalWrite(buzzerPin,HIGH);
  }else{
    digitalWrite(buzzerPin,LOW);
  }
  delay(1000);


  StaticJsonDocument<1000> doc;

  //Obtain Temp and Hum data
  dht11_func();

  //Assign collected data to JSON Object
  doc["humidity"] = hum;
  doc["temperature"] = temp;
  doc["isRainy"] = sensorData;

  //Send data to NodeMCU
  serializeJson(doc, nodemcu);
  delay(500);
}

void dht11_func() {

  hum = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);

}