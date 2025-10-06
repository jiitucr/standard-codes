// Motor Driver 
#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10
#define ENA 11
#define ENB 12

int SL = 150;
int SR = 150;
volatile char receivedChar = '\0';

void goForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, SL);
  analogWrite(ENB, SR);
}

void turnLeft() {
  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, SL - 50);  
  analogWrite(ENB, SR + 30); 
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, SL + 30);
  analogWrite(ENB, SR - 50);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void setup() {
  Serial.begin(9600);  // Bluetooth on hardware serial (pin 0,1)

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

void loop() {
  if (receivedChar == 'F') goForward();
  else if (receivedChar == 'L') turnLeft();
  else if (receivedChar == 'R') turnRight();
  else if (receivedChar == 'S') stop();
}

// This is automatically called by Arduino core when new serial data arrives
void serialEvent() {
  while (Serial.available()) {
    receivedChar = Serial.read();
  }
}
