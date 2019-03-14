#include "RGB_LED.h"

RGB_LED::RGB_LED(int pin_red, int pin_green, int pin_blue, COLOR color) {
  _LEDS[RED].setPin(pin_red);
  _LEDS[RED].setIntensity(color.R);
  _LEDS[GREEN].setPin(pin_green);
  _LEDS[GREEN].setIntensity(color.G);
  _LEDS[BLUE].setPin(pin_blue);
  _LEDS[BLUE].setIntensity(color.B);
  update();
}

void RGB_LED::setPins(int pin_red, int pin_green, int pin_blue) {
  _LEDS[RED].setPin(pin_red);
  _LEDS[GREEN].setPin(pin_green);
  _LEDS[BLUE].setPin(pin_blue);
  update();
}

void RGB_LED::setPin(LED_COLOR led, int pin) {
  _LEDS[led].setPin(pin);
  update();
}

int RGB_LED::getPin(LED_COLOR led) { return _LEDS[led].getPin(); }

void RGB_LED::setColor(COLOR color) {
  _LEDS[RED].setIntensity(color.R);
  _LEDS[GREEN].setIntensity(color.G);
  _LEDS[BLUE].setIntensity(color.B);
  update();
}

const COLOR &RGB_LED::getColor() const { return _color; }

void RGB_LED::setBlink(LED_COLOR led, int speed) { _LEDS[led].setBlink(speed); }

void RGB_LED::setFlicker(LED_COLOR led, int speed) {
  _LEDS[led].setFlicker(speed);
}

void RGB_LED::setTransition(LED_COLOR led, int setIntensity, int speed) {
  _LEDS[led].setTransition(setIntensity, speed);
}

void RGB_LED::setPulse(LED_COLOR led, float speed) {
  _LEDS[led].setPulse(speed);
}

void RGB_LED::setColorTransition(COLOR color, int redStep, int greenStep,
                                 int blueStep) {
  _LEDS[RED].setTransition(color.R, redStep);
  _LEDS[GREEN].setTransition(color.G, greenStep);
  _LEDS[BLUE].setTransition(color.B, blueStep);
}

void RGB_LED::update() {
  _LEDS[RED].update();
  _LEDS[GREEN].update();
  _LEDS[BLUE].update();
}
