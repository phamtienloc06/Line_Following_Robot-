#ifndef run
#define run
#include "khaibao.h"
#include"oled.h"
/* ================== LINE STATE ================== */
uint8_t State() {

  /* ===== FULL BLACK: ĐẾM TỪ LẦN ĐẦU ===== */
  if (sumSensor >=6) return BLACK;           
  /* ===== MẤT LINE ===== */
  if (sumSensor == 0) return MATLINE;

  /* ===== LINE THƯỜNG ===== */
  if ((S[3] || S[4]) && sumSensor >= 2 && sumSensor <= 4)
    return BAMLINE;

  if (S[0]) return LEFT;
  if (S[7]) return RIGHT;

  return BAMLINE;
}

static inline void PID() {
  speed = baseSpeed;
  uint8_t state = State();
  if (AVOID()) {return;}
  if(dem==1){
  if (state == MATLINE) {
    motoresStop();
    motores(60,-60);
    delay(200);
    dem=999;
    return;
  }}
  else{
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motores(baseSpeed, baseSpeed);
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  }
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, speed-upspeed, speed+upspeed);
    rightSpeed = constrain(rightSpeed, speed-upspeed, speed+upspeed);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PIDBLUE() {
  speed = baseSpeed;
  uint8_t state = State();
  if (AVOIDBLUE()) {return;}
  if(dem==1){
  if (state == MATLINE) {
    motoresStop();
    motores(-60,60);
    delay(200);
    dem=999;
    return;
  }}
  else{
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motores(baseSpeed, baseSpeed);
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  }
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, speed-upspeed, speed+upspeed);
    rightSpeed = constrain(rightSpeed, speed-upspeed, speed+upspeed);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PID1() {
  speed = 120;
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motoresStop();
      step=3;
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, speed-upspeed, speed+upspeed);
    rightSpeed = constrain(rightSpeed, speed-upspeed, speed+upspeed);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PID8() {
  speed = baseSpeed;
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motoresStop();
      step=10;
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, speed-upspeed, speed+upspeed);
    rightSpeed = constrain(rightSpeed, speed-upspeed, speed+upspeed);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PID9() {
  speed = baseSpeed;
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motoresStop();
      step=12;
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, speed-upspeed, speed+upspeed);
    rightSpeed = constrain(rightSpeed, speed-upspeed, speed+upspeed);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PIDgo3() {
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motoresStop();
      
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, speed-upspeed, speed+upspeed);
    rightSpeed = constrain(rightSpeed, speed-upspeed, speed+upspeed);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PID14() {
  speed=50;
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motoresStop();
      step=15;
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, speed-upspeed, speed+upspeed);
    rightSpeed = constrain(rightSpeed, speed-upspeed, speed+upspeed);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PID16() {
  speed=50;
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motoresStop();
      step=17;
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, -speedmax, speedmax);
    rightSpeed = constrain(rightSpeed, -speedmax, speedmax);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PID5() {
  speed = baseSpeed;
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motoresStop();
      step=5;
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, speed-upspeed, speed+upspeed);
    rightSpeed = constrain(rightSpeed, speed-upspeed, speed+upspeed);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}

static inline void PIDgo() {
  speed = baseSpeed;
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime <150) {
       motores(80,80);
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, -speedmax, speedmax);
    rightSpeed = constrain(rightSpeed, -speedmax, speedmax);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PIDwent() {
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime <3000) {
       motores(speed*2/3,speed*2/3);
      return;
    }
    motores(lastTurn  <0 ? -speed/2 : speed/2, lastTurn < 0 ?  speed/2 :  -speed/2);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, -speedmax, speedmax);
    rightSpeed = constrain(rightSpeed, -speedmax, speedmax);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
static inline void PIDgo0() {
  speed = 120;
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime <10) {
       motores(80,80);
      return;
    }
    motores(lastTurn  <0 ? -80 :80, lastTurn < 0 ? 80 : -80);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, -speedmax, speedmax);
    rightSpeed = constrain(rightSpeed, -speedmax, speedmax);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}

static inline void PIDgo2() {
  speed = baseSpeed;
  uint8_t state = State();
    if (state == MATLINE) {

    motores(90,90);
    return;
  }
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, -speedmax, speedmax);
    rightSpeed = constrain(rightSpeed, -speedmax, speedmax);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}

