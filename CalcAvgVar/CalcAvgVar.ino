#define SERIAL_BPS  (9600)
#define DELAY_MS    (1000)
#define VOLT_PREC   (1000)
#define VOLT_AR_SIZE  (10) // Voltage array size
#define VOLT_DELAY    (10)  // Voltage measuring delay [ms]

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BPS);
}

void loop() {
  // put your main code here, to run repeatedly:
  int nPort = 0;
  double arVolt[VOLT_AR_SIZE];
  int nVoltSize = VOLT_AR_SIZE;
  int nVoltDelay = VOLT_DELAY;
  fillArrayVolt(nPort, arVolt, nVoltSize, nVoltDelay);
//  printArrayVolt(arVolt, nVoltSize);
  double avg = getAvg(arVolt, nVoltSize);
  double var = getVar(arVolt, nVoltSize, avg);
  printVolt(avg, var);
  delay(DELAY_MS);
}

double getVolt(int nPort) {
  int nVolt = analogRead(nPort);
  double volt = map(nVolt, 0, 1023, 0, 5 * VOLT_PREC) / (double)VOLT_PREC;
  return volt;
}

void fillArrayVolt(int nPort, double arVolt[], int nSize, int nDelay) {
  for (int i = 0; i < nSize; i++) {
    double volt = getVolt(nPort);
    arVolt[i] = volt;
    delay(nDelay);
  }
}

double getAvg(double arVolt[], int nSize) {
  double sum = 0.;
  for (int i = 0; i < nSize; i++)
    sum += arVolt[i];
  return sum/(double)nSize;
}

double getVar(double arVolt[], int nSize, double avg) {
  double sum = 0.;
  for (int i = 0; i < nSize; i++)
    sum += (arVolt[i] - avg)*(arVolt[i] - avg);
  return sum/(double)nSize;
}

void printVolt(double volt, double noisePow) {
  Serial.print("전압 = ");  Serial.println(volt);
  Serial.print("잡음 전력 = ");  Serial.println(noisePow, 10);
}

void printArrayVolt(double arVolt[], int nSize) {
  for (int i = 0; i < nSize; i++) {
    Serial.print(arVolt[i]);
    Serial.print(" ");
  }
}



