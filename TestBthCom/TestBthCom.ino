// Serial 사용법과 SoftwareSerial 사용법은 거의 유사하다.
#include <SoftwareSerial.h>

// Arduino Mega ADK인 경우는 10 ~ 13 사이의 pin에 연결해야 동작함
SoftwareSerial blueSerial(10, 11); // Arduino의 RXD, TXD가 연결된 pin 번호, Bluetooth 입장에서는 TXD, RXD의 연결 번호 

void setup()  
{
  Serial.begin(9600);
  blueSerial.begin(115200);    // Bluetooth는 data rate을 115200으로 설정해야 함
  Serial.println("Welcome, Arduino!");
  blueSerial.println("Welcome, Smartphone!");    // Bluetooth를 이용해 smartphone에 문자 쓰기
}

void loop()
{
  if (blueSerial.available())
    Serial.write(blueSerial.read());
  if (Serial.available())
    blueSerial.write(Serial.read());
  delay(100);
}
