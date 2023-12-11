#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>



void moveCan();
void moveNotCan();
void firstRecycling();
void trashInput();


// --------------------------------------------------------------------------------------------- [������ ����]
const int trigPin = 11;
const int echoPin = 12;
const int maxDistance = 200;

NewPing sonar(trigPin, echoPin, maxDistance);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int trashCheck = 0;
char sendSign = '0';
// ---------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------- [1�� �и�����]
const int photoresistorPin = A0; // ���������� ������ �Ƴ��α� �� ��ȣ
const int threshold = 900; // ��ο� ȯ������ ������ �Ӱ谪, ������ �ʿ��� �� �ֽ��ϴ�.

Servo myservo1;
Servo myservo2;  // ���� ���� ��ü ����
int servoPin1 = 9;
int servoPin2 = 10;  // ���� ���Ͱ� ����� �� ��ȣ
// ---------------------------------------------------------------------------------------------


void setup() {
  // ������ ���� �� ����
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LCD �ʱ�ȭ
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


// -------------------------------------------------- ������ ���� �ν� �Լ� ------------------------------------------------------------------

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

  // LCD�� �Ÿ� ���
  lcd.setCursor(0, 1);
  lcd.print("                ");  // ���� ��� �����
  lcd.setCursor(0, 1);


  if (distance <= 30) // ���� �Ÿ��� 30 �̸��� ��
  {
    lcd.print("Detected"); // ������ ���� ���� ���� ���
    //Serial.print("Distance: ");
    //Serial.print(distance);
    //Serial.println(" cm [check]"); // �ø��� ����� Ȯ��

    trashCheck = 1;
  }

  delay(1000);  // ���� �ֱ� ����
}


// -------------------------------------------------- 1�� �и����� �Լ� ------------------------------------------------------------------
 
void firstRecycling()
{
  int sensorValue = 0;
  if (trashCheck == 1)
  {
    delay(2000);
    sensorValue = analogRead(photoresistorPin); // �������� �� �б�
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

  delay(1000); // 1�� ��� �� �ٽ� ����
}


void moveCan() {
  for (int angle = 90; angle >= 40; angle -= 5) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
  delay(2000);
  for (int angle = 40; angle <= 90; angle += 5) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
}


void moveNotCan() {
  for (int angle = 90; angle <= 120; angle += 5) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
  delay(2000);
  for (int angle = 120; angle >= 90; angle -= 5) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
}