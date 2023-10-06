#ifndef __LIB_H__
#define __LIB_H__

#define L1 2
#define L2 3
#define L3 4
#define L4 5
#define B1 8
#define B2 9
#define B3 10
#define B4 11
#define LS 6
#define POT A0

enum game_conditions {
  WAITING,
  RUNNING,
  SLEEPING
};

void change_button_flag(int);

void change_button1_flag();

void change_button2_flag();

void change_button3_flag();

void change_button4_flag();

void fading(int);

int set_difficulty();

#endif
