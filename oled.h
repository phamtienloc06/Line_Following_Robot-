#ifndef oled
#define oled

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1   // không dùng reset
#define OLED_ADDR     0x3C // địa chỉ phổ biến

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static inline void setupOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED init FAIL");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);      // 128x32 chỉ nên dùng size 1
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("OLED READY");
  display.display();
}
static inline void showLRCountOLED(uint8_t r) {
  static unsigned long last = 0;
  if (millis() - last < 80) return;   // chống spam OLED
  last = millis();

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("RCount: ");
  display.print(r);

  display.display();
}

#endif