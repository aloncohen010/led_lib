#ifndef LED_HEADER
#define LED_HEADER

class LED {

public:
  LED(int pin = 0, int intensity = 0);
  void setPin(int pin);
  int getPin() const;
  void setIntensity(int intensity);
  int getIntensity() const;
  void setBlink(int speed);
  void setFlicker(int step);
  void setTransition(int setIntensity, int speed);
  void setPulse(float speed);
  void update();

private:
  int _pin;
  int _intensity;
  int _runningFunction = 0;
  unsigned long _elapsedTime = 0;
  int _step = 0;
  int _setIntensity = 0;
  float _pulseSpeed = 0;
  float _pulseInput = 0;

  void blink();
  void flicker();
  void transition();
  void pulse();
};

#endif
