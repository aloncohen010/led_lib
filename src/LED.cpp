#include "LED.h"

#if defined(X86)
using namespace std;
const uint8_t PWM_BITS = 8;
void writeToPin(uint8_t pin, uint8_t value) {}
uint32_t getElapsedTime() { return 100; }
long randomIntensityNumber() { return 100; }
void init(uint8_t pin) {}
#elif defined(ARDUINO)
const uint8_t PWM_BITS = 8;
void writeToPin(uint8_t pin, uint8_t value) { analogWrite(pin, value); }
uint32_t getElapsedTime() { return millis(); }
long randomIntensityNumber() { return random(0, MAX_INTENSITY); }
void init(uint8_t pin) { pinMode(pin, OUTPUT); }
#elif defined(STM32)
const uint8_t PWM_BITS = 16;
void writeToPin(uint8_t pin, uint8_t value) {
  // find stm32 equivilant of analogWrite
}
uint32_t getElapsedTime() { return HAL_GetTick(); }
long randomIntensityNumber(){return TM_RNG_Get()};
void init(uint8_t pin) {
  // find stm32 equivilant of pinMode
}
#endif

const uint8_t MAX_INTENSITY = pow(2, PWM_BITS) - 1;

LED::LED(uint8_t pin, uint8_t intensity)
    : _pin(pin), _intensity(intensity), _pulseInput(1.5 * M_PI) {
  init(_pin);
}

void LED::setPin(uint8_t pin) {
  _pin = pin;
  writeToPin(_pin, _intensity);
}

uint8_t LED::getPin() const { return _pin; }

void LED::setIntensity(uint8_t intensity) {
  _intensity = intensity < MAX_INTENSITY ? intensity : MAX_INTENSITY;
  writeToPin(_pin, _intensity);
}

uint8_t LED::getIntensity() const { return _intensity; }

void LED::setBlink(uint8_t speed) {
  _interval = speed;
  setIntensity(0);
  _runningFunction = 1;
}

void LED::setFlicker(uint8_t interval) {
  _interval = interval;
  _runningFunction = 2;
}

void LED::setTransition(uint8_t setIntensity, uint8_t interval) {
  _setIntensity = setIntensity < MAX_INTENSITY ? setIntensity : MAX_INTENSITY;
  _interval = interval;
  _runningFunction = 3;
}

void LED::setPulse(uint32_t interval) {
  _pulseSpeed = interval;
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
    if (_intensity < _setIntensity && _intensity == 0) {
      tempIntensity = pow(2, 1);
    } else if (_intensity < _setIntensity && _intensity > 0) {
      tempIntensity = pow(2, (log10(_intensity) / log10(2))) + 1;
    } else if (_intensity > _setIntensity && _setIntensity == 0) {
      tempIntensity = pow(2, (log10(_intensity) / log10(2))) - 1;
      setIntensity(tempIntensity > _setIntensity ? _setIntensity
                                                 : tempIntensity);
    } else if (_intensity > _setIntensity && _setIntensity > 0) {
      tempIntensity = pow(2, (log10(_intensity) / log10(2))) - 1;
      setIntensity(tempIntensity > _setIntensity ? _setIntensity
                                                 : tempIntensity);
    }
  }

  void LED::pulse() {
    _intensity = static_cast<uint8_t>(
        sin(_pulseInput) * (static_cast<uint8_t>(MAX_INTENSITY) / 2) +
        (static_cast<uint8_t>(MAX_INTENSITY) / 2));
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
