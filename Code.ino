#include <WiFi.h>;
#include <DHT.h>

#define DHT_TYPE DHT11
#define DHT_Pin 12
#define MQ5_Pin 14 

const char* ssid = "your ssid";
const char* password = "your password";

DHT dht(DHT_Pin, DHT_TYPE)

float temperature;
float humidity;
float gas_concentration;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to WiFi network");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(DHT_Pin, INPUT);
  dht.begin();

  pinMode(MQ5_Pin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    get_DHT_readngs();
    get_MQ5_concentration();
    delay(5000);
  }
  else {
    Serial.println("Connection Lost");
  }
}

void get_DHT_readings() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}

void get_MQ5_readings() {
  gas_concentration = analogRead(MQ5_Pin);
}
