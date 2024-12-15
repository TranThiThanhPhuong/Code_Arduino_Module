int GasPin = 0; 
int val; 
const int enA = 9; // chân digital có dấu ~ 
const int in1 = 8; 
const int in2 = 7; 

void setup() { 
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  // lúc đầu tắt motor 
  digitalWrite(in1, LOW); digitalWrite(in2, LOW); 
  Serial.begin(9600); 
} 

void loop() { 
  // put your main code here, to run repeatedly: 
  val =  analogRead(GasPin); 
  Serial.println(val, DEC); 
  if (val > 200) { 
    Serial.println("Có gas --> Quay tới"); 
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW); 
    analogWrite(enA, 255); 
    delay(500); 
  } 
  else { 
    Serial.println("Không có gas --> Quay lui"); 
    // digitalWrite(in1, LOW); 
    // digitalWrite(in2, HIGH); 
    // analogWrite(enA, 255); 
    // delay(500); 
    // line sang thi dung
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW); 
    delay(500); 
  } 
  Serial.println("------------------------------"); 
  delay(100); 
} 