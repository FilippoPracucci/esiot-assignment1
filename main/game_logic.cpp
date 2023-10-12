#include "lib.h"
#include "game_logic.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>
#include <Arduino.h>

unsigned long T2 = 8000;
unsigned long T3 = 15000;
unsigned int F;
int pattern[DIM];
int played[DIM] = {4, 4, 4, 4};

extern int leds[];
extern bool buttons_flags[];

void generate_pattern() {
  int n;
  int j;
  
  srand((unsigned int) time(NULL));
  for (int i = 0; i < DIM; i++) {
    n = random(0, DIM);
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
    if (played[i] != pattern[DIM - i]) {
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
    delay(T2/DIM);
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
  
  while (millis() - start_time < T3 && num_played_buttons() < 3) {
    for (int i = 0; i < 4; i++) {
      if (buttons_flags[i]) {
        Serial.println(String("Hai premuto tasto ") + i);
        add_played_button(i);
        break;
      }
    }
    reset_buttons_flags();
  }
  for (int i = 0; i < 4; i++) {
    Serial.println(played[i]);
  }
  if (is_correct()) {
    Serial.println("Corretta");
  } else {
    Serial.println("Coglione");
  }
  delay(2000);
}
