#ifndef LED_HEADER
#define LED_HEADER

#if defined(X86)
#include <cmath>
#include <cstdint>

#elif defined(ARDUINO)
#include <arduino.h>
#include <math.h>
#include <stdint.h>

#elif defined(STM32)
#include <math.h>
#include <stdint.h>
#endif

extern const unsigned int PWM_BITS;
extern const unsigned int MAX_INTENSITY;

class LED {

public:
  enum PIN_ON_STATE { _HIGH, _LOW };
  LED(unsigned int pin = 0, unsigned int intensity = 0,
      PIN_ON_STATE pinOnState = PIN_ON_STATE::_HIGH);
  void setPin(unsigned int pin, PIN_ON_STATE pinOnState = PIN_ON_STATE::_HIGH);
  unsigned int getPin() const;
  void setIntensity(unsigned int intensity);
  unsigned int getIntensity() const;
  void setOn();
  void setOff();
  void setBlink(double interval);
  void setFlicker(double interval);
  void setTransition(unsigned int setIntensity, double interval);
  void setPulse(double interval);
  void update();

private:
  unsigned int _pin;
  unsigned int _intensity;
  unsigned int _runningFunction = 0;
  unsigned long _elapsedTime = 0;
  unsigned int _setIntensity;
  unsigned int _step;
  double _funcValue;
  double _interval;
  double _factor;
  PIN_ON_STATE _pinState;
  void _blink();
  void _flicker();
  void _transition();
  void _pulse();
};

#endif
