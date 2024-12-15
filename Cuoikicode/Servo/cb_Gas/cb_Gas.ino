#include <Servo.h>
const int gasPin = A0;   // Chân đọc giá trị từ cảm biến khí gas (analog)
Servo myServo;           // Tạo đối tượng servo
int servoPin = 9;        // Chân điều khiển servo
int val = 0;

void setup() {
  myServo.attach(servoPin); // Gắn servo vào chân số 9
  myServo.write(0);         // Khởi tạo góc servo ở 0 độ
  Serial.begin(9600);       // Khởi động giao tiếp Serial để debug
}

void loop() {
  val = analogRead(gasPin);
  Serial.print("Giá trị khí gas: ");
  Serial.println(val);
  if (val < 250) {
    Serial.println("Servo quay đến 90 độ rồi về 0 độ");
    myServo.write(90); // Quay đến 90 độ
    delay(1000);       // Giữ ở vị trí 90 độ trong 1 giây
    myServo.write(0);  // Quay về 0 độ
    delay(1000);       // Giữ ở vị trí 0 độ trong 1 giây
  } else {
    Serial.println("Servo quay đến 180 độ rồi về 0 độ");
    myServo.write(180); // Quay đến 180 độ
    delay(1000);        // Giữ ở vị trí 180 độ trong 1 giây
    myServo.write(0);   // Quay về 0 độ
    delay(1000);        // Giữ ở vị trí 0 độ trong 1 giây
  }
  delay(500); // Đợi 0.5 giây trước khi lặp lại
}