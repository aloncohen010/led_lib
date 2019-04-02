#ifndef LED_HEADER
#define LED_HEADER

//#define X86

#if defined(X86)
#include <cmath>
#include <cstdint>
#elif defined(ARDUINO)
#include <math.h>
#include <stdint.h>
#include <arduino.h>
#elif defined(STM32)
#include <math.h>
#include <stdint.h>
#endif

class LED {

public:
  LED(unsigned int pin = 0, unsigned int intensity = 0);
  void setPin(unsigned int pin);
  unsigned int getPin() const;
  void setIntensity(unsigned int intensity);
  unsigned int getIntensity() const;
  void setBlink(double interval);
  void setFlicker(double interval);
  void setTransition(unsigned int setIntensity, double interval,
                     unsigned int ticks);
  void setPulse(double interval);
  void update();

private:
  unsigned int _pin;
  unsigned int _intensity;
  unsigned int _runningFunction = 0;
  unsigned int _elapsedTime = 0;
  unsigned int _ticks;
  unsigned int _setIntensity;
  double _interval;
  double _rateOfChange;
  double _factor;

  void blink();
  void flicker();
  void transition();
  void pulse();
};

#endif
