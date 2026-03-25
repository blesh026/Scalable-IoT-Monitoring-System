#include <ESP8266WiFi.h>
#include <DHT.h>

// ====== DHT Sensor Setup ======
#define DHTPIN D4         // GPIO2 (D4 pin on NodeMCU)
#define DHTTYPE DHT11     // Change to DHT22 if you're using that

DHT dht(DHTPIN, DHTTYPE);

// ====== Setup Function ======
void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println("📡 DHT Sensor Started");
}

// ====== Loop Function ======
void loop() {
  delay(2000);  // Delay between readings

  float temperature = dht.readTemperature();   // Celsius
  float humidity = dht.readHumidity();         // Percent

  // Check if reading is valid
  if (isnan(temperature) && isnan(humidity)) {
    Serial.println("❌ Failed to read from DHT sensor!");
    return;
  }

  // Print results
  Serial.print("🌡️ Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, 💧 Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}


