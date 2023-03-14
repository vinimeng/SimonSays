#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
int Keyboard = A0;

void setup(void) {
  u8g2.begin();
  Serial.begin(9600);
}

void loop(void) {
  Serial.println(analogRead(Keyboard));

  u8g2.clearBuffer();                     // clear the internal memory
  u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2.drawStr(8, 29, "MENG");         // write something to the internal memory
  u8g2.sendBuffer();                      // transfer internal memory to the display
}
