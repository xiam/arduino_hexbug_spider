// Grab this libray from https://github.com/xiam/arduino_irdump
#include <IRDump.h>

#ifndef HEXBUG_FULL_ROTATION
// How many times does a rotation code needs to be send to complete a full
// turn? This number was made up based on experimentation.
#define HEXBUG_FULL_ROTATION 18
#endif

#ifndef HEXBUG_DELAY_AFTER_INSTRUCTION
// The number of milliseconds to wait after sending an instruction. This number
// was also made up based on experimentation.
#define HEXBUG_DELAY_AFTER_INSTRUCTION 192
#endif

#define HEXBUG_SPIDER_LEAD          1800, 450
#define HEXBUG_SPIDER_CONTROL_CODE  1800, 900
#define HEXBUG_SPIDER_B0            350,  550
#define HEXBUG_SPIDER_B1            350, 1450
#define HEXBUG_SPIDER_STOP          350, 0

#define HEXBUG_SPIDER_H0    HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0
#define HEXBUG_SPIDER_H1    HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0
#define HEXBUG_SPIDER_H2    HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0
#define HEXBUG_SPIDER_H3    HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0
#define HEXBUG_SPIDER_H4    HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0
#define HEXBUG_SPIDER_H5    HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0
#define HEXBUG_SPIDER_H6    HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0
#define HEXBUG_SPIDER_H7    HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0
#define HEXBUG_SPIDER_H8    HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1
#define HEXBUG_SPIDER_H9    HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1
#define HEXBUG_SPIDER_HA    HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1
#define HEXBUG_SPIDER_HB    HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1
#define HEXBUG_SPIDER_HC    HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1
#define HEXBUG_SPIDER_HD    HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1
#define HEXBUG_SPIDER_HE    HEXBUG_SPIDER_B0, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1
#define HEXBUG_SPIDER_HF    HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1

#ifndef HEXBUG_SPIDER_CHANNEL
#define HEXBUG_SPIDER_CHANNEL 'A'
#endif

#if HEXBUG_SPIDER_CHANNEL == 'A'
  #define HEXBUG_SPIDER_CONTROLLER_ID      HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B1

  #define BUTTON_RIGHT      HEXBUG_SPIDER_H4, HEXBUG_SPIDER_H6
  #define BUTTON_LEFT       HEXBUG_SPIDER_H3, HEXBUG_SPIDER_H8
  #define BUTTON_FORWARD    HEXBUG_SPIDER_H1, HEXBUG_SPIDER_HC
  #define BUTTON_BACKWARD   HEXBUG_SPIDER_H2, HEXBUG_SPIDER_HA
#else
  #define HEXBUG_SPIDER_CONTROLLER_ID      HEXBUG_SPIDER_B1, HEXBUG_SPIDER_B0

  #define BUTTON_RIGHT      HEXBUG_SPIDER_H4, HEXBUG_SPIDER_H7
  #define BUTTON_LEFT       HEXBUG_SPIDER_H3, HEXBUG_SPIDER_H9
  #define BUTTON_FORWARD    HEXBUG_SPIDER_H1, HEXBUG_SPIDER_HD
  #define BUTTON_BACKWARD   HEXBUG_SPIDER_H2, HEXBUG_SPIDER_HB
#endif

#define HEXBUG_SPIDER_RIGHT      0
#define HEXBUG_SPIDER_LEFT       1
#define HEXBUG_SPIDER_FORWARD    2
#define HEXBUG_SPIDER_BACKWARD   3

#define HEXBUG_SPIDER_SIGNALS (HEXBUG_SPIDER_BACKWARD + 1)

#define HEXBUG_SPIDER_KHZ    38

#define HEXBUG_SPIDER_SIGNAL(code) { HEXBUG_SPIDER_LEAD, HEXBUG_SPIDER_CONTROL_CODE, code, HEXBUG_SPIDER_CONTROLLER_ID, HEXBUG_SPIDER_STOP }

unsigned int hexbug_spider_signal[HEXBUG_SPIDER_SIGNALS][26] = {
  HEXBUG_SPIDER_SIGNAL(BUTTON_RIGHT),
  HEXBUG_SPIDER_SIGNAL(BUTTON_LEFT),
  HEXBUG_SPIDER_SIGNAL(BUTTON_FORWARD),
  HEXBUG_SPIDER_SIGNAL(BUTTON_BACKWARD)
};

IRDump *hexbug_spider_irdump;
int hexbug_spider_pin;

// hexbug_spider_send emits an IR signal.
void hexbug_spider_send(int code) {
  hexbug_spider_irdump->Emit(hexbug_spider_pin, hexbug_spider_signal[code], HEXBUG_SPIDER_KHZ);
  delay(HEXBUG_DELAY_AFTER_INSTRUCTION);
}

// hexbug_spider_spin_left sends the "spin left" IR code.
void hexbug_spider_spin_left() {
  hexbug_spider_send(HEXBUG_SPIDER_LEFT);
}

// hexbug_spider_spin_right sends the "spin right" IR code.
void hexbug_spider_spin_right() {
  hexbug_spider_send(HEXBUG_SPIDER_RIGHT);
}

// hexbug_spider_forward sends the "go forward" IR code.
void hexbug_spider_forward() {
  hexbug_spider_send(HEXBUG_SPIDER_FORWARD);
}

// hexbug_spider_backward sends the "go backward" IR code.
void hexbug_spider_backward() {
  hexbug_spider_send(HEXBUG_SPIDER_BACKWARD);
}

// hexbug_spider_advance goes forward if times > 0 or backward if times < 0.
// times is the number of times the code is going to be send.
void hexbug_spider_advance(int times) {
  int i;
  for (i = abs(times); i > 0; i--) {
    if (times < 0) {
      hexbug_spider_backward();
    } else {
      hexbug_spider_forward();
    }
  }
}

// hexbug_spider_spin sends rotation instructions by the number of degrees
// given, if deg is > 0, this is a clockwise rotation, if deg < 0, this is a
// counter-clockwise rotation.
void hexbug_spider_spin(int deg) {
  int times, i;
  times = int(float(HEXBUG_FULL_ROTATION)*float(float(abs(deg)) / 360.0f));

  for (i = 0; i < times; i++) {
    if (deg < 0) {
      hexbug_spider_spin_left();
    } else {
      hexbug_spider_spin_right();
    }
 };
}


void hexbug_spider_setup_pin(int pin) {
  hexbug_spider_irdump = new IRDump();
  hexbug_spider_pin = pin;

  pinMode(hexbug_spider_pin, OUTPUT);
}
