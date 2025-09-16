#define SensorPin 34  // Analog input pin connected to pH sensor
float calibration_offset = -1.157;

unsigned long samplingInterval = 1000; // 1 second
unsigned long lastTime = 0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // ESP32 supports 12-bit ADC (0–4095)
}

void loop() {
  if (millis() - lastTime >= samplingInterval) {
    lastTime = millis();

    int analogValue = analogRead(SensorPin);
    float voltage = analogValue * (3.3 / 4095.0); // Convert to voltage (ESP32 3.3V ADC)
    
    // Typical conversion formula (based on DFRobot's sensor)
    float pHValue = 7 + ((2.5 - voltage + calibration_offset) / 0.18); 

    Serial.print("Analog Value: ");
    Serial.print(analogValue);
    Serial.print(" | Voltage: ");
    Serial.print(voltage, 3);
    Serial.print(" V | pH Value: ");
    Serial.println(pHValue, 2);
  }
}