#include <EnableInterrupt.h>
#include "lib.h"

int leds[] = {L1, L2, L3, L4, LS};
int buttons[] = {B1, B2, B3, B4};
boolean buttons_flags[4];
int count;
int current_state;


void test_hw() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(1000);
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void test_buttons() {
  Serial.println("Clicked");
}

void setup() {
  Serial.begin(9600);
  current_state = 0;
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT); 
  }
  /*for (int i = 0; i < 4; i++) {
    //pinMode(buttons[i], INPUT);
    enableInterrupt(buttons[i], change_button_flag, FALLING);
  }*/
  enableInterrupt(buttons[0], change_button1_flag, FALLING);
  enableInterrupt(buttons[1], change_button2_flag, FALLING);
  enableInterrupt(buttons[2], change_button3_flag, FALLING);
  enableInterrupt(buttons[3], change_button4_flag, FALLING);
  pinMode(POT, INPUT);
  test_hw();
  //delay(5000);
  for (int i = 0; i < 4; i++) {
    buttons_flags[i] = false;
    //Serial.println(String("Stato = ") + buttons_flags[i]);
  }
}

void loop() {
  if (current_state == 0) {
    fading(LS);
  } else if (current_state == 1) {
    Serial.println(set_difficulty());
  }
  /*for (int i = 0; i < 4; i++) {
    if (buttons_flags[i] == true) {
      change_button_flag(i);
    }
  }*/
}
