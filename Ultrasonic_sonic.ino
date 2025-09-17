#include <HardwareSerial.h>

// Create UART object (UART2)
HardwareSerial mySerial(2);

// Buffer
uint8_t data_buffer[4];

void setup() {
  Serial.begin(115200);        // Serial Monitor
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17 (TX not needed)
  Serial.println("DYP-A02YYUW UART Ultrasonic Sensor Test");
}

void loop() {
  if (mySerial.available() >= 4) {
    // Read 4 bytes from sensor
    for (int i = 0; i < 4; i++) {
      data_buffer[i] = mySerial.read();
    }

    // Check frame header (0xFF)
    if (data_buffer[0] == 0xFF) {
      int highByte = data_buffer[1];
      int lowByte  = data_buffer[2];
      int sumCheck = data_buffer[3];

      // Verify checksum
      if (((0xFF + highByte + lowByte) & 0xFF) == sumCheck) {
        int distance = (highByte << 8) + lowByte; // distance in mm
        Serial.print("Distance: ");
        Serial.print(distance / 10.0); // Convert mm → cm
        Serial.println(" cm");
      }
    }
  }
}
