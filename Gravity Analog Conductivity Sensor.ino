// ESP32 + Gravity Analog Conductivity Sensor

const int analogPin = 34;  // ADC1_CH6, make sure to use an ADC1 channel for stable reading
const float V_REF = 3.3;   // ESP32 ADC reference voltage
const int ADC_RESOLUTION = 4095;  // 12-bit ADC resolution for ESP32

// Calibration constants (adjust these based on your calibration process)
const float SENSOR_OFFSET = -0.08;  // Voltage offset (in volts), adjust after calibration
const float CALIBRATION_FACTOR = 6.9;  // Multiplier to convert voltage to conductivity (uS/cm)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Gravity Analog Conductivity Sensor with ESP32");
}

void loop() {
  // Read raw ADC value
  int adcValue = analogRead(analogPin);
  
  // Convert ADC value to voltage
  float voltage = ((float)adcValue / ADC_RESOLUTION) * V_REF;

  // Remove sensor offset voltage
  float voltage_corrected = voltage - SENSOR_OFFSET;
  if (voltage_corrected < 0) voltage_corrected = 0;

  // Convert corrected voltage to conductivity (µS/cm)
  float conductivity = voltage_corrected * CALIBRATION_FACTOR;

  Serial.print("Raw ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | Conductivity: ");
  Serial.print(conductivity, 2);
  Serial.println(" mS/cm");

  delay(1000);  // wait 1 second before next read
}
