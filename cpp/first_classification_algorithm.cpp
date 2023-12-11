#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>



void moveCan();
void moveNotCan();
void firstRecycling();
void trashInput();


// --------------------------------------------------------------------------------------------- [쓰레기 투입]
const int trigPin = 11;
const int echoPin = 12;
const int maxDistance = 200;

NewPing sonar(trigPin, echoPin, maxDistance);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int trashCheck = 0;
char sendSign = '0';
// ---------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------- [1차 분리수거]
const int photoresistorPin = A0; // 조도센서를 연결한 아날로그 핀 번호
const int threshold = 900; // 어두운 환경으로 간주할 임계값, 조절이 필요할 수 있습니다.

Servo myservo1;
Servo myservo2;  // 서보 모터 객체 생성
int servoPin1 = 9;
int servoPin2 = 10;  // 서보 모터가 연결된 핀 번호
// ---------------------------------------------------------------------------------------------


void setup() {
  // 초음파 센서 핀 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LCD 초기화
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.clear();
  lcd.print("waiting . . .");

  Serial.begin(9600);

  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
}

void loop()
{
  trashInput();
  firstRecycling();
}


// -------------------------------------------------- 쓰레기 투입 인식 함수 ------------------------------------------------------------------

void trashInput()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // LCD에 거리 출력
  lcd.setCursor(0, 1);
  lcd.print("                ");  // 이전 출력 지우기
  lcd.setCursor(0, 1);


  if (distance <= 30) // 측정 거리가 30 미만일 때
  {
    lcd.print("Input Trash"); // 쓰레기 투입 감지 문구 출력
    //Serial.print("Distance: ");
    //Serial.print(distance);
    //Serial.println(" cm [check]"); // 시리얼 모니터 확인

    trashCheck = 1;
  }

  delay(1000);  // 측정 주기 설정
}


// -------------------------------------------------- 1차 분리수거 함수 ------------------------------------------------------------------
 
void firstRecycling()
{
  int sensorValue = 0;
  if (trashCheck == 1)
  {
    delay(2000);
    sensorValue = analogRead(photoresistorPin); // 조도센서 값 읽기
  }
  //Serial.print("Sensor Value: ");
  //Serial.println(sensorValue);

  if (sensorValue > threshold && trashCheck == 1) {
    //Serial.println("Not Can");
    sendSign = '1';
    if (sendSign == '1')
    {
      Serial.print(sendSign);
      sendSign = '0';
    }
    moveNotCan();
    trashCheck = 0;
  } else if (sensorValue < threshold && trashCheck == 1) {
    //Serial.println("Can");
    moveCan();
    trashCheck = 0;
  }

  delay(1000); // 1초 대기 후 다시 측정
}


void moveCan() {
  for (int angle = 90; angle >= 40; angle -= 5) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
  delay(2000);
  for (int angle = 40; angle <= 90; angle += 5) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
}


void moveNotCan() {
  for (int angle = 90; angle <= 120; angle += 5) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
  delay(2000);
  for (int angle = 120; angle >= 90; angle -= 5) {  // 0도에서 180도까지 30도씩 증가하면서 반복
    myservo1.write(angle);
    myservo2.write(180 - angle);  // 서보 모터를 움직이는 함수 호출
    delay(100);
  }
}