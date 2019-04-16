#include "RGB_LED.h"

RGB_LED::RGB_LED(unsigned int redPin, unsigned int greenPin,
                 unsigned int bluePin, COLOR color, LED::PIN_STATE pinState) {
  _color = color;
  _LEDS[RED].setPin(redPin, pinState);
  _LEDS[RED].setIntensity(color.R);
  _LEDS[GREEN].setPin(greenPin, pinState);
  _LEDS[GREEN].setIntensity(color.G);
  _LEDS[BLUE].setPin(bluePin, pinState);
  _LEDS[BLUE].setIntensity(color.B);
}

void RGB_LED::setPins(unsigned int redPin, unsigned int greenPin,
                      unsigned int bluePin, LED::PIN_STATE pinState) {
  _LEDS[RED].setPin(redPin, pinState);
  _LEDS[GREEN].setPin(greenPin, pinState);
  _LEDS[BLUE].setPin(bluePin, pinState);
}

void RGB_LED::setPin(LED_ID led, unsigned int pin, LED::PIN_STATE pinState) {
  _LEDS[led].setPin(pin, pinState);
}

unsigned int RGB_LED::getPin(LED_ID led) { return _LEDS[led].getPin(); }

void RGB_LED::setColor(COLOR color) {
  _color = color;
  _LEDS[RED].setIntensity(color.R);
  _LEDS[GREEN].setIntensity(color.G);
  _LEDS[BLUE].setIntensity(color.B);
}

void RGB_LED::setColor(unsigned int redValue, unsigned int greenValue,
                       unsigned int blueValue) {
  setColor(COLOR(redValue, greenValue, blueValue));
}

const COLOR &RGB_LED::getColor() const { return _color; }

void RGB_LED::setOn() {
  _LEDS[RED].setOn();
  _LEDS[GREEN].setOn();
  _LEDS[BLUE].setOn();
}

void RGB_LED::setOff() {
  _LEDS[RED].setOff();
  _LEDS[GREEN].setOff();
  _LEDS[BLUE].setOff();
}

void RGB_LED::setBlink(LED_ID led, double interval) {
  _LEDS[led].setBlink(interval);
}

void RGB_LED::setFlicker(LED_ID led, double interval) {
  _LEDS[led].setFlicker(interval);
}

void RGB_LED::setTransition(LED_ID led, unsigned int setIntensity,
                            double interval) {
  _LEDS[led].setTransition(setIntensity, interval);
}

void RGB_LED::setPulse(LED_ID led, double interval) {
  _LEDS[led].setPulse(interval);
}

void RGB_LED::setColorTransition(COLOR color, double redInterval,
                                 double greenInterval, double blueInterval) {
  _LEDS[RED].setTransition(color.R, redInterval);
  _LEDS[GREEN].setTransition(color.G, greenInterval);
  _LEDS[BLUE].setTransition(color.B, blueInterval);
}

void RGB_LED::update() {
  _LEDS[RED].update();
  _LEDS[GREEN].update();
  _LEDS[BLUE].update();
}
