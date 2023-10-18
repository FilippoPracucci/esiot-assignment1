#include "lib.h"
#include "game_logic.h"

int leds[] = {L1, L2, L3, L4, LS};
int buttons[] = {B1, B2, B3, B4};
bool buttons_flags[4];
int count;
int current_state;
String welcome_message;
String go_message;
String next_level_message;
String game_over_message;

/* Uncomment this macro to enable the test of the hardware before running the program. */
//#define TEST
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
  delay(200);   //delay to avoid useless characters' prints.
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT); 
  }

  #ifdef TEST
  test_hw();
  #endif

  randomSeed(analogRead(0));  //fake reading to generate a different random seed
  current_state = 0;
  welcome_message = "Welcome to the Restore the Light Game. Press Key B1 to Start";
  go_message = "Go!";
  next_level_message = "New point! Score: ";
  game_over_message = "Game Over. Final Score: ";
  Serial.println(welcome_message);
  set_interrupt();
  pinMode(POT, INPUT);
  reset_all_buttons_flags();
}

void loop() {
  switch (current_state) {
    case WAITING:
      fading(LS);
      break;
    case RUNNING:
      green_leds_on();
      delay(random(2000) + 1000);
      generate_pattern();
      show_pattern();
      inserting_pattern();
      break;
    case SLEEPING:
      break;
  }
}
