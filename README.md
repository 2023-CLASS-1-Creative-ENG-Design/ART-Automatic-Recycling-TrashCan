<img src="https://capsule-render.vercel.app/api?type=waving&color=76EA63&height=150&section=header" />

# :recycle: <b>ART : Automatic Recycling Trash-can</b> :recycle:
안녕하세요, 기초창의공학설계 6팀 STX입니다.
<br>

<br>                          

## :one: Team STX

### ✔️ Team Logo
<p align=center>
  <img src="https://github.com/2023-CLASS-1-Creative-ENG-Design/ART-Automatic-Recycling-TrashCan/assets/82202775/b0561e14-9616-475a-a6cf-439aa7bf15ba" width="640" height= "360">
</p>


### ✔️ Team Member
:frog: <b>김민재 [ART 앱 제작 담당] </b> : 안녕하세요, 저는 경북대학교 컴퓨터학부 23학번 김민재입니다. <br>
<br>
:whale: <b>김시영 [H/W 개발 담당] </b> : 안녕하세요, 저는 경북대학교 컴퓨터학부 23학번 김시영입니다. <br>
<br>
:cat: <b>이민주 [Arduino S/W 개발 담당] </b> : 안녕하세요, 저는 경북대학교 컴퓨터학부 23학번 이민주입니다. <br>
<br>
:pig: <b>최원아 [Arduino S/W 개발 담당] </b> : 안녕하세요, 저는 경북대학교 컴퓨터학부 23학번 최원아입니다. <br>
<br>

<br>

## :two: Project Introduce
- :computer: [기초창의공학설계] 아두이노 프로젝트
- :recycle: 캔, 유리, 플라스틱을 자동으로 분리해주는 쓰레기통
- :white_check_mark: 투입 감지와 교체 여부를 보기 쉽게 알려주는 친절한 쓰레기통
<p align=center>
  <img src="https://github.com/2023-CLASS-1-Creative-ENG-Design/ART-Automatic-Recycling-TrashCan/assets/82202775/c4c537d3-fc0f-467b-abff-9b4406485154" width="604.8" height="599.2">
</p>
<br>

<br>

## :three: Motive
- "국립대 분리수거 미이행" 사건 모티브
- 함께 해결책을 모색할 필요성 인식
- 조금이나마 편리한 분리수거 제공을 위한 프로젝트
<br>

<br>

## :four: Langange
- Arduino<br>

![c++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

- Application<br>

![Kotlin](https://img.shields.io/badge/Kotlin-0095D5?&style=for-the-badge&logo=kotlin&logoColor=white)
<br>

<br>

## :five: Introduce Our Code
### 🅰️ Used HeaderFile
```cpp
#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
```
<br>

### 🅱️ Arduino Serial Communication
#### Circuit
<p align=center>
  <img src="https://github.com/2023-CLASS-1-Creative-ENG-Design/ART-Automatic-Recycling-TrashCan/assets/82202775/77fc1866-47ad-45b9-8e0f-395055007d73" width="673.5" height="449">
</p>

#### Transmit Program
```cpp
#include <Arduino.h>

void loop(){
  Serial.print("1"); // 시리얼 통신으로 1 송신
}
```

#### Reception Program
```cpp
#include <Arduino.h>

void loop(){
  Serial.available(); // 시리얼 통신을 통해 데이터가 들어오면 True
  char readSign = (char)Serial.read(); // 시리얼 통신으로 들어온 데이터를 readSign에 저장
}
```
<br>

<br>

## :six: Research Procedure

<!--  개발계획서  -->
<details>
<summary>
  <h3>[2023. 11. 15] 개발계획서 📄</h3>
</summary>
   <a href="6조 개발계획서.hwp"> 🔗 6조 개발계획서 한글 파일 </a>
</details>
<br>

<br>

<!--  1차 연구노트  -->
<details>
<summary>
  <h3>[2023. 11. 22] 1차 연구노트 📄</h3>
</summary>
   <a href="6조 11월 4주차 연구노트.hwp"> 🔗 6조 11월 4주차 연구노트 한글 파일 </a>
</details>
<br>

<br>

<!--  2차 연구노트  -->
<details>
<summary>
  <h3>[2023. 11. 29] 2차 연구노트 📄</h3>
</summary>
   <a href="6조 11월 5주차 연구노트.hwp"> 🔗 6조 11월 5주차 연구노트 한글 파일 </a>
</details>
<br>

<br>

<!--  3차 연구노트  -->
<details>
<summary>
  <h3>[2023. 12. 06] 3차 연구노트 📄</h3>
</summary>
   <a href="6조 12월 1주차 연구노트.hwp"> 🔗 6조 12월 1주차 연구노트 한글 파일 </a>
</details>
<br>

<br>

<!--  프로젝트 결과보고서  -->
<details>
<summary>
  <h3>[2023. 12. 13] 프로젝트 결과보고서 📄</h3>
</summary>
   <a href="6조 프로젝트 결과 보고서.hwp"> 🔗 6조 프로젝트 결과보고서 한글 파일 </a>
</details>
<br>

<br>

<!--  영상 및 사진 자료  -->
<details>
<summary>
  <h3>영상 및 사진 자료 📄</h3>
</summary>
   <a href="video"> 🔗 영상 자료 </a><br>
   <a href="photo"> 🔗 사진 자료 </a>
</details>
<br>

<br>

<img src="https://capsule-render.vercel.app/api?type=waving&color=76EA63&height=150&section=footer" />
