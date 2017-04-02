# Hexbug spider library for Arduino

![Hexbug Spider](https://content.hexbug.com/images/animation/spider.gif)

This library uses an IR LED to send codes that can be understood by an
[Hexbug Spider][1].

## Wiring everything together

To build this project you'll need:

1. And Arduino board.
1. An IR LED.
1. A red LED (optional).
1. A 200 to 1000 ohm resistor.

Wire one of the PWN pins of the Arduino board (this example uses pin 3) to the
largest leg of the IR LED, the second leg goes to the longest leg of the red
LED via the resistor, the second leg of the red LED goes to ground.

Should look like this:

![arduino hexbug spider_bb](https://cloud.githubusercontent.com/assets/385670/24587747/cbaa2880-1781-11e7-9a43-ff5c65d30013.png)

Here's an schematic view of the same setup:

![arduino hexbug spider_schem](https://cloud.githubusercontent.com/assets/385670/24587746/cba7d21a-1781-11e7-859e-9ca46ed546c1.png)

## Minimal code example

1. Install the [IRDump.h][2] library.
1. Include the `hexbug_spider.h` file into your main Arduino code, for instance
   `#include <hexbug_spider.h>`.

```c
// Channel the Hexbug Spider is listenning to ('A' or 'B'), must be defined
// before including hexbug-spider.h.
#define HEXBUG_SPIDER_CHANNEL 'A'

#include <hexbug_spider.h>

// Pin the IR LED is wired to. Must be a PWM pin.
#define PIN_IR_OUTPUT    3

void setup()
{
  Serial.begin(9600);
  Serial.println("Point your IR LED to an Hexbug spider.");

  hexbug_spider_setup_pin(PIN_IR_OUTPUT);
}

void loop()
{
  hexbug_spider_left();
  delay(100);
}
```

Here's a [full example](https://github.com/xiam/arduino_hexbug_spider/tree/master/examples/hexbug).


## License

> Copyright (c) 2014-today José Carlos Nieto, https://menteslibres.net/xiam
>
> Permission is hereby granted, free of charge, to any person obtaining
> a copy of this software and associated documentation files (the
> "Software"), to deal in the Software without restriction, including
> without limitation the rights to use, copy, modify, merge, publish,
> distribute, sublicense, and/or sell copies of the Software, and to
> permit persons to whom the Software is furnished to do so, subject to
> the following conditions:
>
> The above copyright notice and this permission notice shall be
> included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
> EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
> MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
> NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
> LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
> OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
> WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

[1]: https://www.hexbug.com/mechanical/spider/
[2]: https://github.com/xiam/arduino_irdump
