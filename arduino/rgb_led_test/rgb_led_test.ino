#include "RGB_LED.h"

const byte numChars = 32;
const int numOfTokens = 8;
unsigned long elapsedTime = 0;
unsigned long interval = 0;
char receivedBytes[numChars];
char* tokens[numOfTokens];
bool newData = false;
int choice = 0;
RGB_LED rgb_led(11, 10, 9, COLOR(0, 0, 0));

void printMenu() {
  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");
  Serial.println("|****************************|");
  Serial.println("|**       LED Demo        |**|");
  Serial.println("|****************************|");
  Serial.println("");
  Serial.println("Usage: [set_color, red(0-255), green(0-255), blue(0-255)]");
  Serial.println("       [blink, led(0-3), interval(seconds)]");
  Serial.println("       [flicker, led(0-3), interval(seconds)]");
  Serial.println("       [transition, led(0-3), intensity(0-255), interval(seconds), ticks(>0)]");
  Serial.println("       [color_transition, red(0-255), green(0-255), blue(0-255), redInterval(seconds), greenInterval(seconds), blueInterval(seconds), ticks(>0)]");
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
  for (int i = 0; i < numOfTokens; i++) {
    tokens[i] = nullptr;
  }
}

void loop() {
  rgb_led.update();
  reciveSerialBytes();
  if (newData && elapsedTime + interval < millis()) {
    for (int i = 0; i < numOfTokens; i++) {
      tokens[i] = strtok(receivedBytes, "\n");
    }
    if (tokens[0]) {
      if (strcmp(tokens[0], "set_color") && tokens[1] && tokens[2] && tokens[3]) {
        rgb_led.setColor(COLOR(static_cast<unsigned int>(atoi(tokens[1])),
                               static_cast<unsigned int>(atoi(tokens[2])),
                               static_cast<unsigned int>(atoi(tokens[3]))));
      } else if (strcmp(tokens[0], "blink") && tokens[1] && tokens[2]) {
        rgb_led.setBlink(static_cast<RGB_LED::LED_ID>(atoi(tokens[1])),
                         static_cast<unsigned int>(atoi(tokens[2])));
      } else if (strcmp(tokens[0], "flicker") && tokens[1] && tokens[2]) {
        rgb_led.setFlicker(static_cast<RGB_LED::LED_ID>(atoi(tokens[1])),
                           static_cast<unsigned int>(atoi(tokens[2])));
      } else if (strcmp(tokens[0], "transition") && tokens[1] && tokens[2] && tokens[3] && tokens[4] && tokens[5]) {
        rgb_led.setTransition(static_cast<RGB_LED::LED_ID>(atoi(tokens[1])),
                              static_cast<unsigned int>(atoi(tokens[2])),
                              static_cast<double>(atof(tokens[3])),
                              static_cast<unsigned int>(atoi(tokens[4])));
      } else if (strcmp(tokens[0], "color_transition") && tokens[1] && tokens[2] && tokens[3] && tokens[4] && tokens[5]) {
        rgb_led.setColorTransition(COLOR(static_cast<unsigned int>(atoi(tokens[1])),
                                         static_cast<unsigned int>(atoi(tokens[2])),
                                         static_cast<unsigned int>(atoi(tokens[3]))),
                                   static_cast<double>(atof(tokens[4])),
                                   static_cast<double>(atof(tokens[5])),
                                   static_cast<double>(atof(tokens[6])),
                                   static_cast<unsigned int>(atoi(tokens[7])));
      } else if (strcmp(tokens[0], "delay") && tokens[1]) {
        interval = static_cast<unsigned int>(atoi(tokens[1]);
      } else {
        Serial.println("Illegal input...");
      }
    } else {
      Serial.println("Illegal input...");
    }
  }
}
