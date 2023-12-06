#include <Arduino.h>
#include <Servo.h>

const int photoresistorPin = A0; // ���������� ������ �Ƴ��α� �� ��ȣ
const int threshold = 900; // ��ο� ȯ������ ������ �Ӱ谪, ������ �ʿ��� �� �ֽ��ϴ�.

void moveCan(); // 1�� �з� �˰���
void moveNonCan();
void firstRecycling();


Servo myservo1;
Servo myservo2;  // ���� ���� ��ü ����
int servoPin1 = 9;
int servoPin2 = 10;  // ���� ���Ͱ� ����� �� ��ȣ


void setup() {
  Serial.begin(9600); // �ø��� ��� ����
  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);  // ���� ���� �� �ʱ�ȭ
}

void loop() {
  int sensorValue = 0;
  int can_check = 0;
  
  for (int i = 0; i < 3; i++)
  {
    sensorValue = analogRead(photoresistorPin);
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);
    if (sensorValue <= threshold)
      {
        can_check++;
      }
    delay(100);
  }


  if (can_check == 0) {
    Serial.println("Not Can"); // ��ο� ȯ�� ���� �� �޽��� ���
    moveNonCan();
  } else {
    Serial.println("Can");
    moveCan();
  }

  delay(1000); // 1�� ��� �� �ٽ� ����
}


void moveCan() {
  for (int angle = 90; angle >= 0; angle -= 10) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
  delay(2000);
  for (int angle = 0; angle <= 90; angle += 10) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
}


void moveNonCan() {
  for (int angle = 90; angle <= 180; angle += 10) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
  delay(2000);
  for (int angle = 180; angle >= 90; angle -= 10) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
}