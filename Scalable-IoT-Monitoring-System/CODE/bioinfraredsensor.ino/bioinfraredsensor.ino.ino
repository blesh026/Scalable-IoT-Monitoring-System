#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

// -------- Wi-Fi Credentials --------
const char* ssid = "Redmi A2";           // Your Wi-Fi name
const char* password = "rathore@1234";   // Your Wi-Fi password

// -------- DHT Sensor Setup --------
#define DHTPIN D2          // Use D4 (GPIO2) on NodeMCU or Wemos D1 Mini
#define DHTTYPE DHT11      // Use DHT22 if you're using that sensor
DHT dht(DHTPIN, DHTTYPE);

// -------- Setup --------
void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to WiFi!");
}

// -------- Loop --------
void loop() {
  delay(5000);  // wait between reads

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("❌ Sensor read error!");
    return;
  }

  Serial.print("🌡️ Temp: "); Serial.print(temp);
  Serial.print(" °C, 💧 Humidity: "); Serial.println(hum);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;

    http.begin(client, "http://192.137.246:5000/sensor");  // 👈 Replace with your Pi IP if different
    http.addHeader("Content-Type", "application/json");

    String json = "{\"device\":\"esp1\",\"temperature\":" + String(temp) + ",\"humidity\":" + String(hum) + "}";
    int httpCode = http.POST(json);
    String response = http.getString();

    Serial.print("📡 HTTP Status: ");
    Serial.println(httpCode);
    Serial.println("🧾 Server response: " + response);

    http.end();
  } else {
    Serial.println("❌ WiFi not connected!");
  }
}






