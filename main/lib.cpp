#include <Arduino.h>
#include "lib.h"

extern int leds[];
extern int buttons[];
extern bool buttons_flags[];
extern int count;
extern int current_state;

void change_button_flag(int pos) {
  buttons_flags[pos] = false;
}

void change_button1_flag() {
  buttons_flags[0] = true;
}

void change_button2_flag() {
  buttons_flags[1] = true;
}

void change_button3_flag() {
  buttons_flags[2] = true;
}

void change_button4_flag() {
  buttons_flags[3] = true;
}

void fading(int pin) {
  int brightness = 0;
  int fadeAmount = 5;
  unsigned long start_time = millis();
  unsigned long last = millis();
  while ((millis() - start_time) < 10000 && !buttons_flags[0]) {
    if ((millis() - last) > 15) {
      analogWrite(pin, brightness);   
      brightness = brightness + fadeAmount;
      if (brightness == 0 || brightness == 255) {
        fadeAmount = -fadeAmount ; 
      }
      last = millis();      
    }
  }
  if (buttons_flags[0]) {
    change_button_flag(0);
    current_state = 1;
  } else {
    current_state = 2;
  }
  digitalWrite(LS, LOW);
}

int set_difficulty() {
  return map(analogRead(POT), 0, 1023, 1, 4);
}
