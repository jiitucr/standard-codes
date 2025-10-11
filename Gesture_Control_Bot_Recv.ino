#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";

const int leftMotorFwd = 5;
const int leftMotorBwd = 6;
const int rightMotorFwd = 7;
const int rightMotorBwd = 8;

void setup() {
  Serial.begin(9600);

  pinMode(leftMotorFwd, OUTPUT);
  pinMode(leftMotorBwd, OUTPUT);
  pinMode(rightMotorFwd, OUTPUT);
  pinMode(rightMotorBwd, OUTPUT);

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char command;
    radio.read(&command, sizeof(command));
    Serial.print("Received: "); Serial.println(command);
    
    switch (command) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      default: stop(); break;
    }
  }
}

void moveForward() {
  digitalWrite(leftMotorFwd, HIGH);
  digitalWrite(leftMotorBwd, LOW);
  digitalWrite(rightMotorFwd, HIGH);
  digitalWrite(rightMotorBwd, LOW);
}

void moveBackward() {
  digitalWrite(leftMotorFwd, LOW);
  digitalWrite(leftMotorBwd, HIGH);
  digitalWrite(rightMotorFwd, LOW);
  digitalWrite(rightMotorBwd, HIGH);
}

void turnLeft() {
  digitalWrite(leftMotorFwd, LOW);
  digitalWrite(leftMotorBwd, HIGH);
  digitalWrite(rightMotorFwd, HIGH);
  digitalWrite(rightMotorBwd, LOW);
}

void turnRight() {
  digitalWrite(leftMotorFwd, HIGH);
  digitalWrite(leftMotorBwd, LOW);
  digitalWrite(rightMotorFwd, LOW);
  digitalWrite(rightMotorBwd, HIGH);
}

void stop() {
  digitalWrite(leftMotorFwd, LOW);
  digitalWrite(leftMotorBwd, LOW);
  digitalWrite(rightMotorFwd, LOW);
  digitalWrite(rightMotorBwd, LOW);
}
