#include <Arduino.h>
#include <Servo.h>

void moveGlass();
void movePlastic();


// --------------------------------------------------------------------------------------------- [1�� �и�����]
const int SOUND_SENSOR_PIN = A5;
int sensorValue;
const int threshold1 = 200;
const int threshold2 = 60;

Servo myservo1;
Servo myservo2;  // ���� ���� ��ü ����
int servoPin1 = 9;
int servoPin2 = 10;  // ���� ���Ͱ� ����� �� ��ȣ
// ---------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
}

void loop() { 
  sensorValue = analogRead(SOUND_SENSOR_PIN);

  if (sensorValue > threshold1)
  {
    Serial.println(sensorValue);
    moveGlass();
  }

  else if (threshold2 < sensorValue && sensorValue < threshold1)
  {
    Serial.println(sensorValue);
    movePlastic();
  }

  
  delay(10);
}



void moveGlass() {
  for (int angle = 90; angle >= 50; angle -= 5) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
  delay(2000);
  for (int angle = 50; angle <= 90; angle += 5) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
}


void movePlastic() {
  for (int angle = 90; angle <= 130; angle += 5) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
  delay(2000);
  for (int angle = 130; angle >= 90; angle -= 5) {  // 0������ 180������ 30���� �����ϸ鼭 �ݺ�
    myservo1.write(angle);
    myservo2.write(180 - angle);  // ���� ���͸� �����̴� �Լ� ȣ��
    delay(100);
  }
}