#include <hexbug-spider.h>

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Point the IR LED to your Hexbug Spider.");
}

void example_hexbug_spider_lookout() {
  int i;

  for (i = 0; i < 5; i++) {
    hexbug_spider_left();
    delay(100);
  };

  for (i = 0; i < 5; i++) {
    hexbug_spider_right();
    delay(100);
  }
}

void loop(void) {
  example_hexbug_spider_lookout();
}
