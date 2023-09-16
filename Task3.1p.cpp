#include <DHT.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h>  // ThingSpeak library

#define DHTPIN 2       // Pin connected to DHT11 data pin
#define DHTTYPE DHT11  // Type of DHT sensor

char ssid[] = "vanshaj vaid";     // WiFi SSID
char pass[] = "jaishreeramj"; // WiFi Password

 long channelID = 2251754;         // Mine ThingSpeak Channel ID
 char *apiKey = "P9L2NFLJ18OB1RPW";   // mine  ThingSpeak API Key

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  Serial.begin(9600);
  dht.begin();
  connectWiFi();
  ThingSpeak.begin(client);
}

void loop() {
  delay(2000);  // gives the delays basically for 2sec.

  float temperature = dht.readTemperature();     // Read temperature in Celsius
  float humidity = dht.readHumidity();           // Read humidity

  if (!isnan(temperature) && !isnan(humidity)) {
    sendDataToThingSpeak(temperature, humidity);
  } else {
    Serial.println("there are some error to transferr the data!");
  }
  
  delay(30000); // give a dealy  for 30 seconds
}

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) { //Print a message indicating WiFi connection is in progress
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, pass);
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}

void sendDataToThingSpeak(float temp, float humidity) {
  ThingSpeak.setField(1, temp);       // Set field 1 with temperature data
  ThingSpeak.setField(2, humidity);   // Set field 2 with humidity data
  
  int httpCode = ThingSpeak.writeFields(channelID, apiKey); // Send data to ThingSpeak and receive the HTTP response code


  if (httpCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.println("problem occured during sending the data  ThingSpeak");
  }
}