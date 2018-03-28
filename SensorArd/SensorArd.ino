// Sensor 설정값, 측정값
class MySensor {
  public:
    double m_val1;
};

class MyProtocol {
  public:
};

// 전역 변수
MySensor mySensor;
MyProtocol myProtocol;

void setup() {
  // put your setup code here, to run once:
  initSensor(mySensor);
  initProtocol(myProtocol);
  initSerial();
  initBth();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Tx
  sensorMeas(mySensor);
  String sSensor = sensorProtocol(mySensor, myProtocol);
  bthComm(sSensor);
}

void initSensor(MySensor & mySensor) {

}

void initProtocol(MyProtocol & myProtocol) {

}

void initSerial() {

}

void initBth() {

}

void sensorMeas(MySensor & mySensor) {

}

String sensorProtocol(MySensor & mySensor, MyProtocol & myProtocol) {
  String sSensor;
  return sSensor;
}

void bthComm(String & sSensor) {

}

