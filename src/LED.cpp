#include "LED.h"

#ifdef X86
#include <cmath>
using namespace std;
const int PWM_BITS = 8;
const int MAX_INTENSITY = pow(2, PWM_BITS);
void writeToPin(int pin, int value) {}
unsigned long getElapsedTime() { return 10; }
long randomNumber() { return 10; };
#endif

#ifdef ARDUINO
#include <arduino.h>
#include <math.h>
const int PWM_BITS = 8;
const int MAX_INTENSITY = pow(2, PWM_BITS);
void writeToPin(int pin, int value) { analogWrite(pin, value); }
unsigned long getElapsedTime() { return millis(); }
long randomNumber() { return random(0, MAX_INTENSITY); }
#endif

#ifdef STM32
#include <math.h>
#include <stm32fxxx_hal.h>
const int PWM_BITS = 16;
const int MAX_INTENSITY = pow(2, PWM_BITS);
void writeToPin(int pin, int value) {
  // find stm32 equivilant of analogWrite
}
unsigned long getElapsedTime() { return HAL_GetTick(); }
long randomNumber(){return TM_RNG_Get()};
#endif

LED::LED(int pin, int intensity)
    : _pin(pin), _intensity(intensity), _elapsedTime(0), _speed(0),
      _setIntensity(0), _pulsespeed(0), _pulseInput(0) {}

void LED::setPin(int pin) {
  _pin = pin > 0 ? pin : 0;
  writeToPin(_pin, _intensity);
}

int LED::getPin() const { return _pin; }

void LED::setIntensity(int intensity) {
  _intensity = (intensity > 0 && intensity < MAX_INTENSITY) ? intensity : 0;
  writeToPin(_pin, _intensity);
}

int LED::getIntensity() const { return _intensity; }

void LED::setBlink(int speed) {
  _speed = speed;
  _runningFunction = 1;
}

void LED::setFlicker(int speed) {
  _speed = speed;
  _runningFunction = 2;
}

void LED::setTransition(int setIntensity, int speed) {
  _setIntensity = setIntensity;
  _speed = speed;
  _runningFunction = 3;
}

void LED::setPulse(float speed) {
  _pulsespeed = speed;
  _pulseInput = 1.5 * M_PI; // setting initial _pulseInput so pulse starts at 0
  _runningFunction = 4;
}

void LED::blink() {
  if ((_elapsedTime + _speed) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    if (_intensity == 0) {
      _intensity = MAX_INTENSITY;
      writeToPin(_pin, _intensity);
    } else {
      _intensity = 0;
      writeToPin(_pin, _intensity);
    }
  }
}

void LED::flicker() {
  if ((_elapsedTime + _speed) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    _intensity = (randomNumber() % MAX_INTENSITY + _speed);
    writeToPin(_pin, _intensity);
  }
}

void LED::transition() {
  if ((_elapsedTime + _speed) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    if (_intensity < _setIntensity && _intensity > 0) {
      _intensity += _speed;
    } else if (_intensity > _setIntensity && _intensity < MAX_INTENSITY) {
      _intensity -= _speed;
    }
    writeToPin(_pin, _intensity);
  }
}

void LED::pulse() {
  _intensity = static_cast<int>(sin(_pulseInput) * (MAX_INTENSITY / 2) +
                                MAX_INTENSITY / 2);
  writeToPin(_pin, _intensity);
  _pulseInput = _pulseInput + _speed;
  if (_pulseInput == 2 * M_PI) {
    _pulseInput = 0;
  }
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
