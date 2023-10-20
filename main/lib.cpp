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
float f;

void set_interrupt() {
  enableInterrupt(buttons[0], change_button1_flag, RISING);
  enableInterrupt(buttons[1], change_button2_flag, RISING);
  enableInterrupt(buttons[2], change_button3_flag, RISING);
  enableInterrupt(buttons[3], change_button4_flag, RISING);
}

void reset_button_flag(int pos) {
  buttons_flags[pos] = false;
}

void change_button1_flag() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 500ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > DEBOUNCE_TIME) {
    Serial.println("Premuto pulsante 1");
    buttons_flags[0] = true;
  }
  last_interrupt_time = interrupt_time;
}

void change_button2_flag() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 500ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > DEBOUNCE_TIME) {
    Serial.println("Premuto pulsante 2");
    buttons_flags[1] = true;
  }
  last_interrupt_time = interrupt_time;
}

void change_button3_flag() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 500ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > DEBOUNCE_TIME) {
    Serial.println("Premuto pulsante 3");
    buttons_flags[2] = true;
  }
  last_interrupt_time = interrupt_time;
}

void change_button4_flag() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 500ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > DEBOUNCE_TIME) {
    Serial.println("Premuto pulsante 4");
    buttons_flags[3] = true;
  }
  last_interrupt_time = interrupt_time;
}

void green_leds_on() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
  }
}

void reset_all_buttons_flags() {
  for (int i = 0; i < 4; i++) {
    reset_button_flag(i);
  }
}

void fading(int pin) {
  int brightness = 0;
  int fadeAmount = 5;
  unsigned long start_time = millis();
  unsigned long last = millis();
  while ((millis() - start_time) < FADING_TIME && !buttons_flags[0]) {
    if ((millis() - last) > 15) {
      analogWrite(pin, brightness);   
      brightness = brightness + fadeAmount;
      if (brightness == 0 || brightness == 255) {
        fadeAmount = -fadeAmount ; 
      }
      last = millis();      
    }
  }
  digitalWrite(LS, LOW);
  if (buttons_flags[0]) {
    //reset_button_flag(0);
    buttons_flags[0] = false;
    current_state = 1;
    Serial.println(go_message);
  } else {
    current_state = 2;
    sleep_now();
    //wakes up after an interrupt
    wake_up();
  }
  f = set_difficulty();
}

float set_difficulty() {
  return (1.00 - (map(analogRead(POT), 0, 1023, 1, 4) / 10.00));
}

void sleep_now() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();
}

void wake_up() {
  sleep_disable(); 
  reset_all_buttons_flags();
  fading(LS);
}
