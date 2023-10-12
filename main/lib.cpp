#include <Arduino.h>
#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include "lib.h"

extern int leds[];
extern int buttons[];
extern bool buttons_flags[];
extern int count;
extern int current_state;
extern String go_message;

void set_interrupt() {
  enableInterrupt(buttons[0], change_button1_flag, RISING);
  enableInterrupt(buttons[1], change_button2_flag, RISING);
  enableInterrupt(buttons[2], change_button3_flag, RISING);
  enableInterrupt(buttons[3], change_button4_flag, RISING);
}

void test_int() {
  
}

void set2_interrupt() {
  enableInterrupt(buttons[0], test_int, RISING);
  enableInterrupt(buttons[1], test_int, RISING);
  enableInterrupt(buttons[2], test_int, RISING);
  enableInterrupt(buttons[3], test_int, RISING);
}

void unset_interrupt() {
  for (int i = 0; i < 4; i++) {
    disableInterrupt(buttons[i]);  
    Serial.println(String("Sto disabilitando il pulsante ") + buttons[i]);
  }
}

void change_button_flag(int pos) {
  buttons_flags[pos] = false;
}

void change_button1_flag() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 1000)
  {
    buttons_flags[0] = true;
  }
  last_interrupt_time = interrupt_time;
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

void reset_buttons_flags() {
  for (int i = 0; i < 4; i++) {
    buttons_flags[i] = false;
  }
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
    Serial.println(go_message);
  } else {
    Serial.println("Sleep");
    current_state = 2;
    sleep_now();
  }
  digitalWrite(LS, LOW);
}

int set_difficulty() {
  return map(analogRead(POT), 0, 1023, 1, 4);
}

void sleep_now() {
  Serial.println("Inizio sleep");
  //set2_interrupt();
  delay(2000);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode(); 
  sleep_disable(); 
  Serial.println("Sveglio");
  reset_buttons_flags();
  fading(LS);
}
