#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "MPU6050.h"

MPU6050 mpu;

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";

void setup() {
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);  // More stable
  radio.openWritingPipe(address);
  radio.stopListening();  // Transmit mode
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  char command = 'S';  // Default Stop

  // Adjust these thresholds based on test
  if (ay > 10000) command = 'F';  // Forward
  else if (ay < -10000) command = 'B';  // Backward
  else if (ax > 8000) command = 'L';  // Left
  else if (ax < -8000) command = 'R';  // Right

  radio.write(&command, sizeof(command));
  delay(100);  // Tune for responsiveness
}
