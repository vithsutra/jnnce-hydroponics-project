#include <Wire.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("AHT2415C Sensor Test");

  if (!aht.begin(&Wire)) {
    Serial.println("Could not find AHT sensor, check wiring!");
    while (1) delay(10);
  }
  Serial.println("AHT2415C found!");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); // get humidity & temperature

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  delay(2000);
}
