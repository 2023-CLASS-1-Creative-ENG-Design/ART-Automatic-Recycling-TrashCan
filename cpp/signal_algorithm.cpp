#include <Arduino.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

const int red = 5;
const int green = 4;
const int blue = 3;

const int trigPin1 = 6;
const int echoPin1 = 7;
const int maxDistance1 = 200;

const int trigPin2 = 9;
const int echoPin2 = 10;
const int maxDistance2 = 200;

const int trigPin3 = 11;
const int echoPin3 = 12;
const int maxDistance3 = 200;

NewPing sonar1(trigPin1, echoPin1, maxDistance1);
NewPing sonar2(trigPin2, echoPin2, maxDistance2);
NewPing sonar3(trigPin3, echoPin3, maxDistance3);

void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  delay(50); // 안정화를 위한 대기 시간

  unsigned int distance1 = sonar1.ping_cm();
  unsigned int distance2 = sonar2.ping_cm();
  unsigned int distance3 = sonar3.ping_cm();

  if (distance1 == NO_ECHO) {
    Serial.println("distance 1 : no echo");
  } else {
    Serial.print("distance 1 : ");
    Serial.print(distance1);
    Serial.println("cm");
  }

  if (distance2 == NO_ECHO) {
    Serial.println("distance 2 : no echo");
  } else {
    Serial.print("distance 2 : ");
    Serial.print(distance2);
    Serial.println("cm");
  }

  if (distance3 == NO_ECHO) {
    Serial.println("distance 3 : no echo");
  } else {
    Serial.print("distance 3 : ");
    Serial.print(distance3);
    Serial.println("cm");
  }

  Serial.println();

  if((distance1 <= 30) && (distance1 != NO_ECHO)){
    digitalWrite(red, HIGH);
  }
  else{
    digitalWrite(red, LOW);
  }
  if((distance2 <= 30) && (distance2 != NO_ECHO)){
    digitalWrite(green, HIGH);
  }
  else{
    digitalWrite(green, LOW);
  }
  if((distance3 <= 30) && (distance3 != NO_ECHO)){
    digitalWrite(blue, HIGH);
  }
  else{
    digitalWrite(blue, LOW);
  }

  delay(1000);
}