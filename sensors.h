#ifndef sensors
#define sensors
#include "khaibao.h"
#include <VL53L0X.h>
#include"oled.h"
VL53L0X sensorF;
int senF;
static inline  void setupVL53L0X(){
  pinMode(XshutF, OUTPUT);
  digitalWrite(XshutF,LOW);
  digitalWrite(XshutF, HIGH);
  delay(100);
  sensorF.init();
  sensorF.setAddress(0x32);

  sensorF.startContinuous();
}
void FSensors(){
  senF = sensorF.readRangeContinuousMillimeters() / 10;
}
void readFSensors(){
  FSensors();
  display.clearDisplay();

  display.setCursor(0, 0);
  display.print(senF);
  display.display();
}
static inline bool NEAR() {
  if (senF > 0 && senF < KHOANGCACH) return true;
  return false;
}

static inline bool AVOID() {

  // ===== STEP 0: IDLE =====
  if (avoidStep == 0) {
    if (!NEAR()) return false;
    avoidStep = 1;
    avoidTime = millis();
    return true;
  }

  // ===== STEP 1: STOP =====
  if (avoidStep == 1) {
    motoresStop();
    if (millis() - avoidTime > STOP_TIME) {
      avoidStep = 2;
      avoidTime = millis();
    }
    return true;
  }

  // ===== STEP 2: TURN 45° (1) =====
  if (avoidStep == 2) {
    motores(-avoidDir * TURN_SPEED, +avoidDir * TURN_SPEED);
    if (millis() - avoidTime > TURN45_TIME) {
      avoidStep = 3;
      avoidTime = millis();
    }
    return true;
  }

  // ===== STEP 3: GO STRAIGHT (1) =====
  if (avoidStep == 3) {
    motores(GO_SPEED, GO_SPEED);
    if (millis() - avoidTime > GO_SHORT) {
      avoidStep = 4;
      avoidTime = millis();
    }
    return true;
  }
  // ===== STEP 8: TURN 45° (4 – về hướng cũ) =====
  if (avoidStep == 4) {
    motores(+avoidDir * TURN_SPEED, -avoidDir * TURN_SPEED);
    if (sumSensor > 0) {
    avoidStep = 5;   // DONE → về PID

    // reset PID cho mượt
    ePrev = 0;
    eSum  = 0;
  }
  if (avoidStep == 5) {
    step=2;
    avoidStep = 0;   // DONE → về PID
    // reset PID cho mượt
    ePrev = 0;
    eSum  = 0;
  }

    return true;
  }
  
  return false;
}
static inline bool AVOIDBLUE() {

  // ===== STEP 0: IDLE =====
  if (avoidStep == 0) {
    if (!NEAR()) return false;
    avoidStep = 1;
    avoidTime = millis();
    return true;
  }

  // ===== STEP 1: STOP =====
  if (avoidStep == 1) {
    motoresStop();
    if (millis() - avoidTime > STOP_TIME) {
      avoidStep = 2;
      avoidTime = millis();
    }
    return true;
  }

  // ===== STEP 2: TURN 45° (1) =====
  if (avoidStep == 2) {
    motores(avoidDir * TURN_SPEED, -avoidDir * TURN_SPEED);
    if (millis() - avoidTime > TURN45_TIME) {
      avoidStep = 3;
      avoidTime = millis();
    }
    return true;
  }

  // ===== STEP 3: GO STRAIGHT (1) =====
  if (avoidStep == 3) {
    motores(GO_SPEED, GO_SPEED);
    if (millis() - avoidTime > GO_SHORT) {
      avoidStep = 4;
      avoidTime = millis();
    }
    return true;
  }
  // ===== STEP 8: TURN 45° (4 – về hướng cũ) =====
  if (avoidStep == 4) {
    motores(-avoidDir * TURN_SPEED, avoidDir * TURN_SPEED);
    if (sumSensor > 0) {
    avoidStep = 5;   // DONE → về PID

    // reset PID cho mượt
    ePrev = 0;
    eSum  = 0;
  }
  if (avoidStep == 5) {
    step=2;
    avoidStep = 0;   // DONE → về PID
    // reset PID cho mượt
    ePrev = 0;
    eSum  = 0;
  }

    return true;
  }
  
  return false;
}

