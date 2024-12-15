#include <DHT.h> 
#define DHTPIN 2          // Chân kết nối cảm biến DHT 
#define DHTTYPE DHT11     // Định nghĩa loại cảm biến DHT (DHT11 hoặc DHT22) 
DHT dht(DHTPIN, DHTTYPE); // Khởi tạo đối tượng DHT 
const int enA = 9; // Chân PWM của động cơ 
const int in1 = 8;  
const int in2 = 7;  

void setup() { 
  // Khởi tạo các chân động cơ 
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  // Tắt động cơ ban đầu 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  // Bắt đầu giao tiếp Serial 
  Serial.begin(9600); 
  // Bắt đầu cảm biến DHT 
  dht.begin(); 
} 

void loop() { 
  // Đọc giá trị từ cảm biến DHT 
  float h = dht.readHumidity();   
  float t = dht.readTemperature(); 
  // Kiểm tra nếu việc đọc cảm biến không thành công 
  if (isnan(h) || isnan(t)) { 
    Serial.println("Không thể đọc cảm biến DHT!"); 
    return;  // Dừng lại nếu không thể đọc được giá trị từ cảm biến 
  } 
  // In ra giá trị nhiệt độ và độ ẩm 
  Serial.print("Nhiệt độ: "); 
  Serial.print(t); 
  Serial.println("°C"); 
  Serial.print("Độ ẩm: "); 
  Serial.print(h); 
  Serial.println("%"); 
  // Điều kiện điều khiển động cơ 
  if (h > 85) { // Nếu độ ẩm lớn hơn 70% 
    Serial.println("Độ ẩm cao, động cơ quay tới."); 
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW); 
    analogWrite(enA, 255); 
    delay(500);  // Tốc độ tối đa 
  } else {  
    Serial.println("Độ ẩm cao, động cơ quay lui."); 
     // line toi thi chay 
    // digitalWrite(in1, LOW); 
    // digitalWrite(in2, HIGH); 
    // analogWrite(enA, 255); 
    // delay(500);  // Tốc độ tối đa 
    //line sang thi dung
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW); 
    delay(500); 
  }  

   Serial.println("---------------------------------");     

 

  

 

  delay(500); // Đợi 0.5 giây trước khi lặp lại   

} 