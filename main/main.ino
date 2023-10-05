#define L1 2
#define L2 3
#define L3 4
#define L4 5
#define B1 10
#define B2 11
#define B3 12
#define B4 13
#define LS 9
#define POT A0

#include <EnableInterrupt.h>

int leds[] = {L1, L2, L3, L4, LS};
int buttons[] = {B1, B2, B3, B4};

void test_hw() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(1000);
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT); 
  }
  for (int i = 0; i < 4; i++) {
    //pinMode(buttons[i], INPUT);
    enableInterrupt(buttons[i], test_hw, FALLING);
  }
  pinMode(POT, INPUT);
  test_hw();
}

void loop() {
}
