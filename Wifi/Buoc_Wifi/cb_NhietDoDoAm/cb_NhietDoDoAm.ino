#include <ESP8266WebServer.h>  
#include <WebSocketsServer.h>  
#include "DHT.h"  
#include <Stepper.h>  
const int stepsPerRevolution = 2048;  
Stepper myStepper(stepsPerRevolution, D5, D7, D6, D8); // GPIO4 (D2), GPIO2 (D4), GPIO0 (D3), GPIO14 (D5)  
const int DHTPIN = D1; // GPIO5 (D1)  
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Lavie"; // Thay bằng SSID Wi-Fi  
const char* password = "03102004"; // Thay bằng mật khẩu Wi-Fi  

ESP8266WebServer server(80);  
WebSocketsServer webSocket(81);  
float temperature = 0;  
float humidity = 0;  
int stepAngle = 0;       // Góc quay (°)  
bool motorRunning = false; // Trạng thái động cơ  

void setup() {  
  myStepper.setSpeed(10);  
  dht.begin();  
  Serial.begin(115200);  
  Serial.print("Connecting to Wi-Fi");  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {  
    delay(1000);  
    Serial.print(".");  
  }  
  Serial.println("\nWi-Fi connected!");  
  Serial.print("IP address: ");  
  Serial.println(WiFi.localIP());  
  server.on("/", handleRoot);  
  server.begin();  
  webSocket.begin();  
  webSocket.onEvent(webSocketEvent);  
}  

void loop() {  
  server.handleClient();  
  webSocket.loop();  
  static unsigned long lastUpdate = 0;  
  if (millis() - lastUpdate > 2000) { 
    lastUpdate = millis();  
    temperature = dht.readTemperature();  
    Serial.print("Nhiet do: ");  
    Serial.println(temperature);  
    humidity = dht.readHumidity();  
    Serial.print("Do am: ");  
    Serial.println(humidity); 
    Serial.println("------------------");  
    // Gửi dữ liệu đến WebSocket  
    String data = "{\"temperature\":" + String(temperature) +  
                  ",\"humidity\":" + String(humidity) + "}";  
    webSocket.broadcastTXT(data);  
  }  
  // Quay động cơ liên tục nếu trạng thái đang chạy  
  if (motorRunning) {  
    myStepper.step((stepsPerRevolution / 360) * stepAngle);  
    delay(500); 
  }  
}  

void handleRoot() {  
  // Tạo giao diện HTML  
  String htmlPage = R"rawliteral(  
<!DOCTYPE html>  
<html lang="en">  

<head>  

  <meta charset="UTF-8">  

  <meta name="viewport" content="width=device-width, initial-scale=1.0">  

  <title>SmartHome Control</title>  

  <style>  

    body { font-family: Arial, sans-serif; text-align: center; }  

    .container { max-width: 600px; margin: 50px auto; }  

    .card { border: 1px solid #ddd; padding: 20px; margin: 20px; border-radius: 10px; }  

    input, button { padding: 10px; margin: 10px; font-size: 16px; }  

  </style>  

</head>  

<body>  

  <div class="container">  

    <h1>SmartHome Control</h1>  

    <div class="card">  

      <h2>Temperature: <span id="temperature">--</span> °C</h2>  

      <h2>Humidity: <span id="humidity">--</span> %</h2>  

    </div>  

    <div class="card">  

      <h2>Control Stepper Motor</h2>  

      <input type="number" id="angle" placeholder="Enter angle (°)" />  

      <button onclick="sendAngle()">Rotate</button>  

    </div>  

  </div>  

  <script>  

    const ws = new WebSocket(`ws://${location.hostname}:81/`);  

    ws.onmessage = (event) => {  

      const data = JSON.parse(event.data);  

      document.getElementById('temperature').innerText = data.temperature.toFixed(1);  

      document.getElementById('humidity').innerText = data.humidity.toFixed(1);  

    };  

  

    function sendAngle() {  

      const angle = document.getElementById('angle').value;  

      ws.send(angle);  

    }  

  </script>  

</body>  

</html>  

  )rawliteral";  

  

  server.send(200, "text/html", htmlPage);  

}  

  

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {  

  if (type == WStype_TEXT) {  

    String message = String((char*)payload);  

    stepAngle = message.toInt();  

  

    // Kiểm tra nếu góc = 0 thì dừng động cơ  

    if (stepAngle == 0) {  

      motorRunning = false;  

    } else {  

      motorRunning = true;  

    }  

  

    // Ghi thông báo nhận được  

    Serial.print("Received angle: ");  

    Serial.println(stepAngle);  

  }  

} 