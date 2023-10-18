#include "lib.h"
#include "game_logic.h"
#include <stdio.h>  
#include <stdlib.h>
#include <Arduino.h>

unsigned long t2 = T2;
unsigned long t3 = T3;
int pattern[DIM];
int played[DIM] = {4, 4, 4, 4};
int score = 0;

extern int leds[];
extern bool buttons_flags[];
extern float f;
extern String next_level_message;
extern String game_over_message;

void generate_pattern() {
  int n;
  int j;
  
  for (int i = 0; i < DIM; i++) {
    n = random(DIM);
    for (j = 0; j < i; j++) {
      if (n == pattern[j]) {
        i--;
        break;
      }
    }
    if (j == i) {
      pattern[i] = n;
    }
  }
}

void add_played_button(int pos_button) {
  int index = num_played_buttons();
  played[index] = pos_button;
}

bool is_correct() {
  for (int i = 0; i < DIM; i++) {
    if (played[i] != pattern[DIM - i - 1]) {
      reset_played_buttons();
      return false;
    }
  }
  reset_played_buttons();
  return true;
}

void reset_played_buttons() {
  for (int i = 0; i < DIM; i++) {
    played[i] = 4;
  }
}

void show_pattern() {
  for (int i = 0; i < DIM; i++) {
    digitalWrite(leds[pattern[i]], LOW);
    delay(t2/DIM);
  }
}

int num_played_buttons() {
  int i;
  for (i = 0; i < DIM && played[i] != 4; i++) {
  }
  return i;
}

void inserting_pattern() {
  unsigned long start_time = millis();
  do {
    for (int i = 0; i < 4; i++) {
      if (buttons_flags[i]) {
        add_played_button(i);
        reset_button_flag(i);
      }
    }
  } while (millis() - start_time < t3 && num_played_buttons() < 4);
  if (is_correct()) {
    if (score < 6) {
      t2 = t2 * f;
      t3 = t3 * f;
    }
    Serial.println(next_level_message + (++score));
  } else {
    end_game();
  }
  delay(2000);
}

void end_game() {
  Serial.println(game_over_message +  score);
  digitalWrite(LS, HIGH);
  delay(1000);
  digitalWrite(LS, LOW);
  init_setup();
  fading(LS);
}

void init_setup() {
  t2 = T2;
  t3 = T3;
  score = 0;
}
