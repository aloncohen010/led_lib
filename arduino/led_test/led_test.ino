#include "LED.h"
LED led(8, 0);
int func = 0;

void setup() {
  pinMode(8, OUTPUT);
}

void loop() {
  if ((millis() / 1000) % 60 == 0) {
    switch (func) {
      case 0:
        led.setBlink(500);
        break;
      case 1:
        led.setFlicker(250);
        break;
      case 2:
        led.setIntensity(0);
        led.setTransition(255, 200);
        break;
      case 3:
        led.setPulse(0.0025);
        break;
    }
    func = func > 3 ? 0 : func + 1;
  }
  led.update();
}
