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
#define PLAYBTN 84
#define UPBTN 87
#define DOWNBTN 83
#define LEFTBTN 65
#define RIGHTBTN 68

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
bool menu;
int keysToPress[15];
int keyPressed;
int previousKey;
String key;

void setup(void) {
  u8g2.begin();
  Serial.begin(BAUDRATE);
  //randomSeed(analogRead(RANDOMSEEDPIN));
  previousKey = 1023;
  menu = true;
}

void loop(void) {
  if (menu) {
    displayTitle();
  } else {
    u8g2.clearBuffer();
    displayStop();
    u8g2.sendBuffer();
  }

  keyPressed = analogRead(KEYBOARDPIN);
  Serial.println(keyPressed);
  
  if (keyPressed <= 10) { // Botão esquerdo
    key = "ESQUERDO";
  } else if (keyPressed >= 25 && keyPressed <= 35) { // Botão cima
    key = "CIMA";
  } else if (keyPressed >= 80 && keyPressed <= 90) { // Botão baixo
    key = "BAIXO";
  } else if (keyPressed >= 160 && keyPressed <= 170) { // Botão direito
    key = "DIREITO";
  } else if (keyPressed >= 345 && keyPressed <= 355) { // Botão play
    key = "PLAY";
  }

  if (keyPressed != previousKey && keyPressed < 1000) {
    Serial.println(key);
    previousKey = keyPressed;
  }
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
