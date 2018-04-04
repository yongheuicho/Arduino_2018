#include <StringTok.h>
#define NUM_SENSOR_ARD  (3)

// Sensor 설정값, 측정값
class MySensor {
  public:
    int m_nPort[NUM_SENSOR_ARD];
    boolean m_bPort[NUM_SENSOR_ARD];
    double m_val1[NUM_SENSOR_ARD];
    double m_val2[NUM_SENSOR_ARD];
};

class MyProtocol {
  public:
    boolean m_bStart; // true: 통신 mode, false: 설정 mode
    int m_nDelay, m_nAvgSize, m_nDelayAvg;  
};

// 전역 변수(global variables)
MySensor g_mySensor;
MyProtocol g_myProtocol;

void setup() {
  // put your setup code here, to run once:
  initSensor(g_mySensor);
  initProtocol(g_myProtocol);
  initSerial();
  initBth();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Tx
  sensorMeas(g_mySensor, g_myProtocol);
  String sSensor = sensorProtocolTx(g_mySensor, g_myProtocol);
  bthCommTx(sSensor);
  serialCommTx(sSensor);
  // Rx
  sSensor = bthCommRx();
  sensorProtocolRx(sSensor, g_myProtocol);
}

void initSensor(MySensor & mySensor) {

}

void initProtocol(MyProtocol & myProtocol) {

}

void initSerial() {

}

void initBth() {

}

void sensorMeas(MySensor & mySensor, MyProtocol & myProtocol) {

}

String sensorProtocolTx(MySensor & mySensor, MyProtocol & myProtocol) {
  String sSensor;
  return sSensor;
}

void bthCommTx(String & sSensor) {

}

void serialCommTx(String & sSensor) {

}

void sensorProtocolRx(String & sSensor, MyProtocol & myProtocol) {

}

String bthCommRx() {
  String sSensor;
  return sSensor;
}
