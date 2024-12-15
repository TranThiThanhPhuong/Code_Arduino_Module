#include <Servo.h> 
const int trigPin = 5; // Chân Trig của cảm biến siêu âm 
const int echoPin = 3; // Chân Echo của cảm biến siêu âm 
Servo myServo;         // Tạo đối tượng servo 
int servoPin = 9;      // Chân điều khiển servo 
void setup() { 
  myServo.attach(servoPin); // Gắn servo vào chân số 9 
  myServo.write(0);         // Khởi tạo góc servo ở 0 độ 
  pinMode(trigPin, OUTPUT); // Đặt chân Trig là đầu ra 
  pinMode(echoPin, INPUT);  // Đặt chân Echo là đầu vào 
  Serial.begin(9600);       // Khởi động giao tiếp Serial để debug 
} 

void loop() { 
  long duration; 
  float distance; 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034 / 2; 
  Serial.print("Khoảng cách: "); 
  Serial.print(distance); 
  Serial.println(" cm"); 
  if (distance > 20) { // Nếu khoảng cách nhỏ hơn 20 cm 
    Serial.println("Servo quay đến 90 độ rồi về 0 độ"); 
    myServo.write(90); // Quay đến 90 độ 
    delay(1000);       // Giữ ở vị trí 90 độ trong 1 giây 
    myServo.write(0);  // Quay về 0 độ 
    delay(1000);       // Giữ ở vị trí 0 độ trong 1 giây 
  } else { // Nếu khoảng cách lớn hơn hoặc bằng 20 cm 
    Serial.println("Servo quay đến 180 độ rồi về 0 độ"); 
    myServo.write(180); // Quay đến 180 độ 
    delay(1000);        // Giữ ở vị trí 180 độ trong 1 giây 
    myServo.write(0);   // Quay về 0 độ 
    delay(1000);        // Giữ ở vị trí 0 độ trong 1 giây 
  } 
  delay(500); // Đợi 0.5 giây trước khi lặp lại 
} 