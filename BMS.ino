#include <DHT.h>
#include <BlynkSimpleEsp8266.h>

#define DHTPIN 2   // DHT11 data pin connected to NodeMCU D2
#define DHTTYPE DHT11

const int pirPin = 4;     // PIR sensor pin connected to NodeMCU D4
const int soundPin = A0;  // Sound sensor analog pin connected to NodeMCU A0

char auth[] = "VjY07Qeatd8ttFlgvAxbAaUcJbwmFV_R";  // Replace with your Blynk Auth Token
char ssid[] = "IOTproject";         // Replace with your WiFi SSID
char pass[] = "getclear24";     // Replace with your WiFi password

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(pirPin, INPUT);
}

void loop() {
  Blynk.run();
  int pirValue = digitalRead(pirPin);
  int soundValue = analogRead(soundPin);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, temperature);  // Virtual Pin V5 for temperature
  Blynk.virtualWrite(V6, humidity);     // Virtual Pin V6 for humidity
  Blynk.virtualWrite(V7, pirValue);     // Virtual Pin V7 for PIR sensor
  Blynk.virtualWrite(V8, soundValue);   // Virtual Pin V8 for Sound sensor

  delay(1000);  // Adjust the delay based on your preferences
}
