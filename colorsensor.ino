#include <Wire.h>
#include <Adafruit_APDS9960.h>

Adafruit_APDS9960 apds;

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial monitor to open

  if (!apds.begin()) {
    //Serial.println("Failed to initialize APDS-9960 sensor!");
    while (1); // Stop execution if sensor initialization fails
  }
  //Serial.println("APDS-9960 sensor initialized.");

  apds.enableColor(true); // Enable color sensing
  apds.enableProximity(true); // Enable proximity sensor
}

void loop() {
  uint16_t r, g, b, c;

  //if close enough, then check color and send color!
  if (apds.readProximity() > 10) {

    if (apds.colorDataReady()) {
      apds.getColorData(&r, &g, &b, &c);

      int values[4] = {r,g,b,c};
    
      for (int i = 0; i < 4; i++) {
        Serial.print(values[i]);
        if (i < 3) Serial.print(',');  // Comma-separated
      }
      Serial.println();  // End of line to signal Unity it's one set

    }

  } 
  //Otherwise say "none" and print -1 four times in a row...
  else {

      int values[4] = {-1,-1,-1,-1};
    
      for (int i = 0; i < 4; i++) {
        Serial.print(values[i]);
        if (i < 3) Serial.print(',');  // Comma-separated
      }
      Serial.println();  // End of line to signal Unity it's one set

  }
  
  
  delay(100); // Delay for half a second before reading again
}
