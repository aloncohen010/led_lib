#ifndef RGB_LED_HEADER
#define RGB_LED_HEADER

#include "LED.h"

struct COLOR {
  COLOR(unsigned int r, unsigned int g, unsigned int b) : R(r), G(g), B(b) {}
  COLOR() : R(0), G(0), B(0) {}
  unsigned int R;
  unsigned int G;
  unsigned int B;
};

class RGB_LED {
public:
  enum LED_ID { RED, GREEN, BLUE };
  RGB_LED(unsigned int pin_red, unsigned int pin_green, unsigned int pin_blue,
          COLOR color, LED::PIN_ON_STATE pinOnState = LED::PIN_ON_STATE::_HIGH);
  void setPins(unsigned int pin_red, unsigned int pin_green,
               unsigned int pin_blue,
               LED::PIN_ON_STATE pinOnState = LED::PIN_ON_STATE::_HIGH);
  void setPin(LED_ID led, unsigned int pin,
              LED::PIN_ON_STATE pinOnState = LED::PIN_ON_STATE::_HIGH);
  unsigned int getPin(LED_ID led);
  void setColor(COLOR color);
  void setColor(unsigned int redValue, unsigned int greenValue,
                unsigned int blueValue);
  const COLOR &getColor() const;
  void setOn();
  void setOff();
  void setBlink(LED_ID led, double interval);
  void setFlicker(LED_ID led, double interval);
  void setTransition(LED_ID led, unsigned int setIntensity, double interval);
  void setPulse(LED_ID led, double interval);
  void setColorTransition(COLOR color, double redInterval, double greenInterval,
                          double blueInterval);
  void update();

private:
  LED _LEDS[3];
  COLOR _color;
};

#endif
