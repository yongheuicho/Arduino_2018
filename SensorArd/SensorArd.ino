// Sensor 설정값, 측정값
class MySensor {
public:
 double m_val1;  
};

// 전역 변수
MySensor mySensor;

void setup() {
  // put your setup code here, to run once:
  initSensor(mySensor);
  initSerial();
  initBth();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Tx
  sensorMeas(mySensor);
  sensorProtocol();
  bthComm();
}

void initSensor(MySensor & mySensor) {
  
}

void initSerial() {
  
}

void initBth() {
  
}

void sensorMeas(MySensor & mySensor) {
  
}

void sensorProtocol() {
  
}

void bthComm() {
  
}

