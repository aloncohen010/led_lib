#include "RGB_LED.h"

const byte numChars = 32;
const int numOfTokens = 8;
unsigned long elapsedTime = 0;
unsigned long interval = 0;
char receivedBytes[numChars];
char* tokens[numOfTokens];
bool newData = false;
RGB_LED rgb_led(11, 10, 9, COLOR(0, 0, 0), LOW);

void printMenu() {
  Serial.println("|****************************|");
  Serial.println("|**       LED Demo        |**|");
  Serial.println("|****************************|");
  Serial.println("");
  Serial.println("Usage:");
  Serial.println("  [test]");
  Serial.println("  [reset]");
  Serial.println("  [on]");
  Serial.println("  [off]");
  Serial.println("  [color, red(0-255), green(0-255), blue(0-255)]");
  Serial.println("  [blink, led(0-3), interval(milliseconds)]");
  Serial.println("  [flicker, led(0-3), interval(milliseconds)]");
  Serial.println("  [transition, led(0-3), intensity(0-255), interval(milliseconds");
  Serial.println("  [color_transition, red(0-255), green(0-255), blue(0-255), redInterval(milliseconds), greenInterval(milliseconds), blueInterval(milliseconds)");
  Serial.println("> ");
}

void reciveSerialBytes() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  if (Serial.available() > 0) {
    rc = Serial.read();
    if (rc != endMarker) {
      receivedBytes[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedBytes[ndx] = '\0';
      ndx = 0;
      newData = true;
    }
  }
}

void setup() {
  Serial.begin(9600);
  printMenu();
}

void loop() {
  elapsedTime = millis();
  rgb_led.update();
  reciveSerialBytes();
  if (newData && elapsedTime + interval < millis()) {
    tokens[0] = strtok(receivedBytes, ",");
    for (int i = 1; i < numOfTokens; i++) {
      tokens[i] = strtok(nullptr, ",");
    }
    for (int i = 0 ; i < numOfTokens ; i++) {
      if (tokens[i]) {
        Serial.print(tokens[i]);
        Serial.print(",");
      }
    }
    Serial.print("\n");
    if (tokens[0]) {
      if (!strcmp(tokens[0], "test")) {
        rgb_led.setColor(255, 0, 0);
        delay(1000);
        rgb_led.setColor(0, 255, 0);
        delay(1000);
        rgb_led.setColor(0 , 0, 255);
        delay(1000);
        rgb_led.setColor(0 , 0, 0);
      } else if (!strcmp(tokens[0], "reset")) {
        rgb_led.setColor(0, 0, 0);
        rgb_led.setOn();
      } else if (!strcmp(tokens[0], "on")) {
        rgb_led.setOn();
      } else if (!strcmp(tokens[0], "off")) {
        rgb_led.setOff();
      } else if (!strcmp(tokens[0], "color") && tokens[1] && tokens[2] && tokens[3]) {
        rgb_led.setColor(COLOR(static_cast<unsigned int>(atoi(tokens[1])),
                               static_cast<unsigned int>(atoi(tokens[2])),
                               static_cast<unsigned int>(atoi(tokens[3]))));
      } else if (!strcmp(tokens[0], "blink") && tokens[1] && tokens[2]) {
        rgb_led.setBlink(static_cast<RGB_LED::LED_ID>(atoi(tokens[1])),
                         static_cast<unsigned int>(atoi(tokens[2])));
      } else if (!strcmp(tokens[0], "flicker") && tokens[1] && tokens[2]) {
        rgb_led.setFlicker(static_cast<RGB_LED::LED_ID>(atoi(tokens[1])),
                           static_cast<unsigned int>(atoi(tokens[2])));
      } else if (!strcmp(tokens[0], "transition") && tokens[1] && tokens[2] && tokens[3]) {
        rgb_led.setTransition(static_cast<RGB_LED::LED_ID>(atoi(tokens[1])),
                              static_cast<unsigned int>(atoi(tokens[2])),
                              static_cast<double>(atof(tokens[3])));
      } else if (!strcmp(tokens[0], "color_transition") && tokens[1] && tokens[2] && tokens[3] && tokens[4] && tokens[5]) {
        rgb_led.setColorTransition(COLOR(static_cast<unsigned int>(atoi(tokens[1])),
                                         static_cast<unsigned int>(atoi(tokens[2])),
                                         static_cast<unsigned int>(atoi(tokens[3]))),
                                   static_cast<double>(atof(tokens[4])),
                                   static_cast<double>(atof(tokens[5])),
                                   static_cast<double>(atof(tokens[6])));
      } else if (!strcmp(tokens[0], "delay") && tokens[1]) {
        interval = static_cast<unsigned int>(atoi(tokens[1]));
      } else {
        Serial.println("Illegal input...");
      }
    } else {
      Serial.println("Illegal input...");
    }
    interval = 0;
    newData = false;
  }
}
