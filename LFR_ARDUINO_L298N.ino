//3 IR SENSOR
#define LS 2
#define RS 4
#define CS 3

//Motor Driver 
#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10

#define ENA 11
#define ENB 12

int SL = 150;
int SR = 150;


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
  
  pinMode(LS,INPUT);
  pinMode(RS,INPUT);
  pinMode(CS,INPUT);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

}

void loop() {

  int left = digitalRead(LS);
  int right = digitalRead(RS);
  int center = digitalRead(CS);  

  if(center == LOW && left == HIGH && right == HIGH){
    goForward();
  }else if(left == LOW){
    turnLeft();
  }else if(right == LOW){
    turnRight();
  }else{
    stop();
  }
}
