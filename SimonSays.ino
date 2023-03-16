#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#define KEYBOARDPIN A0
#define RANDOMSEEDPIN A4
#define TITLEFONT u8g2_font_sticker_mel_tr
#define COMMANDFONT u8g2_font_t0_12b_tr
#define GLYPHFONT u8g2_font_iconquadpix_m_all
#define BAUDRATE 9600
#define PLAYBTN 0x0054
#define UPBTN 0x0057
#define DOWNBTN 0x0053
#define LEFTBTN 0x0041
#define RIGHTBTN 0x0044

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

void setup(void) {
  u8g2.begin();
  Serial.begin(BAUDRATE);
  randomSeed(analogRead(RANDOMSEEDPIN));
}

void loop(void) {
  //Serial.println(analogRead(KEYBOARDPIN));
  Serial.println(analogRead(RANDOMSEEDPIN));

  u8g2.clearBuffer();
  displayStop();
  u8g2.sendBuffer();
}

void displayTitle() {
  u8g2.clearBuffer();
  u8g2.setFont(TITLEFONT);
  u8g2.drawStr(0, 12, "MESTRE");
  u8g2.drawStr(0, 32, "MANDOU");
  u8g2.setFont(GLYPHFONT);
  u8g2.drawGlyph(102, 20, PLAYBTN);
  u8g2.setFont(COMMANDFONT);
  u8g2.drawStr(87, 32, "Iniciar");
  u8g2.sendBuffer();
}

void displayStop() {
  u8g2.setFont(GLYPHFONT);
  u8g2.drawGlyph(108, 20, PLAYBTN);
  u8g2.setFont(COMMANDFONT);
  u8g2.drawStr(99, 32, "Parar");
}
