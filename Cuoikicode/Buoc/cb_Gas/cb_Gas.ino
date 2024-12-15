#include <Stepper.h>      // Thư viện Stepper dùng để điều khiển động cơ bước  
const int stepsPerRevolution = 2048; // Số bước cần để động cơ bước quay trọn một vòng   
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); // Khai báo đối tượng động cơ bước với các chân điều khiển   
const int GasPin = A0;    // Chân kết nối cảm biến khí gas (analog pin A0)   
int val = 0;              // Giá trị đọc từ cảm biến khí gas   

void setup() {  
  myStepper.setSpeed(10);   // Đặt tốc độ quay của động cơ bước là 10 RPM   
  Serial.begin(9600);       // Khởi tạo giao tiếp Serial ở tốc độ 9600 baud   
}  
void loop() {  
  val = analogRead(GasPin); // Đọc giá trị từ cảm biến khí gas   
  Serial.print("Gia tri khi gas: ");  
  Serial.println(val);      // Hiển thị giá trị khí gas lên Serial Monitor   
  if (val > 250) { // Nếu giá trị khí gas lớn hơn 250   
    Serial.println("Quay theo chiều kim đồng hồ...");  
    myStepper.step(stepsPerRevolution / 4); // Quay động cơ 1/4 vòng theo chiều kim đồng hồ   
    delay(100);  
  } else { // Nếu giá trị khí gas nhỏ hơn hoặc bằng 250   
    Serial.println("Quay ngược chiều kim đồng hồ...");  
    myStepper.step(-stepsPerRevolution / 4); // Quay động cơ 1/4 vòng ngược chiều kim đồng hồ   
    delay(100);  
  }  
  delay(1000); // Chờ 1 giây trước khi lặp lại   
} 