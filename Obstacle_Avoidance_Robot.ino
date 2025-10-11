#include <Servo.h>

// Motor pins (connected to L298N)
const int motorLeftForward = 5;
const int motorLeftBackward = 6;
const int motorRightForward = 9;
const int motorRightBackward = 10;

// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;

// Servo motor
Servo scanServo;
const int servoPin = 11;

// Distance thresholds
const int safeDistance = 20; // in cm

void setup() {
  // Motor pins
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Servo
  scanServo.attach(servoPin);
  scanServo.write(90); // Center

  Serial.begin(9600);
}

void loop() {
  int centerDist = measureDistanceAt(90);
  delay(200);

  if (centerDist > safeDistance) {
    moveForward();
  } else {
    stopMoving();
    delay(300);

    int leftDist = measureDistanceAt(150);
    delay(200);

    int rightDist = measureDistanceAt(30);
    delay(200);

    if (leftDist > rightDist && leftDist > safeDistance) {
      turnLeft();
      delay(400);
    } else if (rightDist > leftDist && rightDist > safeDistance) {
      turnRight();
      delay(400);
    } else {
      
      moveBackward();
      delay(500);
    }
  }

  stopMoving(); 
  delay(100);
}

long measureDistanceAt(int angle) {
  scanServo.write(angle);
  delay(300); 
  return getDistance();
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

// Movement Functions
void moveForward() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

void moveBackward() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, HIGH);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, HIGH);
}

void turnLeft() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, HIGH);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

void turnRight() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, HIGH);
}

void stopMoving() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}
