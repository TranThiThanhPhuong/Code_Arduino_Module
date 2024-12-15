const int enA = 9; // chân digital có dấu ~  
const int in1 = 8;  
const int in2 = 7;  
int trigPin = 5; 
int echoPin = 3; 
long duration; 
float distance;    

void setup() {     
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(enA, OUTPUT);  
  pinMode(in1, OUTPUT);  
  pinMode(in2, OUTPUT);  
  // lúc đầu tắt motor  
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);  
  Serial.begin(9600);       // Khởi động giao tiếp Serial để debug     
}     

void loop() {   ;;    
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
    Serial.println("--> Quay tới");   
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);  
    analogWrite(enA, 255);  
    delay(500);  
  } else {     
    // Serial.println("--> Quay lui");  
    // digitalWrite(in1, LOW); 
    // digitalWrite(in2, HIGH); 
    // analogWrite(enA, 255); 
    // delay(500); 
    // dung
    Serial.println("--> Dừng quay");  
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW); 
    delay(500); 
  }     
  Serial.println("---------------------------------");     
  delay(500); // Đợi 0.5 giây trước khi lặp lại     
} 