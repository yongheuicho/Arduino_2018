#include <StringTok.h>
#define SERIAL_BPS  (9600)
#define DELAY_MS  (500)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BPS);
}

void loop() {
  // put your main code here, to run repeatedly:
  String sInput = inputString();
  double ans = processString(sInput);
  printString(ans);
  delay(DELAY_MS);
}

String inputString() {
  String sInput;
  return sInput;
}

double processString(String sInput) {
  double ans = 0.;
  StringTok stToken;
  return ans;
}

void printString(double ans) {
  Serial.print("답 = "); Serial.println(ans);
}

double funAdd(double a, double b) {
  return a + b;
}

double funSub(double a, double b) {
  return a - b;
}

