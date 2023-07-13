#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
}

void loop() {
  // check if a proximity reading is available
  if (APDS.proximityAvailable()) {
    int proximity = APDS.readProximity();
    if(proximity <= 50)
    {
      Serial.println("Danger Close");
    } else if(proximity > 50 && proximity <= 150)
    {
      Serial.println("Target is approaching");
    }
    else
    {
      Serial.println("Target is far away");
    }


    // print value to the Serial Monitor
    //Serial.println(proximity);
  }

  // wait a bit before reading again
  delay(100);
}
