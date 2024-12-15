#include<Stepper.h>
int value = 0;
int pin = A0;
const int stepsPerRevolution = 2048;
Stepper myStepper (stepsPerRevolution, 8, 10, 9, 11);
void setup() {
  myStepper.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  value = analogRead(pin);
  if (value < 700){
    Serial.println(value);
    Serial.println("Quay theo chiều kim đồng hồ..."); 
    myStepper.step(stepsPerRevolution/4); 
    delay(100); 
  }
  else {
    Serial.println(value);
    Serial.println("Quay ngược chiều kim đồng hồ..."); 
    myStepper.step(-stepsPerRevolution/4);
    delay(100); 
  }
  delay(300);
  

  
}
