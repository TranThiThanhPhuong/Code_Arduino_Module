#include <Stepper.h>
#define LINE 2 
int val = 0;  
const int stepsPerRevolution = 2048; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); 
void setup() { 
  Serial.begin(9600); 
  myStepper.setSpeed(10); 
  pinMode(LINE, INPUT);
} 

void loop() { 
  val = digitalRead(LINE);
  Serial.println(val); 
  if (val == 1) {
    Serial.println("Quay theo chiều kim đồng hồ..."); 
    myStepper.step(stepsPerRevolution / 8); 
    delay(100); 
  } else { 
    Serial.println("Quay ngược chiều kim đồng hồ..."); 
    myStepper.step(-stepsPerRevolution / 8);
    delay(100); 
  } 
} 

 