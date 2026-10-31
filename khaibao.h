#ifndef khaibao
#define khaibao

HardwareSerial Serial3(PB11, PB10); // RX, TX
#define BT   Serial3
#define HC06 BT

#define PWMA PA10
#define AIN1 PA8
#define AIN2 PB15
#define STBY PB14
#define BIN1 PB12
#define BIN2 PB13
#define PWMB PA9

// LEFT encoder
#define ENCA_A PA0
#define ENCA_B PA1

// RIGHT encoder (tránh 21/22)
#define ENCB_A PB6
#define ENCB_B PB7

#define S1 PA6
#define S2 PB1
#define S3 PA5
#define S4 PB0
#define S5 PA4
#define S6 PA7
#define S7 PA3
#define S8 PA2
#define OK PA12  // nút bấm
#define MODE PA15  // nút bấm
#define XshutF PB4
// ================= LINE STATE =================
#define BAMLINE 0
#define LEFT   1
#define RIGHT  2
#define BLACK  3
#define MATLINE   4
//--- KHAI BÁO BIẾN CẢM BIẾN -------------------
const uint8_t num=8;
uint16_t sensorValue[num];     // giá trị analog đọc được
uint16_t S[num];    // giá trị 0/1 sau khi so sánh
uint16_t ValueMax[num];
uint16_t ValueMin[num];
uint16_t threshold[num]; 
const uint8_t sensorPin[num] = {S1,S2,S3,S4,S5,S6,S7,S8};
int weightValue[num] = {-20,-15,-10,-5,5,10,15,20}; // trọng số giãn cách
int sumSensor;
int sumWeight;
uint8_t mode = 0;
bool calibrated = false;
float error, previous_error;
float currPos;
float cenPos = 0;   // trung tâm
float cenPos2 = 30;   // trung tâm
float ePrev = 0;
float eCurr;  
float u;
float dE;
float eSum = 0;
float Ki =0 ;
float Kp = 5;
float Kd = 20;
float Kp2 = 4;
float Kd2 = 30;
float integral = 0;
int baseSpeed = 70;   // tốc độ cơ bản
int speed ;
int speedmax=255;
int upspeed=20;
int lastTurn = 0;  // -1 = trái, 0 = thẳng, 1 = phải
int step = 0;

// ================= TIMER =================
unsigned long lostTime = 0;
unsigned long turnTime = 0;
uint8_t prevState = BAMLINE;

unsigned long startTime = 0;
bool startDone = false;
#define LINETIME      100    // ms
#define EEPROM_MAGIC 0xA5
#define KHOANGCACH   25    // cm – khoảng cách phát hiện vật cản
static unsigned long lastToF = 0;
uint8_t avoidStep = 0;      // 0 = idle
unsigned long avoidTime = 0;
int avoidDir = 1;           // 1 = né phải, -1 = né trái
#define STOP_TIME     200
#define TURN45_TIME   250
#define GO_SHORT      500
#define GO_LONG       800
#define TURN_SPEED    50
#define GO_SPEED      50
volatile uint32_t avoidCount = 0;
unsigned long runStartTime = 0;
int dem =1;
#endif