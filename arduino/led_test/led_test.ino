#include "LED.h"
LED led(11, 0);
int func = 0;

void setup() {
}

void loop() {
  if ((millis() / 1000) % 10 == 0) {
    switch (func) {
      case 0:
        led.setBlink(1000);
        break;
      case 1:
        led.setFlicker(20);
        break;
      case 2:
        led.setTransition(255, 20);
        break;
      case 3:
        led.setPulse(0.0025);
        break;
    }
    func = func > 3 ? 0 : func + 1;
  }
  led.update();
}