struct CalibData {
  uint8_t  magic;
  uint16_t minVal[num];
  uint16_t maxVal[num];
  uint16_t threshold[num];
};

CalibData calib;
static inline void saveCalibEEPROM() {

  calib.magic = EEPROM_MAGIC;

  for (uint8_t i = 0; i < num; i++) {
    calib.minVal[i]    = ValueMin[i];
    calib.maxVal[i]    = ValueMax[i];
    calib.threshold[i] = threshold[i];
  }
  EEPROM.put(0, calib);
  BT.println("EEPROM SAVED");
}
static inline bool loadCalibEEPROM() {
  EEPROM.get(0, calib);
  if (calib.magic != EEPROM_MAGIC) {
    BT.println("EEPROM INVALID");
    return false;
  }
  for (uint8_t i = 0; i < num; i++) {
    ValueMin[i]  = calib.minVal[i];
    ValueMax[i]  = calib.maxVal[i];
    threshold[i] = calib.threshold[i];
  }
  BT.println("EEPROM LOADED");
  return true;
}


// ------------------- HÀM ĐỌC CẢM BIẾN -------------------
static inline void readSensor() {
  for (uint8_t i = 0; i < num; i++) {
    sensorValue[i] = analogRead(sensorPin[i]); // 0–4095 (12-bit)
  }
}
static inline void printSensor() {
  readSensor();   // đọc trước

  for (uint8_t i = 0; i < num; i++) {
    BT.print(sensorValue[i]);
    BT.print(' ');   // cách nhau bằng tab
  }
  BT.println();
}

static inline void calibrate() {
  for (uint8_t i = 0; i < num; i++) {
    ValueMin[i] = 1023;
    ValueMax[i] = 0;
  }
  unsigned long start = millis();
  while (millis() - start < 5000) {
    readSensor();
    for (uint8_t i = 0; i < num; i++) {
      uint16_t val = sensorValue[i];
      if (val < ValueMin[i]) ValueMin[i] = val;
      if (val > ValueMax[i]) ValueMax[i] = val;
    }
    delay(3);
  }
  for (uint8_t i = 0; i < num; i++) {
    threshold[i] = (ValueMin[i] + ValueMax[i]) /2;
  }
  saveCalibEEPROM();
  // Debug
  BT.println("CALIB DONE:");
  for (uint8_t i = 0; i < num; i++) {
    BT.print("S"); BT.print(i);
    BT.print(" Min="); BT.print(ValueMin[i]);
    BT.print(" Max="); BT.print(ValueMax[i]);
    BT.print(" Th=");  BT.println(threshold[i]);
  }
  delay(300);
}
static inline void readLine() {
  sumSensor = 0;
  sumWeight = 0;
  readSensor();   // đọc sensorValue[]
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  // ----- Dòng 1: S0 - S3 -----
  display.setCursor(0, 0);
  for (uint8_t i = 0; i < num; i++) {
    if (sensorValue[i] > threshold[i])
      S[i] = 0;
    else
      S[i] = 1;
      sumSensor += S[i];
      sumWeight += S[i] * weightValue[i];

    // IN SENSOR
    display.print(S[i]);
    display.print(' ');
  }

  // ----- Dòng 3: sumSensor -----
  display.setCursor(0, 10);
  display.print("Sensor:");
  display.print(sumSensor);

  // ----- Dòng 4: sumWeight -----
  display.setCursor(64, 10);
  display.print("W:");
  display.print(sumWeight);

  display.display();
}
static inline void updateLine() {
  sumSensor = 0;
  sumWeight = 0;

  readSensor();   // đọc sensorValue[]
  for (uint8_t i = 0; i < num; i++) {
    if (sensorValue[i] > threshold[i]) S[i] = 0;
    else S[i] = 1;
    sumSensor += S[i];
    sumWeight += S[i] * weightValue[i];
  
}
}
static inline void printMINMAXTH() {
  BT.println("=== EEPROM MIN / MAX / TH ===");
  for (uint8_t i = 0; i < num; i++) {
    BT.print("S"); BT.print(i);
    BT.print("  min=");
    BT.print(ValueMin[i]);
    BT.print("  max=");
    BT.print(ValueMax[i]);
    BT.print("  th=");
    BT.println(threshold[i]);
  }
  BT.println("============================");
}

#endif