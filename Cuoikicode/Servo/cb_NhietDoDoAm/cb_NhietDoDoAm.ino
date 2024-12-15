#include <Servo.h> 
#include <DHT.h> 
#define DHTPIN 2  
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);  
Servo myServo;  
const int servoPin = 9; 
void setup() {  
  Serial.begin(9600);  
  myServo.attach(servoPin); 
  dht.begin();  
} 

void loop() {  
  float h = dht.readHumidity();  
  float t = dht.readTemperature(); 
  if (isnan(h) || isnan(t)) { 
    Serial.println("Không thể đọc cảm biến DHT!"); 
    return;  // Dừng lại nếu không thể đọc được giá trị từ cảm biến 
  } 
  Serial.print("Nhiet do: "); 
  Serial.println(t); 
  Serial.print("Do am: "); 
  Serial.println(h); 
  if (h > 70) { 
    Serial.println("Do am cao - Xoay servo đến 180 độ"); 
    myServo.write(180);   // Quay servo đến góc 180 độ 
    delay(500);            // Giữ ở vị trí 180 độ trong 500ms 
    myServo.write(0);     // Quay servo về góc 0 độ 
    delay(500);            // Giữ ở vị trí 0 độ trong 500ms 
  } else { 
    Serial.println("Do am thap - Xoay servo đến 90 độ"); 
    myServo.write(90);    // Quay servo đến góc 90 độ 
    delay(500);            // Giữ ở vị trí 90 độ trong 500ms 
    myServo.write(0);     // Quay servo về góc 0 độ 
    delay(500);            // Giữ ở vị trí 0 độ trong 500ms 
  } 
  Serial.println("-----------------------------"); 
  delay(1000);             // Đợi 1 giây trước khi lặp lại 
} 