/////////////////////////////////////////////
// 1. Sensor port pin 정보를 바꾸고 싶으면 initSensorPort() 함수에서 조정
/////////////////////////////////////////////
#include <StringTok.h>
#define NUM_SENSOR_ARD  (3)
#define SERIAL_BPS    (9600)
#define SERIAL_BTH_BPS  (115200)
#define ARD_BTH_RX    (10)
#define ARD_BTH_TX    (11)
#define VOLT_PREC   (1000)

// Sensor 설정값, 측정값
class MySensor {
  public:
    int m_nPort[NUM_SENSOR_ARD];
    boolean m_bPort[NUM_SENSOR_ARD];
    double m_val1[NUM_SENSOR_ARD];
    double m_val2[NUM_SENSOR_ARD];
    int m_nAvgSize[NUM_SENSOR_ARD];
    int m_nDelayAvg[NUM_SENSOR_ARD];
};

class MyProtocol {
  public:
    boolean m_bStart; // true: 통신 mode, false: 설정 mode
    int m_nDelay;
};

// 전역 변수(global variables)
MySensor g_mySensor;
MyProtocol g_myProtocol;
SoftwareSerial serialBth(ARD_BTH_RX, ARD_BTH_TX);

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
  serialCommTx(sSensor);
  sensorProtocolRx(sSensor, g_mySensor, g_myProtocol);
  // Delay
  delay(g_myProtocol.m_nDelay);
}

void initSensor(MySensor & mySensor) {
  for (int i = 0; i < NUM_SENSOR_ARD; i++) {
    mySensor.m_bPort[i] = true;
    mySensor.m_val1[i] = 0.;
    mySensor.m_val2[i] = 0.;
    mySensor.m_nAvgSize[i] = 1;
    mySensor.m_nDelayAvg[i] = 10;
  }
  initSensorPort(mySensor);
}

void initSensorPort(MySensor & mySensor) {
  mySensor.m_nPort[0] = A0; // Voltage sensor
  mySensor.m_nPort[1] = A1; // Pressure sensor
  mySensor.m_nPort[2] = A2; // Temperature sensor
}

void initProtocol(MyProtocol & myProtocol) {
  myProtocol.m_bStart = false;
  myProtocol.m_nDelay = 1000;
}

void initSerial() {
  Serial.begin(SERIAL_BPS);
}

void initBth() {
  serialBth.begin(SERIAL_BTH_BPS);
}

void sensorMeas(MySensor & mySensor, MyProtocol & myProtocol) {
  if (!myProtocol.m_bStart) return;
  if (mySensor.m_bPort[0])  // Sensor #0?
    mySensor.m_val1[0] = getSensor0(mySensor, myProtocol);
  if (mySensor.m_bPort[1])  // Sensor #1?
    mySensor.m_val1[1] = getSensor1(mySensor, myProtocol);
  if (mySensor.m_bPort[2])  // Sensor #2?
    mySensor.m_val1[2] = getSensor2(mySensor, myProtocol);
}

double getSensorAvg(int nSensor, MySensor & mySensor, MyProtocol & myProtocol) {
  double sum = 0.;
  for (int i = 0; i < mySensor.m_nAvgSize[nSensor]; i++)
  {
    sum += getVolt(mySensor.m_nPort[nSensor]);
    delay(mySensor.m_nDelayAvg[nSensor]);
  }
  return sum/(double)mySensor.m_nAvgSize[nSensor];
}

// Voltage sensor
double getSensor0(MySensor & mySensor, MyProtocol & myProtocol) {
  return getSensorAvg(0, mySensor, myProtocol);
}

double getVolt(int nPort) {
  int nVolt = analogRead(nPort);
  double volt = map(nVolt, 0, 1023, 0, 5 * VOLT_PREC) / (double)VOLT_PREC;
  return volt;
}

// Pressure sensor
double getSensor1(MySensor & mySensor, MyProtocol & myProtocol) {
  return getSensorAvg(1, mySensor, myProtocol);
}

// Temperature sensor
double getSensor2(MySensor & mySensor, MyProtocol & myProtocol) {
  return getSensorAvg(2, mySensor, myProtocol);
}

String sensorProtocolTx(MySensor & mySensor, MyProtocol & myProtocol) {
  if (!myProtocol.m_bStart) return "";
  String sSensor;
  if (mySensor.m_bPort[0])  // Sensor #0?
    sSensor += "getsen 0 " + String(mySensor.m_val1[0], 5) + "\r\n";
  if (mySensor.m_bPort[1])  // Sensor #1?
    sSensor += "getsen 1 " + String(mySensor.m_val1[1], 5) + "\r\n";
  if (mySensor.m_bPort[2])  // Sensor #2?
    sSensor += "getsen 2 " + String(mySensor.m_val1[2], 5) + "\r\n";
  return sSensor;
}

void bthCommTx(String & sSensor) {
  if (sSensor.length() > 0) serialBth.println(sSensor);
}

void serialCommTx(String & sSensor) {
  if (sSensor.length() > 0) Serial.println(sSensor);
}

void sensorProtocolRx(String & sSensor, MySensor & mySensor, MyProtocol & myProtocol) {
  if (sSensor.length() <= 0)  return;
  StringTok sInput(sSensor);
  StringTok sToken;
  sToken = sInput.getToken();
  if (sToken.toString() == "start") myProtocol.m_bStart = true;
  else if (sToken.toString() == "stop") myProtocol.m_bStart = false;
  else if (sToken.toString() == "setsen") protoSetSen(sInput, mySensor);  // ex: setsen 0 on
  else if (sToken.toString() == "delay")  protoDelay(sInput, myProtocol); // ex: delay 3000
  else if (sToken.toString() == "avgsize") protoAvgSize(sInput, mySensor);  // ex: avgsize 0 100
  else if (sToken.toString() == "delayavg") protoDelayAvg(sInput, mySensor);  // ex: delayavg 0 5
}

// ex: setsen 0 on
void protoSetSen(StringTok & sInput, MySensor & mySensor) {
  StringTok sToken;
  int nPort;
  boolean bPort;
  sToken = sInput.getToken(); nPort = sToken.atoi();
  sToken = sInput.getToken();
  if (sToken.toString() == "on")  bPort = true;
  else if (sToken.toString() == "off")  bPort = false;
  mySensor.m_bPort[nPort] = bPort;
}

// ex: delay 3000
void protoDelay(StringTok & sInput, MyProtocol & myProtocol) {
  StringTok sToken;
  int nDelay;
  sToken = sInput.getToken(); nDelay = sToken.atoi();
  myProtocol.m_nDelay = nDelay;  
}

// ex: avgsize 0 100
void protoAvgSize(StringTok & sInput, MySensor & mySensor) {
  StringTok sToken;
  int nPort, nAvgSize;
  sToken = sInput.getToken(); nPort = sToken.atoi();
  sToken = sInput.getToken(); nAvgSize = sToken.atoi();
  mySensor.m_nAvgSize[nPort] = nAvgSize;
}

// ex: delayavg 0 5
void protoDelayAvg(StringTok & sInput, MySensor & mySensor) {
  StringTok sToken;
  int nPort, nDelayAvg;
  sToken = sInput.getToken(); nPort = sToken.atoi();
  sToken = sInput.getToken(); nDelayAvg = sToken.atoi();
  mySensor.m_nDelayAvg[nPort] = nDelayAvg;
}

String bthCommRx() {
  StringTok sInputBth;
  sInputBth.inputSerial(serialBth);
  return sInputBth.toString();
}
