#include <Arduino.h>
#include <Servo.h>

void moveGlass();
void movePlastic();


// --------------------------------------------------------------------------------------------- [1차 분리수거]
const int SOUND_SENSOR_PIN = A5;
int sensorValue;
const int threshold1 = 150;
const int threshold2 = 77;

Servo myservo1;
Servo myservo2;  // 서보 모터 객체 생성
int servoPin1 = 9;
int servoPin2 = 10;
// ---------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
}

void loop() { 
  char readSign = '0';
  int maxValue = 0;

  if (Serial.available())
  {
    readSign = (char)Serial.read();
    Serial.println(readSign);
  }

  if (readSign == '1')
  {
    for (int i = 0; i < 2000; i++)
    {
      sensorValue = analogRead(SOUND_SENSOR_PIN);
      if (maxValue < sensorValue)
        maxValue = sensorValue;
      delay(1);
    }
    Serial.println(maxValue);
  }
  
  if (maxValue > threshold1)
  {
    Serial.println(maxValue);
    moveGlass();
  }

  else if (maxValue > threshold2)
  {
    Serial.println(maxValue);
    movePlastic();
  }

  readSign = '0';
}



void moveGlass() {
  for (int angle = 90; angle >= 50; angle -= 5) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
  delay(2000);
  for (int angle = 50; angle <= 90; angle += 5) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
}


void movePlastic() {
  for (int angle = 90; angle <= 130; angle += 5) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
  delay(2000);
  for (int angle = 130; angle >= 90; angle -= 5) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
}