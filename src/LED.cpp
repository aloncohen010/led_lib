#include "LED.h"

#if defined(X86)
using namespace std;
const unsigned int PWM_BITS = 8;
const unsigned int MAX_INTENSITY =
    static_cast<unsigned int>(pow(2, PWM_BITS) - 1);
void writeToPin(unsigned int pin, unsigned int value) {}
unsigned long getElapsedTime() { return 100; }
long randomIntensityNumber() { return 100; }
void init(unsigned int pin) {}

#elif defined(ARDUINO)
const unsigned int PWM_BITS = 8;
const unsigned int MAX_INTENSITY =
    static_cast<unsigned int>(pow(2, PWM_BITS) - 1);
void writeToPin(unsigned int pin, unsigned int value) {
  analogWrite(pin, value);
}
unsigned long getElapsedTime() { return millis(); }
long randomIntensityNumber() { return random(0, MAX_INTENSITY); }
void init(unsigned int pin) { pinMode(pin, OUTPUT); }

#elif defined(STM32)
const unsigned int PWM_BITS = 16;
const unsigned int MAX_INTENSITY =
    static_cast<unsigned int>(pow(2, PWM_BITS) - 1);
void writeToPin(unsigned int pin, unsigned int value) {
  // find stm32 equivilant of analogWrite
}
unsigned long getElapsedTime() { return HAL_GetTick(); }
long randomIntensityNumber(){return TM_RNG_Get()};
void init(unsigned int pin) {
  // find stm32 equivilant of pinMode
}
#endif

LED::LED(unsigned int pin, unsigned int intensity)
    : _pin(pin), _intensity(intensity),
      _factor(MAX_INTENSITY * log10(2) / log10(255)) {
  init(_pin);
}

void LED::setPin(unsigned int pin) {
  _pin = pin;
  writeToPin(_pin, _intensity);
}

unsigned int LED::getPin() const { return _pin; }

void LED::setIntensity(unsigned int intensity) {
  _intensity = intensity < MAX_INTENSITY ? intensity : MAX_INTENSITY;
  writeToPin(_pin, _intensity);
}

unsigned int LED::getIntensity() const { return _intensity; }

void LED::setBlink(double interval) {
  _interval = interval;
  setIntensity(0);
  _runningFunction = 1;
}

void LED::setFlicker(double interval) {
  _interval = interval;
  _runningFunction = 2;
}

void LED::setTransition(unsigned int setIntensity, double interval,
                        unsigned int ticks) {
  _rateOfChange =
      abs(static_cast<int>(_setIntensity) - static_cast<int>(_intensity)) /
      (interval * ticks);
  _setIntensity = setIntensity < MAX_INTENSITY ? setIntensity : MAX_INTENSITY;
  _interval = interval;
  _runningFunction = 3;
}

void LED::setPulse(double interval) {
  _interval = interval;
  _rateOfChange = 1.5 * M_PI;
  _runningFunction = 4;
}

void LED::blink() {
  if ((_elapsedTime + _interval) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    if (_intensity == 0) {
      setIntensity(MAX_INTENSITY);
    } else {
      setIntensity(0);
    }
  }
}

void LED::flicker() {
  if ((_elapsedTime + _interval) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    setIntensity((randomIntensityNumber() % MAX_INTENSITY + _intensity));
  }
}

void LED::transition() {
  if ((_elapsedTime + _interval) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    double temp = 0;
    if (_intensity == _setIntensity) {
      return;
    } else if (_intensity < _setIntensity) {
      temp = pow(2, ((_intensity + _rateOfChange) / _factor));
      setIntensity(temp > _setIntensity ? _setIntensity : temp);
    } else if (_intensity > _setIntensity) {
      temp = pow(2, ((_intensity - _rateOfChange) / _factor));
      setIntensity(temp < _setIntensity ? _setIntensity : temp);
    }
  }
}

void LED::pulse() {
  _intensity = static_cast<unsigned int>(
      sin(_rateOfChange) * (MAX_INTENSITY / 2) + (MAX_INTENSITY / 2));
  setIntensity(_intensity / _factor);
  _rateOfChange = _rateOfChange + _interval;
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
