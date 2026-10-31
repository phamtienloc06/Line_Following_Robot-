#include <EEPROM.h>
#include "motor.h"
#include "sensors.h"
#include "run.h"
#include "khaibao.h"
void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(OK, INPUT_PULLUP);
  pinMode(MODE, INPUT_PULLUP);
  
  digitalWrite(STBY, HIGH);   // bật TB6612
  // ===== I2C REMAP PB8 PB9 (QUAN TRỌNG) =====
  Wire.setSCL(PB8);
  Wire.setSDA(PB9);
  Wire.begin();

  setupOLED();
  setupVL53L0X();
  motorPWMInit();
  encoderInit();

  BT.begin(115200);          // HC-05 / HC-06 (PB10 PB11)
  calibrated = loadCalibEEPROM();
   
}

static inline void showEncoderOLED(long left, long right) {
  static unsigned long last = 0;
  if (millis() - last < 100) return;   // chống nháy OLED
  last = millis();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("ENCODER");

  display.setCursor(0, 12);
  display.print("L: ");
  display.print(left);

  display.setCursor(0, 22);
  display.print("R: ");
  display.print(right);

  display.display();
}
// ================== LOOP ==================
void loop() {
  static int lastMode = -1;
  static bool running = false;
  // ===== CHỌN MODE =====
  if (digitalRead(MODE) == LOW) {
    delay(200);
    mode = (mode + 1) % 5;
    while (digitalRead(MODE) == LOW);
  }

  if (mode != lastMode) {
  BT.print("Mode = ");
  BT.println(mode);
  lastMode = mode;
  running = false;

  // ===== HIỂN THỊ MODE LÊN OLED =====
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("MODE: ");
  display.print(mode);

  display.setCursor(0, 12);
  if (mode == 0) display.print("RUN PID");
  else if (mode == 1) display.print("TEST SENSOR");
  else if (mode == 2) display.print("CALIBRATE");
  else if (mode == 3) display.print("SHOW EEPROM");
  else if (mode == 4) display.print("RUN PID2");

  display.display();
}


  // ===== OK: START / STOP =====
  if (digitalRead(OK) == LOW) {
    delay(200);
    while (digitalRead(OK) == LOW);
    running = !running;
    BT.print("Running = ");
    BT.println(running);
    if (running) {                 // <-- THÊM Ở ĐÂY
    startTime = millis();
    startDone = false;
    resetEncoder();   // ⭐ THÊM Ở ĐÂY
  }
  }
  // ===== MODE 0: CALIBRATE =====
  if (mode == 2 && running ) {
    calibrate();
    calibrated = true;
    running = false;
  }
  // ===== MODE 1: TEST SENSOR =====
  if (mode == 1 && running) {
  static bool done = false;

  if (!startDone && millis() - startTime < 1000) {
    motores(0, 0);
    return;
  }
  startDone = true;

  if (!done) {
     turnLeft(45);   // quay đúng 1 lần
    done = true;
  }
}
  // ===== MODE 2: RUN PID =====
  if (mode == 0 && running&& calibrated) {
    if (!startDone && millis() - startTime < 1000) {
    motores(0, 0);
    return;
  }
  startDone = true;
    if(step==0){
    go0(150);
    step=1;
    
    }
    else if(step==1){
    updateLine();
    PID();
     if (millis() - lastToF >= 20) { // 20,000 µs = 20 ms
    FSensors();
    lastToF = millis();}
    }
    else if(step==2){
    updateLine();
    PID1();
    }
    else if(step==3){
      go(40);
      step=4;
    }
    else if(step==4){
    updateLine();
    PID5();
    }
    else if(step==5){
      go(9);
      turnRight(55);
      step=6;
    }
    else if(step==6){
      go(120);
      step=7;
    }
    else if(step==7){
      turnRight(55);
      step=8;
    }
    else if(step==8){
      go2(250);
      step=9;
    }
    else if(step==9){
    updateLine();
    PID8();
    }
    else if(step==10){
    turnLeft(25);
    step=11;
    }
    else if(step==11){
    updateLine();
    PID9();
    }
    else if(step==12){
      // go(9);
      turnLeft(60);
      step=13;
    }
    else if(step==13){
    go3(120);
    step=14;
    }
    else if(step==14){
    updateLine();
    PID14();
    }
    else if(step==15){
      went(5,50);
      turnRight(60);
      step=16;
    }
    else if(step==16){
      updateLine();
      PID16();
    }

    else{};
    
  }
  if (mode == 4 && running&& calibrated) {
  
  showEncoderOLED(countA, countB);
    
  }
  if (mode == 3 && running) {
  readLine();
}

}

