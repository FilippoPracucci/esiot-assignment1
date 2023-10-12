#include "lib.h"
#include "game_logic.h"

int leds[] = {L1, L2, L3, L4, LS};
int buttons[] = {B1, B2, B3, B4};
bool buttons_flags[4];
int count;
int current_state;
String welcome_message;
String go_message;


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

void green_leds_on() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
  }
}

void setup() {
  delay(2000);
  Serial.begin(9600);
  Serial.println("Inizio setup");
  current_state = 0;
  welcome_message = "Welcome to the Restore the Light Game. Press Key B1 to Start";
  go_message = "Go!";
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT); 
  }
  Serial.println(welcome_message);
  set_interrupt();
  pinMode(POT, INPUT);
  test_hw();
  for (int i = 0; i < 4; i++) {
    buttons_flags[i] = false;
  }
  
}

void loop() {
  switch (current_state) {
    case WAITING:
      fading(LS);
      break;
    case RUNNING:
      //set_difficulty());
      green_leds_on();
      delay(1000);
      generate_pattern();
      show_pattern();
      inserting_pattern();
      break;
    case SLEEPING:
      break;
  }
}
