#include <AppleRemote.h>

#include <hexbug_spider.h>

#define SIGNAL_MAX_LENGTH 70

#define PIN_IR_INPUT      2
#define PIN_IR_OUTPUT     3

int last_code = 0;

unsigned int signal[SIGNAL_MAX_LENGTH];

IRDump *irdumper;
AppleRemote *appleRemote;

void setup()
{
  Serial.begin(115200);
  Serial.println("Apple Remote for Arduino.");

  appleRemote = new AppleRemote(PIN_IR_OUTPUT, APPLE_REMOTE_MODEL_A);
  irdumper = new IRDump();
}

void receive_signals() {
  unsigned int *s = signal;

  bool captured;
  int code;

  code = 0;

  captured = irdumper->Capture(PIN_IR_INPUT, s, SIGNAL_MAX_LENGTH, 9500);

  if (captured) {
    code = appleRemote->Match(s);

    switch (code) {
      case APPLE_REMOTE_RIGHT:
        Serial.println("[right]");
        break;
      case APPLE_REMOTE_LEFT:
        Serial.println("[left]");
        break;
      case APPLE_REMOTE_UP:
        Serial.println("[up]");
        break;
      case APPLE_REMOTE_DOWN:
        Serial.println("[down]");
        break;
      case APPLE_REMOTE_REPEAT:
        Serial.println("[repeat]");
        code = last_code;
        break;
      default:
        Serial.println("[?]");
        code = 0;
        return;
    }

    if (code > 0) {

      int i;

      for (i = 0; i < 5; i++) {
        switch (code) {
          case APPLE_REMOTE_RIGHT:
            hexbug_spider_right();
            break;
          case APPLE_REMOTE_LEFT:
            hexbug_spider_left();
            break;
          case APPLE_REMOTE_UP:
            hexbug_spider_forward();
            break;
          case APPLE_REMOTE_DOWN:
            hexbug_spider_backward();
            break;
          default:
            return;
        }
        delay(50);
      }

      last_code = code;
    }
  }
}


void loop() {
  receive_signals();
}
