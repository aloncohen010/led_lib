#include "RGB_LED.h"

RGB_LED rgb_led(11, 10, 9, COLOR(0, 0, 0));
int func = 0;

void setup() { pinMode(8, OUTPUT); }

void loop() {
  delay(1000 * 10);
  switch (func) {
  case 0:
    rgb_led.setColorTransition(COLOR(255, 255, 0), 20, 20, 20);
    func++;
    break;
  case 1:
    rgb_led.setColorTransition(COLOR(255, 0, 255), 20, 20, 20);
    func++;
    break;
  case 2:
    rgb_led.setColorTransition(COLOR(0, 255, 255), 20, 20, 20);
    func++;
    break;
  case 3:
    rgb_led.setColorTransition(COLOR(128, 0, 255), 20, 20, 20);
    func++;
    break;
  }
  func = func > 3 ? 0 : func + 1;
}
rgb_led.update();
}
