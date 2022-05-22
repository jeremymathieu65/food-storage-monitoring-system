#include <WiFi.h>;
#include <DHT.h>;
#include "ESPAsyncWebServer.h";
#include "AsyncTCP.h"
#include "SPIFFS.h"

#define DHT_TYPE DHT11
#define DHT_Pin 4
#define MQ5_Pin 14
#define LDR_Pin A0 

const char* ssid = "Redmi 9C";
const char* password = "a629fg65";

AsyncWebServer server(80);

DHT dht(DHT_Pin, DHT_TYPE);

float temperature;
float humidity;
float gas_concentration;
float light_intensity;

String get_temperature() {
  temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  return String(temperature);
}

String get_humidity() {
  humidity = dht.readHumidity();
  Serial.print("Humidity");
  Serial.println(humidity);
  return String(humidity);
}

String get_gas_readings() {
  gas_concentration = analogRead(MQ5_Pin);
  Serial.print("Gas Level: ");
  Serial.println(gas_concentration);
  return String(gas_concentration);
}

String get_light_intensity() {
  light_intensity = analogRead(LDR_Pin);
  Serial.print("Light Intensity: ");
  Serial.println(light_intensity);
  return String(light_intensity);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  Serial.println("\nConnected to WiFi network");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(DHT_Pin, INPUT);
  dht.begin();
  pinMode(MQ5_Pin, INPUT);
  pinMode(LDR_Pin, INPUT);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", get_temperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", get_humidity().c_str());
  });
  server.on("/gas-concentration", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", get_gas_readings().c_str());
  });
  server.on("/light-intensity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", get_light_intensity().c_str());
  });

  server.begin();
}

void loop() {}
