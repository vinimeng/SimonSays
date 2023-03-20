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
bool showSequence;
bool wrong;
bool win;
byte key;
byte arrayToChoose[] = { LEFT, LEFT, RIGHT, DOWN, DOWN, UP, RIGHT, RIGHT, UP, LEFT };
byte keysToPress[10];
int sequenceUser;
int sequence;

void setup(void) {
  u8g2.begin();
  Serial.begin(BAUDRATE);
  randomSeed(analogRead(RANDOMSEEDPIN));
  pinMode(KEYBOARDPIN, INPUT_PULLUP);

  sequenceUser = 0;
  sequence = 0;
  showSequence = false;
  menu = true;
  key = NONE;
  wrong = false;
  win = false;
}

void loop(void) {
  if (menu) {
    displayTitle();
  } else {
    displaySequence();

    if (wrong || win || showSequence) {
      delay(1500);
      showSequence = false;

      if (wrong || win) {
        sequenceUser = 0;
        sequence = 0;
        wrong = false;
        win = false;
        menu = true;
      }
    }
  }

  key = getKey();

  if (key == LEFT) {
    Serial.println("LEFT");

    keyAction(keysToPress[sequenceUser] == LEFT);
  }
  if (key == RIGHT) {
    Serial.println("RIGHT");

    keyAction(keysToPress[sequenceUser] == RIGHT);
  }
  if (key == UP) {
    Serial.println("UP");

    keyAction(keysToPress[sequenceUser] == UP);
  }
  if (key == DOWN) {
    Serial.println("DOWN");

    keyAction(keysToPress[sequenceUser] == DOWN);
  }
  if (key == PLAY) {
    Serial.println("PLAY");
    menu = !menu;

    if (!menu) {
      for (int i = 0; i < 10; i++) {
        keysToPress[i] = arrayToChoose[random(10)];
      }

      sequenceUser = 0;
      sequence = 1;
      showSequence = true;
    }

    delay(150);
  }
}

void keyAction(bool wright) {
  if (wright) {
    sequenceUser++;
    if (sequenceUser == sequence) {
      sequenceUser = 0;
      sequence++;
      if (sequence > 10) {
        win = true;
      } else {
        showSequence = true;
      }
    }
  } else {
    wrong = true;
  }

  delay(150);
}

void displaySequence() {
  int limit = sequenceUser;

  if (showSequence) {
    limit = sequence;
  }

  u8g2.clearBuffer();
  u8g2.setFont(GLYPHFONT);

  if (!wrong && !win) {
    for (int i = 0; i < limit; i++) {
      int x = (i / 5) > 0 ? 18 * (i - 5) : 18 * i;
      int y = (i / 5) > 0 ? 32 : 12;
      if (keysToPress[i] == LEFT) {
        u8g2.drawGlyph(x, y, LEFTBTN);
      } else if (keysToPress[i] == UP) {
        u8g2.drawGlyph(x, y, UPBTN);
      } else if (keysToPress[i] == RIGHT) {
        u8g2.drawGlyph(x, y, RIGHTBTN);
      } else if (keysToPress[i] == DOWN) {
        u8g2.drawGlyph(x, y, DOWNBTN);
      }
    }
  }

  u8g2.drawGlyph(108, 20, PLAYBTN);
  u8g2.setFont(COMMANDFONT);
  u8g2.drawStr(99, 32, "Parar");

  if (wrong) {
    u8g2.drawStr(0, 32, "Errou!!!");
  }
  if (win) {
    u8g2.drawStr(0, 32, "Ganhou!!!");
  }

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
