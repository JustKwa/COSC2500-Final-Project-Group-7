// Arduino_JSON - Version: Latest 
#include <Arduino_JSON.h>

// Constants for making API request
const int    HTTP_PORT   = 80;
const String HTTP_METHOD = "GET";
const char   HOST_NAME[] = "api.weatherapi.com"; // hostname of web server:
const String PATH_NAME   = "/v1/current.json?q=Hanoi&key=";
const String API_KEY = "3e0b9b1f70824efebab171204231509";

// Variables for weather forecast
//char*

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // Do Nothing
  }

  // Connect with host and make a api GET call
  WiFiClient client;
  if (client.connect(HOST_NAME, HTTP_PORT)) {
    Serial.println("Connected to server");
    client.println(HTTP_METHOD + " " + PATH_NAME + API_KEY + "HTTP/1.1"));
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
  }
  
  // While Client is connected with host, parse the json reponse
  while (client.connected()){
    if (client.available()) {
      char response = client.read();
      Serial.print(c);
    }
  }
}

void loop() {
}

void parseJsonResponse(String response)
{
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, response);
  
  //Checks for parsing error
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  
  //Get the needed fields
  const char* locationName = doc["location"]["name"];
  const char* locationCountry = doc["location"]["country"];
  float temperatureC = doc["current"]["temp_c"];
  const char* weatherCondition = doc["current"]["condition"]["text"];
  float feelsLikeC = doc["current"]["feelslike_c"];
  
  //Print the extracted data
  // Print the extracted data
  Serial.print("Location: ");
  Serial.println(locationName);
  Serial.print("Country: ");
  Serial.println(locationCountry);
  Serial.print("Temp (C): ");
  Serial.println(temperatureC);
  Serial.print("Weather Condition: ");
  Serial.println(weatherCondition);
  Serial.print("Feels Like (Celcius): ");
  Serial.println(feelsLikeC);
}