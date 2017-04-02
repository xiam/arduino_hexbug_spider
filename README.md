# Hexbug spider library for Arduino

This library uses an IR LED to send codes that can be understood by an
[Hexbug Spider][1].

The IR LED is expected to be wired to your Arduino's pin #3.

## Minimal code example

```c
// Channel the Hexbug Spider is listenning to ('A' or 'B'), must be defined
// before including hexbug-spider.h. 
#define HEXBUG_SPIDER_CHANNEL 'A'

#include "hexbug_spider.h"

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

## How to install

1. Install the [IRDump.h][2] library.
3. Include the `hexbug_spider.h` file into your main Arduino code, for instance
   `#include "hexbug_spider.h"`.

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
