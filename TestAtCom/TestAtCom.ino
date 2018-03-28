// Serial 사용법과 SoftwareSerial 사용법은 거의 유사하다.
#include <SoftwareSerial.h>

// Arduino Mega ADK인 경우는 10 ~ 13 사이의 pin에 연결해야 동작함
SoftwareSerial blueSerial(10, 11); // Arduino의 RXD, TXD가 연결된 pin 번호, Bluetooth 입장에서는 TXD, RXD의 연결 번호 

void setup()  
{
  Serial.begin(9600);
  blueSerial.begin(38400);    // AT Command는 data rate을 38400으로 설정해야 함
  Serial.println("[AT Command Mode]");
}

// AT Command 끝에는 "\r\n"이 반드시 들어가야 함
void loop()
{
  while (blueSerial.available())
    Serial.write(blueSerial.read());
  while (Serial.available())
    blueSerial.write(Serial.read());
  delay(100);
}
