// Channel the Hexbug Spider is listenning to ('A' or 'B').
#define HEXBUG_SPIDER_CHANNEL 'A'
// How many times does a rotation code needs to be send to complete a full
// turn? This number was made up based on experimentation.
#define HEXBUG_FULL_ROTATION 18
// The number of milliseconds to wait after sending an instruction. This number
// was also made up based on experimentation.
#define HEXBUG_DELAY_AFTER_INSTRUCTION 192
// IR codes and utilities for Hexbug Spider.
#include <hexbug_spider.h>

// Pin the IR LED is wired to. Must be a PWM pin.
#define PIN_IR_OUTPUT    3

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Make sure your HexBug spider is within the IR LED's range.");

  hexbug_spider_setup_pin(PIN_IR_OUTPUT);
}

void loop(void) {
  // go forward 30 times.
  hexbug_spider_advance(30);

  // rotate ~-90seg (90deg ccw).
  hexbug_spider_spin(-90);

  // go backward 10 times.
  hexbug_spider_advance(-10);

  // rotate ~120deg (120deg cw).
  hexbug_spider_spin(360/3);
}
