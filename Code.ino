/*
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <NewPing.h> // Include the NewPing library

String command;
int speedCar = 255; // 0-255 for L293D
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

// HC-SR04 Ultrasonic Sensor pins
#define TRIGGER_PIN 16 //D0 to trigger
#define ECHO_PIN 5 //D1 to echo
//VCC to 5V
//gnd to ground
#define MAX_DISTANCE 200 // Maximum distance to measure

ESP8266WebServer server(80);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

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
  analogWrite(motor1EnablePin, speedCar);

  digitalWrite(motor2Input1Pin, HIGH);
  digitalWrite(motor2Input2Pin, LOW);
  analogWrite(motor2EnablePin, speedCar);
}

void goBack() {
  digitalWrite(motor1Input1Pin, LOW);
  digitalWrite(motor1Input2Pin, HIGH);
  analogWrite(motor1EnablePin, speedCar);

  digitalWrite(motor2Input1Pin, LOW);
  digitalWrite(motor2Input2Pin, HIGH);
  analogWrite(motor2EnablePin, speedCar);
}

void goRight() {
  digitalWrite(motor1Input1Pin, HIGH);
  digitalWrite(motor1Input2Pin, LOW);
  analogWrite(motor1EnablePin, speedCar);

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
  analogWrite(motor2EnablePin, speedCar);
}

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
  if (command == "B") goBack();
  if (command == "L") goLeft();
  if (command == "R") goRight();
  else if (command == "S") stopRobot();

  // Measure distance using the HC-SR04 sensor
  unsigned int distance = sonar.ping_cm();

  // Make navigation decisions based on the detected distance
  if (distance > 0 && distance <= 100) {
    // Stop or take evasive action if an obstacle is very close (adjust distance as needed)
    stopRobot();
  }
  void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
  }
}
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <NewPing.h>
#include <Servo.h> // Include the Servo library

String command;
int speedCar = 255; // 0-255 for L293D
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

// HC-SR04 Ultrasonic Sensor pins
#define TRIGGER_PIN 16 // D0 GPIO pin for TRIGGER 
#define ECHO_PIN 5    // D1 GPIO pin for ECHO
//VCC to 5V
//gnd to ground
#define MAX_DISTANCE 200 // Maximum distance to measure

// Servo motor control pin
int servoPin = 4; // D2 GPIO pin for the servo

ESP8266WebServer server(80);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servo; // Create a servo object

int leftAngleSum = 0;
int rightAngleSum = 0;
int leftCount = 0;
int rightCount = 0;

void setup() {
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor1Input1Pin, OUTPUT);
  pinMode(motor1Input2Pin, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  pinMode(motor2Input1Pin, OUTPUT);
  pinMode(motor2Input2Pin, OUTPUT);

  pinMode(servoPin, OUTPUT); // Initialize the servo pin
  
  servo.attach(servoPin); // Attach the servo to the pin

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
  analogWrite(motor1EnablePin, speedCar);

  digitalWrite(motor2Input1Pin, HIGH);
  digitalWrite(motor2Input2Pin, LOW);
  analogWrite(motor2EnablePin, speedCar);
}

void goBack() {
  digitalWrite(motor1Input1Pin, LOW);
  digitalWrite(motor1Input2Pin, HIGH);
  analogWrite(motor1EnablePin, speedCar);

  digitalWrite(motor2Input1Pin, LOW);
  digitalWrite(motor2Input2Pin, HIGH);
  analogWrite(motor2EnablePin, speedCar);
}

void goRight() {
  digitalWrite(motor1Input1Pin, HIGH);
  digitalWrite(motor1Input2Pin, LOW);
  analogWrite(motor1EnablePin, speedCar);

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
  analogWrite(motor2EnablePin, speedCar);
}

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
  if (command == "B") goBack();
  if (command == "L") goLeft();
  if (command == "R") goRight();
  else if (command == "S") stopRobot();

  // Measure distance using the HC-SR04 sensor
  unsigned int distance = sonar.ping_cm();

  // Make navigation decisions based on the detected distance
  if (distance > 0 && distance <= 100) {
    // Stop or take evasive action if an obstacle is very close (adjust distance as needed)
    stopRobot();
    
    // Rotate the servo motor to scan for an obstacle-free path
    for (int angle = 0; angle <= 180; angle += 5) 
    {
      servo.write(angle);
      delay(100);
      distance = sonar.ping_cm();
      if (distance > 100) 
      {
        if (angle < 90) 
        {
          leftAngleSum += angle;
          leftCount++;
        } 
        else if(angle>90)
        {
          rightAngleSum += angle;
          rightCount++;
        }
        break;
      }
    }
    servo.write(90); // Reset the servo to its default position (facing forward)
  }
  if (leftCount > 0 && rightCount > 0) 
  {
    int leftAverage = leftAngleSum / leftCount;
    int rightAverage = rightAngleSum / rightCount;
    int averageAngle = (leftAverage>rightAverage)?leftAverage:rightAverage;
    
    // int averageAngle = (leftAverage + rightAverage) / 2;

    if(averageAngle<90)
    {
      goLeft();
    }
    else if(averageAngle>90)
    {
      goRight();
    }
    
    // Now, you can use the averageAngle to determine the direction to move the rover.
    // For example, if averageAngle is less than 90, you can move left, and if it's greater than 90, move right.
  }
}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}
