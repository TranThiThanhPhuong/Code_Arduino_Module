#define LINE_SENSOR_PIN 2   // Chân đọc giá trị từ cảm biến dò line (digital pin 2) 
int val = 0;              // Biến để lưu giá trị đọc từ cảm biến dò line 
const int enA = 9; // chân digital có dấu ~ 
const int in1 = 8; 
const int in2 = 7; 

void setup() {  
  pinMode(LINE_SENSOR_PIN, INPUT); // Cấu hình chân cảm biến dò line là input 
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  // lúc đầu tắt motor 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  Serial.begin(9600);              // Khởi động giao tiếp Serial để theo dõi giá trị cảm biến 
}  

void loop() {  
  val = digitalRead(LINE_SENSOR_PIN); // Đọc giá trị từ cảm biến dò line (HIGH hoặc LOW) 
  Serial.print("Giá trị val: ");  
  Serial.println(val); // In ra giá trị đọc được từ cảm biến dò line 
  if (val == 1) { // Nếu cảm biến phát hiện line (HIGH) 
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW); 
    analogWrite(enA, 255); 
    delay(500); 
  } 
  else { // Nếu cảm biến không phát hiện line (LOW) 
    // line toi thi chay 
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH); 
    analogWrite(enA, 255); 
    delay(500); 
    // line sang thi dung
    // digitalWrite(in1, LOW); 
    // digitalWrite(in2, LOW); 
    // delay(500); 
  }  
  Serial.println("----------------------------"); // Để phân cách các lần đọc giá trị 
  delay(500); // Đợi 0.5 giây trước khi lặp lại vòng lặp 
} 