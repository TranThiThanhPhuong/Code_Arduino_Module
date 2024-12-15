int JoyStick_x = 0; // Chân X của Joystick   
int JoyStick_y = 1; // Chân Y của Joystick   
int JoyStick_z = 2; // Chân Z (nút nhấn) của Joystick   
const int enA = 9; // chân digital có dấu ~ 
const int in1 = 8; 
const int in2 = 7; 
void setup() {    
  // lúc đầu tắt motor 
  pinMode(enA, OUTPUT);  
  pinMode(in1, OUTPUT);  
  pinMode(in2, OUTPUT);  
  // lúc đầu tắt motor  
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);  
  Serial.begin(9600);       // Khởi động giao tiếp Serial để debug
  pinMode(JoyStick_z, INPUT_PULLUP); // Chân Z của Joystick sử dụng Pull-up   
}   

void loop() {   
  int x = analogRead(JoyStick_x);  // Đọc giá trị trục X   
  int y = analogRead(JoyStick_y);  // Đọc giá trị trục Y   
  int z = digitalRead(JoyStick_z); // Đọc trạng thái nút nhấn Z   
  Serial.print("X: ");   
  Serial.print(x);   
  Serial.print(" | Y: ");   
  Serial.print(y);   
  Serial.print(" | Z: ");   
  Serial.println(z);   
  // Nếu nhấn nút Z   
  if (z == 0) {  
    Serial.println("Nhấn nút Z - Dừng quay");   
    digitalWrite(in1, LOW);  
    digitalWrite(in2, LOW);  
    delay(2000); 
    return;
  }   
  // Kiểm tra trục Y (phải/trái)   
  if (y > 800) { // Joystick đẩy phải  
    Serial.println("Joystick đẩy phải - Quay tới nhanh dần");   
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW); 
    for (int sp=0; sp<256; sp++) { 
      analogWrite(enA, sp); 
      delay(2); 
      return;
    }   
  } 
  else if (y < 200) { // Joystick đẩy trái   
    Serial.println("Joystick đẩy trái - Quay tới chậm dần");   
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW); 
    for (int sp=255; sp>0; sp--) { 
      analogWrite(enA, sp); 
      delay(2);
      return;
    }        
  }   
  // Kiểm tra trục X (lên/xuống)   
  if (x > 800) { // Joystick đẩy lên   
    Serial.println("Joystick đẩy lên - Quay lui nhanh dần");   
    digitalWrite(in1, LOW); digitalWrite(in2, HIGH); 
    for (int sp=0; sp<256; sp++) { 
      analogWrite(enA, sp); 
      delay(2);  
      return; 
    }  
  } 
  else if (x < 200) { // Joystick đẩy xuống   
    Serial.println("Joystick đẩy xuống - Quay lui chậm dần");   
    digitalWrite(in1, LOW); digitalWrite(in2, HIGH); 
    for (int sp=255; sp>0; sp--) { 
      analogWrite(enA, sp); 
      delay(2);  
      return;
    }
  }   
  // Trạng thái bình thường   
    Serial.println("Trạng thái bình thường - Quay tới max tốc độ");   
    digitalWrite(in1, HIGH);  
    digitalWrite(in2, LOW);  
    analogWrite(enA, 255);  
    delay(500); 
    return;  
} 

 

 

 

 