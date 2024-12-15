#include<Stepper.h>
int trigPin = 5;
int echoPin = 3;
long duration;
float distance;
const int stepsPerRevolution = 2048;
Stepper myStepper (stepsPerRevolution, 8, 10, 9, 11);
void setup() {
  myStepper.setSpeed(10);
  Serial.begin(9600);
  Serial.println("Động cơ bước 28BYJ-48 đang hoạt động...");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.println("distance: ");
  Serial.println(distance);
  Serial.println(" cm ");
  if (distance < 20) {
    Serial.println("Quay theo chiều kim đồng hồ..."); 
    myStepper.step(stepsPerRevolution/4); 
    delay(100); 
  }  
  else {
    Serial.println("Quay ngược chiều kim đồng hồ..."); 
    myStepper.step(-stepsPerRevolution/4);
    delay(100); 
  }
}

