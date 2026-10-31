#ifndef motor
#define motor

#include <Arduino.h>
#include "khaibao.h"
#include "oled.h"

/* =====================================================
   MOTOR PWM INIT
   ===================================================== */
static inline void motorPWMInit() {
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);

  analogWriteFrequency(20000);   // 20 kHz cho TB6612
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

/* =====================================================
   SET PWM
   ===================================================== */
static inline void setMotorPWM(uint8_t pwmA, uint8_t pwmB) {
  analogWrite(PWMA, pwmA);
  analogWrite(PWMB, pwmB);
}

/* =====================================================
   MOTOR CONTROL
   ===================================================== */
static inline void motores(int pwmA, int pwmB) {
  pwmA = constrain(pwmA, -255, 255);
  pwmB = constrain(pwmB, -255, 255);

  // Motor A (phải)
  if (pwmA > 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else if (pwmA < 0) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }

  // Motor B (trái)
  if (pwmB > 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else if (pwmB < 0) {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }

  setMotorPWM(abs(pwmA), abs(pwmB));
}

/* =====================================================
   MOTOR STOP (BRAKE)
   ===================================================== */
static inline void motoresStop() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
  setMotorPWM(255, 255);
}

/* =====================================================
   ENCODER – X1 (2 INTERRUPT, ỔN ĐỊNH)
   ===================================================== */

volatile int32_t countA = 0;   // bánh phải
volatile int32_t countB = 0;   // bánh trái

/* ---------- ISR ---------- */
void readEncA() {
  if (digitalRead(ENCA_B)) countA++;
  else                     countA--;
}

void readEncB() {
  if (digitalRead(ENCB_B)) countB++;
  else                     countB--;
}

/* ---------- INIT ---------- */
static inline void encoderInit() {
  pinMode(ENCA_A, INPUT_PULLUP);
  pinMode(ENCA_B, INPUT_PULLUP);
  pinMode(ENCB_A, INPUT_PULLUP);
  pinMode(ENCB_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCA_A), readEncA, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCB_A), readEncB, RISING);

  countA = 0;
  countB = 0;
}

/* ---------- RESET ---------- */
static inline void resetEncoder() {
  noInterrupts();
  countA = 0;
  countB = 0;
  interrupts();
}

/* =====================================================
   BASIC MOTION
   ===================================================== */

void turnLeft(int counts_90) {
  int speed=80;
  motores(0, 0);
  delay(10);

  resetEncoder();
  delay(5);

  // quay nhanh
  motores(-speed, speed);

  // hãm sớm 1 chút
  while (abs(countB) < counts_90 /2) {}

  motores(-50, 50);   // ⭐ speed MIN motor chạy được

  while (abs(countB) < counts_90) {}
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("TURN LEFT");

    display.setCursor(0, 12);
    display.print("Pulse: ");
    display.print(abs(countB));

    display.display();
  motoresStop();
  delay(30);
  resetEncoder();
}


/* =====================================================
   TURN RIGHT
   ===================================================== */
void turnRight(int counts_90) {
  int speed=80;
  
  motores(0, 0);
  delay(10);

  resetEncoder();
  delay(5);

  // quay nhanh
  motores(speed, -speed);

  // hãm sớm 1 chút
  while (abs(countA) < counts_90 /2) {}

  motores(50, -50);   // ⭐ speed MIN motor chạy được

  while (abs(countA) < counts_90) {}
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("TURN RIGHT");

    display.setCursor(0, 12);
    display.print("Pulse: ");
    display.print(abs(countA));

    display.display();
  motoresStop();
  delay(30);
  resetEncoder();
}
void GoLeft(int speed) {
  int counts_90=110;
  motores(0, 0);
  delay(10);

  resetEncoder();
  delay(5);

  // quay nhanh
  motores(speed*0.25, speed);

  // hãm sớm 1 chút
  while (abs(countB) < counts_90 /2) {}

  motores(80*0.25, 80);   // ⭐ speed MIN motor chạy được

  while (abs(countB) < counts_90) {}
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("TURN LEFT");

    display.setCursor(0, 12);
    display.print("Pulse: ");
    display.print(abs(countB));

    display.display();
  motoresStop();
  delay(30);
  resetEncoder();
}
void GoRight(int speed) {
  int counts_90=110;
  motores(0, 0);
  delay(10);

  resetEncoder();
  delay(5);

  // quay nhanh
  motores(speed,speed*0.25);

  // hãm sớm 1 chút
  while (abs(countA) < counts_90 /2) {}

  motores(80,80*0.25);   // ⭐ speed MIN motor chạy được

  while (abs(countA) < counts_90) {}
  display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("TURN RIGHT");

    display.setCursor(0, 12);
    display.print("Pulse: ");
    display.print(abs(countA));

    display.display();
  motoresStop();
  delay(30);
  resetEncoder();
}


#endif