static inline void PID2() {
  speed = baseSpeed;
  uint8_t state = State();
    if (state == MATLINE) {
    if (millis() - lostTime < LINETIME) {
      motores(baseSpeed, baseSpeed);
      step=6;
      return;
    }
    motores(lastTurn  <0 ? -60 : 60, lastTurn < 0 ? 60 : -60);
    return;
  }
  
  lostTime = millis();
  // -------- CUA --------
  if (state == LEFT) {
    lastTurn = -1;
  }
  if (state == RIGHT) {
    lastTurn = 1;
  }
  // -------- PID --------
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;
    dE = eCurr - ePrev;
    eSum += eCurr;
    // eSum = constrain(eSum, -80, 80);
    u = Kp * eCurr + Kd * dE + Ki * eSum;
    int leftSpeed  = speed - u;
    int rightSpeed = speed + u;
    leftSpeed  = constrain(leftSpeed, speed-upspeed, speed+upspeed);
    rightSpeed = constrain(rightSpeed, speed-upspeed, speed+upspeed);
    motores(leftSpeed, rightSpeed);
    ePrev = eCurr;
}
void went(int cm,int speed) {
  int pulse = cm*200/63 ;
  eSum = 0;
  ePrev = 0;
  motores(0, 0);
  delay(10);
  resetEncoder();
  delay(5);
  // hãm sớm 1 chút
  while ((abs(countA)+abs(countB))/2 < pulse) {
    updateLine();
    PIDgo();
  }
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("S=:  ");
    display.print(cm);
    display.print("cm ");

    display.setCursor(0, 8);
    display.print("A:  ");
    display.print(abs(countA));

    display.setCursor(0, 16);
    display.print("B:  ");
    display.print(abs(countB));

    display.setCursor(0, 24);
    display.print("(A+B)/2:  ");
    display.print((abs(countA)+abs(countB))/2);
    display.display();
  motoresStop();
  delay(30);
  resetEncoder();
}
// ================= LINE GO =================
void go(int cm) {
  int pulse = cm*200/63 ;
  eSum = 0;
  ePrev = 0;
  motores(0, 0);
  delay(10);
  resetEncoder();
  delay(5);
  // hãm sớm 1 chút
  while ((abs(countA)+abs(countB))/2 < pulse) {
    updateLine();
    PIDgo();
  }
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("S=:  ");
    display.print(cm);
    display.print("cm ");

    display.setCursor(0, 8);
    display.print("A:  ");
    display.print(abs(countA));

    display.setCursor(0, 16);
    display.print("B:  ");
    display.print(abs(countB));

    display.setCursor(0, 24);
    display.print("(A+B)/2:  ");
    display.print((abs(countA)+abs(countB))/2);
    display.display();
  motoresStop();
  delay(30);
  resetEncoder();
}
void go0(int cm) {
  int pulse = cm*200/63 ;
  eSum = 0;
  ePrev = 0;
  motores(0, 0);
  delay(10);
  resetEncoder();
  delay(5);
  // hãm sớm 1 chút
  while ((abs(countA)+abs(countB))/2 < pulse) {
    updateLine();
    PIDgo0();
  }
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("S=:  ");
    display.print(cm);
    display.print("cm ");

    display.setCursor(0, 8);
    display.print("A:  ");
    display.print(abs(countA));

    display.setCursor(0, 16);
    display.print("B:  ");
    display.print(abs(countB));

    display.setCursor(0, 24);
    display.print("(A+B)/2:  ");
    display.print((abs(countA)+abs(countB))/2);
    display.display();
  motoresStop();
  delay(30);
  resetEncoder();
}
void go3(int cm) {
  int pulse = cm * 200 / 63;
  int pulse_fast = pulse * 2 / 3;   // 2/3 quãng đường

  eSum = 0;
  ePrev = 0;

  motores(0, 0);
  delay(10);
  resetEncoder();
  delay(5);

  while ((abs(countA) + abs(countB)) / 2 < pulse) {
    updateLine();

    int curPulse = (abs(countA) + abs(countB)) / 2;

    if (curPulse < pulse_fast) {
      speed = 200;          // 🚀 chạy nhanh 2/3 đầu
    } else {
      speed = 50;   // 🐢 giảm tốc 1/3 cuối
    }

    PIDgo3();
  }

  motoresStop();
  delay(30);
  resetEncoder();
}

void go2(int cm) {
  int pulse = cm*200/63 ;
  eSum = 0;
  ePrev = 0;
  motores(0, 0);
  delay(10);
  resetEncoder();
  delay(5);
  // hãm sớm 1 chút
  while ((abs(countA)+abs(countB))/2 < pulse) {
    updateLine();
    PIDgo2();
  }
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("S=:  ");
    display.print(cm);
    display.print("cm ");

    display.setCursor(0, 8);
    display.print("A:  ");
    display.print(abs(countA));

    display.setCursor(0, 16);
    display.print("B:  ");
    display.print(abs(countB));

    display.setCursor(0, 24);
    display.print("(A+B)/2:  ");
    display.print((abs(countA)+abs(countB))/2);
    display.display();
  motoresStop();
  delay(30);
  resetEncoder();
}
// ================= RUN SCRIPT =================
// static inline void Running() {
  

//   switch (step) {

//     case 0:   // rẽ trái
//       if (turnLeft(80, 150)) step++;
//       break;

//     case 1:   // đi thẳng PID
//       if (go(60, 200)) step++;
//       break;

//     case 2:   // rẽ phải
//       if (turnRight(60, 180)) step++;
//       break;

//     case 3:   // đi thẳng 
//       if (go(60, 300)) step++;   
//       break;

//     default:  // kết thúc
//       motoresStop();
//       break;
//   }
// }

#endif
