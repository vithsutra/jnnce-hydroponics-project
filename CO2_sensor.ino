#include <HardwareSerial.h>

#define RXD_PIN 16   // ESP32 RX pin (connect to MH-Z16 TX)
#define TXD_PIN 17   // ESP32 TX pin (connect to MH-Z16 RX)

HardwareSerial mySerial(1);   // Use UART1

// Command to read CO2 concentration (MH-Z16 / MH-Z19 protocol)
uint8_t cmd_get_sensor[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

void setup() {
  Serial.begin(115200);           
  mySerial.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN);  // MH-Z16 UART
  delay(3000); // wait for sensor to warm up
  Serial.println("MH-Z16 CO2 Sensor initialized.");
}

int16_t readCO2() {
  uint8_t response[9];

  // Send command
  mySerial.write(cmd_get_sensor, 9);
  mySerial.flush();

  delay(100); // wait for sensor response

  // Read response
  if (mySerial.available() >= 9) {
    mySerial.readBytes(response, 9);

    if (response[0] == 0xFF && response[1] == 0x86) {
      int16_t ppm = (response[2] << 8) | response[3];
      return ppm;
    }
  }
  return -1; // error
}

void loop() {
  int16_t co2 = readCO2();
  if (co2 > 0) {
    Serial.print("CO2 Concentration: ");
    Serial.print(co2);
    Serial.println(" ppm");
  } else {
    Serial.println("Error reading CO2");
  }
  delay(2000); // read every 2 seconds
}
