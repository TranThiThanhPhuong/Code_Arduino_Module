const int enA = 9; // chân digital có dấu ~ 
const int in1 = 8; 
const int in2 = 7; 
int light = A0;   
int val = 0;    

void setup() {    
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  // lúc đầu tắt motor 
  digitalWrite(in1, LOW); digitalWrite(in2, LOW); 
  Serial.begin(9600);       // Khởi động giao tiếp Serial để debug    
}    

void loop() {   ;;	 
  val = analogRead(light);    
  Serial.print("Giá trị LIGHT: ");    
  Serial.println(val);    
  if (val < 700) {    
    Serial.println("--> Quay tới");  
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW); 
    analogWrite(enA, 255); 
    delay(2000); 
  } else {    
    Serial.println("--> Quay lui"); 
    digitalWrite(in1, LOW); digitalWrite(in2, HIGH); 
    analogWrite(enA, 255); 
    delay(2000); 
  }    
  Serial.println("---------------------------------");    
  delay(500); // Đợi 0.5 giây trước khi lặp lại    
} 