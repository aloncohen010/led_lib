#include "LED.h"
LED led(11, 0);
int func = 0;

void setup() {}

void loop() {
  delay(1000 * 10);
  switch (func) {
  case 0:
    led.setBlink(1000);
    func++;
    break;
  case 1:
    led.setFlicker(20);
    func++;
    break;
  case 2:
    led.setTransition(255, 20);
    func++;
    break;
  case 3:
    led.setPulse(0.0008);
    func++;
    break;
  }
  func = func > 3 ? 0 : func + 1;
}
led.update();
}
