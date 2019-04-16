#include "RGB_LED.h"

RGB_LED* x;

void setup() {
  Serial.begin(9600);
  Serial.println("setup complete...");
  x = new RGB_LED(11, 10, 9, COLOR(255, 0, 255), LOW);
}

void loop() {
}
