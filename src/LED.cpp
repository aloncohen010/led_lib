#include "LED.h"

#ifdef ARDUINO
#include <arduino.h>
#include <math.h>
const int PWM_BITS = 8;
const int MAX_INTENSITY = pow(2, PWM_BITS) - 1;
void writeToPin(int pin, int value) { analogWrite(pin, value); }
unsigned long getElapsedTime() { return millis(); }
long randomNumber() { return random(0, MAX_INTENSITY); }
void init(int pin) { pinMode(pin, OUTPUT); }
#endif

#ifdef STM32
#include <math.h>
#include <stm32fxxx_hal.h>
const int PWM_BITS = 16;
const int MAX_INTENSITY = pow(2, PWM_BITS) - 1;
void writeToPin(int pin, int value) {
  // find stm32 equivilant of analogWrite
}
unsigned long getElapsedTime() { return HAL_GetTick(); }
long randomNumber(){return TM_RNG_Get()};
void init(int pin) {
  // find stm32 equivilant of pinMode
}
#endif

LED::LED(int pin, int intensity)
    : _pin(pin), _intensity(intensity), _pulseInput(1.5 * M_PI) {
  init(_pin);
}

void LED::setPin(int pin) {
  _pin = pin > 0 ? pin : 0;
  writeToPin(_pin, _intensity);
}

int LED::getPin() const { return _pin; }

void LED::setIntensity(int intensity) {
  _intensity = abs(intensity) < MAX_INTENSITY ? abs(intensity) : MAX_INTENSITY;
  _intensity = (intensity >= 0 && intensity <= MAX_INTENSITY) ? intensity : 0;
  writeToPin(_pin, _intensity);
}

int LED::getIntensity() const { return _intensity; }

void LED::setBlink(int speed) {
  _step = abs(speed);
  _runningFunction = 1;
}

void LED::setFlicker(int step) {
  _step = abs(step);
  _runningFunction = 2;
}

void LED::setTransition(int setIntensity, int step) {
  _setIntensity =
      abs(setIntensity) < MAX_INTENSITY ? abs(setIntensity) : MAX_INTENSITY;
  _step = abs(step);
  _runningFunction = 3;
}

void LED::setPulse(float step) {
  _pulseSpeed = fabs(step);
  _runningFunction = 4;
}

void LED::blink() {
  if ((_elapsedTime + _step) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    if (_intensity == 0) {
      setIntensity(MAX_INTENSITY);
    } else {
      setIntensity(0);
    }
  }
}

void LED::flicker() {
  if ((_elapsedTime + _step) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    setIntensity((randomNumber() % MAX_INTENSITY + _step));
  }
}

void LED::transition() {
  if ((_elapsedTime + _step) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    if (_setIntensity > _intensity) {
      _intensity = (_setIntensity - (_intensity + _step)) < 0
                       ? _setIntensity
                       : (_intensity + _step);
    } else if (_setIntensity < _intensity) {
      _intensity = _intensity - _step;
      _intensity = (_setIntensity - (_intensity - _step)) > 0
                       ? _setIntensity
                       : (_intensity - _step);
    }
    _intensity = setIntensity(_intensity);
  }
}

void LED::pulse() {
  _intensity = static_cast<int>(sin(_pulseInput) *
                                    (static_cast<int>(MAX_INTENSITY) / 2) +
                                (static_cast<int>(MAX_INTENSITY) / 2));
  setIntensity(_intensity);
  _pulseInput = _pulseInput + _pulseSpeed;
}

void LED::update() {
  switch (_runningFunction) {
  case 0:
    break;
  case 1:
    blink();
    break;
  case 2:
    flicker();
    break;
  case 3:
    transition();
    break;
  case 4:
    pulse();
    break;
  }
}
