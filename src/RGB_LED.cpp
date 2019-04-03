#include "RGB_LED.h"

RGB_LED::RGB_LED(unsigned int redPin, unsigned int greenPin,
                 unsigned int bluePin, COLOR color) {
  _LEDS[RED].setPin(redPin);
  _LEDS[RED].setIntensity(color.R);
  _LEDS[GREEN].setPin(greenPin);
  _LEDS[GREEN].setIntensity(color.G);
  _LEDS[BLUE].setPin(bluePin);
  _LEDS[BLUE].setIntensity(color.B);
  update();
}

void RGB_LED::setPins(unsigned int redPin, unsigned int greenPin,
                      unsigned int bluePin) {
  _LEDS[RED].setPin(redPin);
  _LEDS[GREEN].setPin(greenPin);
  _LEDS[BLUE].setPin(bluePin);
  update();
}

void RGB_LED::setPin(LED_ID led, unsigned int pin) {
  _LEDS[led].setPin(pin);
  update();
}

unsigned int RGB_LED::getPin(LED_ID led) { return _LEDS[led].getPin(); }

void RGB_LED::setColor(COLOR color) {
  _LEDS[RED].setIntensity(color.R);
  _LEDS[GREEN].setIntensity(color.G);
  _LEDS[BLUE].setIntensity(color.B);
  update();
}

const COLOR &RGB_LED::getColor() const { return _color; }

void RGB_LED::setBlink(LED_ID led, double interval) {
  _LEDS[led].setBlink(interval);
}

void RGB_LED::setFlicker(LED_ID led, double interval) {
  _LEDS[led].setFlicker(interval);
}

void RGB_LED::setTransition(LED_ID led, unsigned int setIntensity,
                            double interval, unsigned int ticks) {
  _LEDS[led].setTransition(setIntensity, interval, ticks);
}

void RGB_LED::setPulse(LED_ID led, double interval) {
  _LEDS[led].setPulse(interval);
}

void RGB_LED::setColorTransition(COLOR color, double redInterval,
                                 double greenInterval, double blueInterval,
                                 unsigned int ticks) {
  _LEDS[RED].setTransition(color.R, redInterval, ticks);
  _LEDS[GREEN].setTransition(color.G, greenInterval, ticks);
  _LEDS[BLUE].setTransition(color.B, blueInterval, ticks);
}

void RGB_LED::update() {
  _LEDS[RED].update();
  _LEDS[GREEN].update();
  _LEDS[BLUE].update();
}
