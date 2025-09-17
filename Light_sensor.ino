#include "Wire.h"

#define BH1750_ADDRESS 0x23   // I2C address of BH1750

uint16_t data;
float Lux;

void setup() {
  Serial.begin(9600);
  // For ESP32, default SDA=21, SCL=22. If your wiring is different, use Wire.begin(SDA, SCL);
  Wire.begin();
  delay(200);

  // Power on BH1750
  Wire.beginTransmission(BH1750_ADDRESS);
  Wire.write(0x01); // Power ON
  Wire.endTransmission();

  // Set mode: Continuously H-Resolution Mode (1 lx resolution, 120ms)
  Wire.beginTransmission(BH1750_ADDRESS);
  Wire.write(0x10); // Continuous mode command
  Wire.endTransmission();
}

void loop() {
  delay(200);
  // Request 2 bytes from sensor
  Wire.requestFrom(BH1750_ADDRESS, 2);
  if (Wire.available() == 2) {
    data = (Wire.read() << 8) | Wire.read();
    Lux = data / 1.2; // Convert to lux
    Serial.print("LUX: ");
    Serial.print(Lux);
    Serial.println(" lx");
  } else {
    Serial.println("Data not available!");
  }

  delay(500); // print every half second
}
