#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String command;
int speed = 255; // 0-255 for L293D
int slow = 180;

const char* ssid = "YourSSID";
const char* password = "YourPassword";

// Motor control pins
int motor1EnablePin = 14;  // ENA
int motor1Input1Pin = 15;  // IN1
int motor1Input2Pin = 13;  // IN2

int motor2EnablePin = 12;  // ENB
int motor2Input1Pin = 2;   // IN3
int motor2Input2Pin = 0;   // IN4

ESP8266WebServer server(80);

void setup() {
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor1Input1Pin, OUTPUT);
  pinMode(motor1Input2Pin, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  pinMode(motor2Input1Pin, OUTPUT);
  pinMode(motor2Input2Pin, OUTPUT);

  Serial.begin(115200);

  // Connecting to Wi-Fi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Starting WEB-server
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void goAhead() {
  digitalWrite(motor1Input1Pin, HIGH);
  digitalWrite(motor1Input2Pin, LOW);
  analogWrite(motor1EnablePin, speed);

  digitalWrite(motor2Input1Pin, HIGH);
  digitalWrite(motor2Input2Pin, LOW);
  analogWrite(motor2EnablePin, speed);
}

void goBack() {
  digitalWrite(motor1Input1Pin, LOW);
  digitalWrite(motor1Input2Pin, HIGH);
  analogWrite(motor1EnablePin, speed);

  digitalWrite(motor2Input1Pin, LOW);
  digitalWrite(motor2Input2Pin, HIGH);
  analogWrite(motor2EnablePin, speed);
}

void goRight() {
  digitalWrite(motor1Input1Pin, HIGH);
  digitalWrite(motor1Input2Pin, LOW);
  analogWrite(motor1EnablePin, speed);

  digitalWrite(motor2Input1Pin, HIGH);
  digitalWrite(motor2Input2Pin, LOW);
  analogWrite(motor2EnablePin, slow);
}

void goLeft() {
  digitalWrite(motor1Input1Pin, HIGH);
  digitalWrite(motor1Input2Pin, LOW);
  analogWrite(motor1EnablePin, slow);

  digitalWrite(motor2Input1Pin, HIGH);
  digitalWrite(motor2Input2Pin, LOW);
  analogWrite(motor2EnablePin, speed);
}
// Define similar functions for other motor directions

void stopRobot() {
  digitalWrite(motor1Input1Pin, LOW);
  digitalWrite(motor1Input2Pin, LOW);
  analogWrite(motor1EnablePin, 0);

  digitalWrite(motor2Input1Pin, LOW);
  digitalWrite(motor2Input2Pin, LOW);
  analogWrite(motor2EnablePin, 0);
}

void loop() {
  server.handleClient();

  command = server.arg("State");
  if (command == "F") goAhead();
  if(command == "B") goBack();
  if(command == "L") goLeft();
  if(command == "R") goRight();
  // Add similar conditions for other directions
  else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}