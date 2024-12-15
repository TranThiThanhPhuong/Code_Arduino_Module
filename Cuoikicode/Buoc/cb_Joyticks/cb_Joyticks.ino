#include <Stepper.h> 
int JoyStick_x = 0; // Chân X của Joystick 
int JoyStick_y = 1; // Chân Y của Joystick 
int JoyStick_z = 2; // Chân Z (nút nhấn) của Joystick 
const int stepsPerRevolution = 2048; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); 
void setup() { 
  pinMode(JoyStick_z, INPUT_PULLUP); // Chân Z của Joystick sử dụng Pull-up 
  Serial.begin(9600);               // Khởi tạo giao tiếp Serial 
  myStepper.setSpeed(10);           // Đặt tốc độ cho động cơ bước 
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
    Serial.println("Nhấn nút Z - Quay ngược kim đồng hồ 10 độ..."); 
    myStepper.step(-stepsPerRevolution / 36); // Quay ngược 1/36 vòng 
    delay(100); 
    return; 
  } 
  // Kiểm tra trục Y (phải/trái) 
  if (y > 800) { // Joystick đẩy phải 
    Serial.println("Đẩy phải - Quay thuận chiều kim đồng hồ 90 độ..."); 
    myStepper.step(stepsPerRevolution / 4); // Quay 1/4 vòng 
    delay(100); 
    return; 
  } else if (y < 200) { // Joystick đẩy trái 
    Serial.println("Đẩy trái - Quay ngược chiều kim đồng hồ 90 độ..."); 
    myStepper.step(-stepsPerRevolution / 4); // Quay ngược 1/4 vòng 
    delay(100); 
    return; 
  } 
  // Kiểm tra trục X (lên/xuống) 
  if (x > 800) { // Joystick đẩy lên 
    Serial.println("Đẩy lên - Quay thuận chiều kim đồng hồ 45 độ..."); 
    myStepper.step(stepsPerRevolution / 8); // Quay 1/8 vòng 
    delay(100); 
    return; 
  } else if (x < 200) { // Joystick đẩy xuống 
    Serial.println("Đẩy xuống - Quay ngược chiều kim đồng hồ 45 độ..."); 
    myStepper.step(-stepsPerRevolution / 8); // Quay ngược 1/8 vòng 
    delay(100); 
    return; 
  } 
  // Trạng thái bình thường 
  Serial.println("Trạng thái bình thường - Quay thuận chiều kim đồng hồ 10 độ..."); 
  myStepper.step(stepsPerRevolution / 36); // Quay 1/36 vòng 
  delay(100);  
} 

 