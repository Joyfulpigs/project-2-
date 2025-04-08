#include <Wire.h>
#include <Adafruit_APDS9960.h>

Adafruit_APDS9960 apds;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial monitor to open

  if (!apds.begin()) {
    Serial.println("Failed to initialize APDS-9960 sensor!");
    while (1); // Stop execution if sensor initialization fails
  }
  Serial.println("APDS-9960 sensor initialized.");

  apds.enableColor(true); // Enable color sensing
  apds.enableProximity(true); // Enable proximity sensor
}

void loop() {
  uint16_t r, g, b, c;

  if (apds.colorDataReady()) {
    apds.getColorData(&r, &g, &b, &c);

    // Print the raw RGB and clear values to the Serial Monitor for debugging
    Serial.print("Red: "); Serial.print(r);
    Serial.print(" Green: "); Serial.print(g);
    Serial.print(" Blue: "); Serial.print(b);
    Serial.print(" Clear: "); Serial.println(c);

    // Send detected color over serial to Unity based on adjusted thresholds
    if (r > 30 && g < 30 && b < 30) {  // Adjusted red detection
      Serial.println("red");  // Send "red" to Unity
    } 
    else if (g > 20 && r < 20 && b < 20) {  // Loosened green detection
      Serial.println("green");  // Send "green" to Unity
    } 
    else if (b > 20 && r < 30 && g < 30) {  // Lowered blue threshold
      Serial.println("blue");  // Send "blue" to Unity
    } 
    else if (r > 20 && g > 20 && b > 20 &&
             abs(r - g) < 25 && abs(r - b) < 25 && abs(g - b) < 25) {  // Loosened white detection
      Serial.println("white");  // Send "white" to Unity
    }
  }

  delay(50); // Delay for half a second before reading again
}
