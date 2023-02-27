
/*
  Arduino LSM9DS1 - Accelerometer Application

  This example reads the acceleration values as relative direction and degrees,
  from the LSM9DS1 sensor and prints them to the Serial Monitor or Serial Plotter.

  The circuit:
  - Arduino Nano 33 BLE

  Created by Riccardo Rizzo

  Modified by Jose García
  27 Nov 2020

  This example code is in the public domain.
*/
#include <Arduino_LSM9DS1.h>


float x, y, z, X, Y, Z, totalAccel;

int mosfet = 5;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // IMU.begin;
  pinMode(mosfet, HIGH);
  Serial.begin(9600);
  // while (!Serial);
  //Serial.println("Started");

  //if (!IMU.begin()) {
  //Serial.println("Failed to initialize IMU!");
  // while (1);
  // }

  //Serial.print("Accelerometer sample rate = ");
  // Serial.print(IMU.accelerationSampleRate());
  // Serial.println("Hz");
}

void loop() {

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Compute total acceleration
    X = 0;
    Y = 0;
    Z = 0;
    for (int i = 0; i < 10; i++) {
      X += x;
      Y += y;
      Z += z;
      delay(1);
    }
    X /= 10;
    Y /= 10;
    Z /= 10;

    totalAccel = sqrt(X * X + Y * Y + Z * Z);
    Serial.println(totalAccel);

    if (totalAccel > 2) {
      delay(2000);
      digitalWrite(mosfet, HIGH);
      delay(5000);
      digitalWrite(mosfet, LOW);
    }
  }

}
