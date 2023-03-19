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

const byte NONE = 0;
const byte LEFT = 1;
const byte UP = 2;
const byte RIGHT = 3;
const byte DOWN = 4;
const byte PLAY = 5;
bool menu;
byte key;

void setup(void) {
  u8g2.begin();
  Serial.begin(BAUDRATE);
  randomSeed(analogRead(RANDOMSEEDPIN));
  pinMode(KEYBOARDPIN, INPUT_PULLUP);

  menu = true;
  key = NONE;
}

void loop(void) {
  if (menu) {
    displayTitle();
  } else {
    u8g2.clearBuffer();
    displayStop();
    u8g2.sendBuffer();
  }

  key = getKey();
  
  if (key == LEFT) {
    Serial.println("LEFT");
  }
  if (key == RIGHT) {
    Serial.println("RIGHT");
  }
  if (key == UP) {
    Serial.println("UP");
  }
  if (key == DOWN) {
    Serial.println("DOWN");
  }
  if (key == PLAY) {
    Serial.println("PLAY");
    menu = !menu;
  }

  delay(100);
}

byte getKey() {
  int val = 0;
  byte button = 0;
  val = analogRead(KEYBOARDPIN);

  button = NONE;

  if (val <= 35) {
    button = LEFT;
  } else if ((val >= 40) && (val <= 90)) {
    button = UP;
  } else if ((val >= 100) && (val <= 140)) {
    button = DOWN;
  } else if ((val >= 170) && (val <= 250)) {
    button = RIGHT;
  } else if ((val >= 290) && (val <= 500)) {
    button = PLAY;
  }

  return button;
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
