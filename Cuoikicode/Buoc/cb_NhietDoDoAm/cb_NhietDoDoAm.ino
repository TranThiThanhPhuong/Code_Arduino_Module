#include<Stepper.h>
#include "DHT.h"
#include "math.h"
int DHTtype = DHT11;
int pin_DHT = 2;
const int stepsPerRevolution = 2048;
DHT dht(pin_DHT, DHTtype);
Stepper myStepper (stepsPerRevolution, 8, 10, 9, 11);
void setup() {
  dht.begin();
  myStepper.setSpeed(10);
  Serial.begin(9600);
  Serial.println("Động cơ bước 28BYJ-48 đang hoạt động...");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("nhiet do:" );
  Serial.println(t);
  Serial.println("do am:" );
  Serial.println(h);
  Serial.println( " ");
  if (h > 70) { 
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

