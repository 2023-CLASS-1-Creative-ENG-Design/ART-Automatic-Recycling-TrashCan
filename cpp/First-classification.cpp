#include <Arduino.h>
#include <Servo.h>

const int photoresistorPin = A0; // 조도센서를 연결한 아날로그 핀 번호
const int threshold = 900; // 어두운 환경으로 간주할 임계값, 조절이 필요할 수 있습니다.

void moveCan(); // 1차 분류 알고리즘
void moveNonCan();
void firstRecycling();


Servo myservo1;
Servo myservo2;  // 서보 모터 객체 생성
int servoPin1 = 9;
int servoPin2 = 10;  // 서보 모터가 연결된 핀 번호


void setup() {
  Serial.begin(9600); // 시리얼 통신 시작
  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);  // 서보 모터 핀 초기화
}

void loop() {
  int sensorValue = analogRead(photoresistorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);


  if (sensorValue > threshold) {
    Serial.println("Not Can"); // 어두운 환경 감지 시 메시지 출력
  } else {
    Serial.println("Can"); // 밝은 환경 감지 시 메시지 출력
    moveCan();
  }

  delay(1000); // 1초 대기 후 다시 측정
}


void moveCan() {
  for (int angle = 90; angle >= 0; angle -= 10) {  // 기준 90도에서 0도까지 오른쪽으로 10도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);
    delay(100);
  }
  delay(2000);
  for (int angle = 0; angle <= 90; angle += 10) {  // 회전한 0도에서 90도까지 왼쪽으로 10도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);
    delay(100);
  }
}


void moveNonCan() {
  for (int angle = 90; angle <= 180; angle += 10) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
  delay(2000);
  for (int angle = 180; angle >= 90; angle -= 10) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
}