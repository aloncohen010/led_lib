#include "RGB_LED.h"
RGB_LED rgb_led(8, 9, 10, COLOR(0, 0, 0));
int func = 0;

void setup() {
  pinMode(8, OUTPUT);
}

void loop() {
  if ((millis() / 1000) % 60 == 0) {
    switch (func) {
      case 0:
        rgb_led.setColorTransition(COLOR(255, 255, 0), 0.0025, 0.0025, 0.0025);
        break;
      case 1:
        rgb_led.setColorTransition(COLOR(255, 0, 255), 0.0025, 0.0025, 0.0025);
        break;
      case 2:
        rgb_led.setColorTransition(COLOR(0, 255, 255), 0.0025, 0.0025, 0.0025);
        break;
      case 3:
        rgb_led.setColorTransition(COLOR(128, 0, 255), 0.0025, 0.0025, 0.0025);
        break;
    }
    func = func > 3 ? 0 : func + 1;
  }
  rgb_led.update();
}
