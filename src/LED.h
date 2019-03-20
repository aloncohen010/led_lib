#ifndef LED_HEADER
#define LED_HEADER

#define X86

#if defined(X86)
#include <cmath>
#include <cstdint>
#elif defined(ARDUINO)
#include <math.h>
#include <stdint.h>
#elif defined(STM32)
#include <math.h>
#include <stdint.h>
#endif

class LED {

public:
  LED(uint8_t pin = 0, uint8_t intensity = 0);
  void setPin(uint8_t pin);
  uint8_t getPin() const;
  void setIntensity(uint8_t intensity);
  uint8_t getIntensity() const;
  void setBlink(uint8_t speed);
  void setFlicker(uint8_t interval);
  void setTransition(uint8_t setIntensity, uint8_t speed);
  void setPulse(uint32_t speed);
  void update();

private:
  uint8_t _pin;
  uint8_t _intensity;
  uint8_t _runningFunction = 0;
  uint32_t _elapsedTime = 0;
  uint8_t _interval = 0;
  uint8_t _setIntensity = 0;
  uint32_t _pulseSpeed = 0;
  uint32_t _pulseInput = 0;

  void blink();
  void flicker();
  void transition();
  void pulse();
};

#endif
