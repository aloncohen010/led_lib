#include "LED.h"

struct COLOR {
  COLOR(int r, int g, int b) : R(r), G(g), B(b) {}
  COLOR() : R(0), G(0), B(0) {}
  int R;
  int G;
  int B;
};

class RGB_LED {
public:
  enum LED_COLOR { RED, GREEN, BLUE };
  RGB_LED(int pin_red, int pin_green, int pin_blue, COLOR color);
  void setPins(int pin_red, int pin_green, int pin_blue);
  void setPin(LED_COLOR led, int pin);
  int getPin(LED_COLOR led);
  void setColor(COLOR color);
  const COLOR &getColor() const;
  void setBlink(LED_COLOR led, int speed);
  void setFlicker(LED_COLOR led, int speed);
  void setTransition(LED_COLOR led, int setIntensity, int speed);
  void setPulse(LED_COLOR led, float speed);
  void setColorTransition(COLOR color, int redSpeed, int greenSpeed,
                          int blueSpeed);
  void update();

private:
  LED _LEDS[3];
  COLOR _color;
};
