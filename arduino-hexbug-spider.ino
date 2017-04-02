// https://github.com/xiam/arduino_irdump
#include <IRDump.h> 

#define HEXBUG_SPIDER_CHANNEL 'A' // Either A or B

// How many times does a rotation code needs to be send to complete
// a full turn? This number was made up based on experimentation.
#define HEXBUG_FULL_ROTATION 18

// The number of milliseconds to wait after sending an instruction. This
// number was also made up based on experimentation.
#define HEXBUG_DELAY_AFTER_INSTRUCTION 192

#include "hexbug-spider.h"

// Must be a PWN pin.
#define PIN_IR_OUTPUT    3

IRDump *irdumper;

// hexbug_spider_send emits an IR signal.
void hexbug_spider_send(int code) {
  irdumper->Emit(PIN_IR_OUTPUT, hexbug_spider_signal[code], HEXBUG_SPIDER_KHZ);
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

// hexbug_spider_advance goes forward if times > 0 or backward if times < 0. times is the
// number of times the code is going to be send.
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

// hexbug_spider_spin sends rotation instructions by the number of degrees given,
// if deg is > 0, this is a clockwise rotation, if deg < 0, this is a counter-clockwise
// rotation.
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

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Make sure your HexBug spider is within the IR LED's range.");
  
  irdumper = new IRDump();
  pinMode(PIN_IR_OUTPUT, OUTPUT);
}

void loop(void) {
  // go forward 30 times.
  hexbug_spider_advance(30);

  // rotate ~-90deg (90deg ccw).
  hexbug_spider_spin(-90);
  
  // go backward 10 times.
  hexbug_spider_advance(-10);

  // rotate ~120deg (120deg cw).
  hexbug_spider_spin(360/3);
}
