#include "LED.h"

#ifndef RGB_LED_HEADER
#define RGB_LED_HEADER

struct COLOR {
  COLOR(unsigned int r, unsigned int g, unsigned int b) : R(r), G(g), B(b) {}
  COLOR() : R(0), G(0), B(0) {}
  unsigned int R;
  unsigned int G;
  unsigned int B;
};

class RGB_LED {
public:
  enum LED_COLOR { RED, GREEN, BLUE };
  RGB_LED(unsigned int pin_red, unsigned int pin_green, unsigned int pin_blue, COLOR color);
  void setPins(unsigned int pin_red, unsigned int pin_green, unsigned int pin_blue);
  void setPin(LED_COLOR led, unsigned int pin);
  unsigned int getPin(LED_COLOR led);
  void setColor(COLOR color);
  const COLOR &getColor() const;
  void setBlink(LED_COLOR led, unsigned int speed);
  void setFlicker(LED_COLOR led, unsigned int speed);
  void setTransition(LED_COLOR led, unsigned int setIntensity, unsigned int speed);
  void setPulse(LED_COLOR led, float speed);
  void setColorTransition(COLOR color, unsigned int redSpeed, unsigned int greenSpeed,
                          unsigned int blueSpeed);
  void update();

private:
  LED _LEDS[3];
  COLOR _color;
};

#endif
