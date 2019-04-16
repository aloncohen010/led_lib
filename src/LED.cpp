#include "LED.h"

#if defined(X86)
using namespace std;
const unsigned int PWM_BITS = 8;
const unsigned int MAX_INTENSITY =
    static_cast<unsigned int>(pow(2, PWM_BITS) - 1);
void analogWrite(unsigned int pin, unsigned int value) {}
unsigned long getElapsedTime() { return 100; }
long randomIntensityNumber() { return 100; }
void initializePin(unsigned int pin) {}

#elif defined(ARDUINO)
const unsigned int PWM_BITS = 8;
const unsigned int MAX_INTENSITY =
    static_cast<unsigned int>(pow(2, PWM_BITS) - 1);
unsigned long getElapsedTime() { return millis(); }
long randomIntensityNumber() { return random(0, MAX_INTENSITY); }
void initializePin(unsigned int pin) { pinMode(pin, OUTPUT); }

#elif defined(STM32)
const unsigned int PWM_BITS = 16;
const unsigned int MAX_INTENSITY =
    static_cast<unsigned int>(pow(2, PWM_BITS) - 1);
void analogWrite(unsigned int pin, unsigned int value) {
  // find stm32 equivilant of analogWrite
}
unsigned long getElapsedTime() { return HAL_GetTick(); }
long randomIntensityNumber(){return TM_RNG_Get()};
void initializePin(unsigned int pin) {
  // find stm32 equivilant of pinMode
}
#endif

LED::LED(unsigned int pin, unsigned int intensity, PIN_STATE pinState) {
  initializePin(pin);
  setPin(pin, pinState);
  setIntensity(_intensity);
}

void LED::setPin(unsigned int pin, PIN_STATE pinState) {
  _pin = pin;
  _pinState = pinState;
}

unsigned int LED::getPin() const { return _pin; }

void LED::setIntensity(unsigned int intensity) {
  _intensity = intensity < MAX_INTENSITY ? intensity : MAX_INTENSITY;
  analogWrite(_pin, _pinState ? _intensity : (MAX_INTENSITY - _intensity));
}

unsigned int LED::getIntensity() const { return _intensity; }

void LED::setOn() {
  _runningFunction = 0;
  setIntensity(_intensity);
}

void LED::setOff() {
  _runningFunction = 0;
  setIntensity(0);
}

void LED::setBlink(double interval) {
  _runningFunction = 1;
  _interval = interval;
  setIntensity(0);
}

void LED::setFlicker(double interval) {
  _runningFunction = 2;
  _interval = interval;
}

void LED::setTransition(unsigned int setIntensity, double interval) {
  _runningFunction = 3;
  _setIntensity = setIntensity < MAX_INTENSITY ? setIntensity : MAX_INTENSITY;
  _step = _intensity;
  _factor =
      (abs(static_cast<int>(_setIntensity) - static_cast<int>(_intensity)) *
       log10(2)) /
      log10(255);
  _interval = interval;
}

void LED::setPulse(double interval) {
  _runningFunction = 4;
  _interval = interval;
  _funcValue = 1.5 * M_PI;
}

void LED::_blink() {
  if ((_elapsedTime + _interval) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    if (_intensity == 0) {
      setIntensity(MAX_INTENSITY);
    } else {
      setIntensity(0);
    }
  }
}

void LED::_flicker() {
  if ((_elapsedTime + _interval) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    setIntensity(randomIntensityNumber());
  }
}

void LED::_transition() {
  if ((_elapsedTime + _interval) < getElapsedTime()) {
    _elapsedTime = getElapsedTime();
    double temp = 0;
    if (_intensity == _setIntensity) {
      _runningFunction = 0;
      return;
    } else if (_intensity < _setIntensity) {
      temp = pow(2, _step / _factor);
      setIntensity(temp > _setIntensity ? _setIntensity : temp);
      _step++;
    } else if (_intensity > _setIntensity) {
      temp = pow(2, _step / _factor);
      setIntensity(temp > _setIntensity ? _setIntensity : temp);
      _step--;
    }
  }
}

void LED::_pulse() {
  setIntensity(static_cast<unsigned int>(sin(_funcValue) * (MAX_INTENSITY / 2) +
                                         (MAX_INTENSITY / 2)));
  _funcValue = _funcValue + _interval;
}

void LED::update() {
  switch (_runningFunction) {
  case 0:
    break;
  case 1:
    _blink();
    break;
  case 2:
    _flicker();
    break;
  case 3:
    _transition();
    break;
  case 4:
    _pulse();
    break;
  }
}
