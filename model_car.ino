#include <WiFi.h>
#include <WebServer.h>
int motpin1 =13;
int motpin2 =12;
int motpin3 =14;
int motpin4 =27;
const char* ssid = "aaaa";
const char* password = "11111111";
WebServer server(80);
int command = 0; 
void handleForward() {
  command = 1;  
  server.send(200, "text/plain", "Moving Forward");
}
void handleBackward() {
  command = 2; 
  server.send(200, "text/plain", "Moving Backward");
}
void handleRight() {
  command = 3;
  server.send(200, "text/plain", "Turning Right");
}
void handleLeft() {
  command = 4;
  server.send(200, "text/plain", "Turning Left");
}
void handleStop(){
  command = 5;
  server.send(200, "text/plain", "Stopping");
}
void handleRoot() {
  server.send(200, "text/html",
    "<h1 style=\"text-align: center; font-family: Arial, sans-serif;\">Control Bot</h1>"
    "<div style=\"text-align: center;\">"
    "  <button onclick=\"sendCommand('/forward')\""
    "          style=\"width: 150px; height: 50px; font-size: 18px; margin: 10px; background-color: #4CAF50; color: white; border: none; border-radius: 10px; cursor: pointer;\">"
    "    Forward ^"
    "  </button><br>"
    "  <button onclick=\"sendCommand('/left')\""
    "          style=\"width: 150px; height: 50px; font-size: 18px; margin: 10px; background-color: #FF9800; color: white; border: none; border-radius: 10px; cursor: pointer;\">"
    "    <-- Left"
    "  </button>"
    "  <button onclick=\"sendCommand('/right')\""
    "          style=\"width: 150px; height: 50px; font-size: 18px; margin: 10px; background-color: #008CBA; color: white; border: none; border-radius: 10px; cursor: pointer;\">"
    "    Right -->"
    "  </button><br>"
    "  <button onclick=\"sendCommand('/backward')\""
    "          style=\"width: 150px; height: 50px; font-size: 18px; margin: 10px; background-color: #f44336; color: white; border: none; border-radius: 10px; cursor: pointer;\">"
    "    Backward v"
    "  </button><br>"
    "<button onclick=\"sendCommand('/stop')\""
" style=\"width: 150px; height: 50px; font-size: 18px; margin: 10px; background-color: #000000; color: white; border: none; border-radius: 50%; cursor: pointer;\">"
"Stop !"
"</button>"
    "</div>"
    "<script>"
    "  function sendCommand(command) {"
    "    fetch(command).then(response => response.text()).then(data => {"
    "      console.log(data);"
    "    });"
    "  }"
    "</script>"
  );
}
void setup() {
  Serial.begin(115200);
  pinMode(motpin1,OUTPUT);
  pinMode(motpin2,OUTPUT);
  pinMode(motpin3,OUTPUT);
  pinMode(motpin4,OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/right", handleRight);
  server.on("/left", handleLeft);
  server.on("/stop", handleStop);
  server.begin();
}
void loop() {
  server.handleClient();
if(command==1){
   runForward();
}
else if(command==2){
   runBackward();
}
else if(command==3){
   runRight();
}
else if(command==4){
   runLeft();
}
else if(command==5){
  stop();
}
delay(100);
}
void runForward() {
  digitalWrite(motpin1, HIGH);
  digitalWrite(motpin2, LOW);
  digitalWrite(motpin3, HIGH);
  digitalWrite(motpin4, LOW);
}
void runBackward() {
  digitalWrite(motpin1, LOW);
  digitalWrite(motpin2, HIGH);
  digitalWrite(motpin3, LOW);
  digitalWrite(motpin4, HIGH);
}
void runRight() {
  digitalWrite(motpin1, LOW);
  digitalWrite(motpin2, HIGH);
  digitalWrite(motpin3, HIGH);
  digitalWrite(motpin4, LOW);
}
void runLeft() {
  digitalWrite(motpin1, HIGH);
  digitalWrite(motpin2, LOW);
  digitalWrite(motpin3, LOW);
  digitalWrite(motpin4,HIGH);
}
void stop(){
  digitalWrite(motpin1, LOW);
  digitalWrite(motpin2, LOW);
  digitalWrite(motpin3, LOW);
  digitalWrite(motpin4, LOW);
}
