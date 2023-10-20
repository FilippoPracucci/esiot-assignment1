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
#define DEBOUNCE_TIME 500
#define FADING_TIME 10000

enum game_state {
  WAITING,
  RUNNING,
  SLEEPING
};

/*
* Enables and configures all the interrupts.
*/
void set_interrupt();

/*
* Change the flag of the first button to true, managing the bouncing.
*/
void change_button1_flag();

/*
* Change the flag of the second button to true, managing the bouncing.
*/
void change_button2_flag();

/*
* Change the flag of the third button to true, managing the bouncing.
*/
void change_button3_flag();

/*
* Change the flag of the fourth button to true, managing the bouncing.
*/
void change_button4_flag();

/*
* Turns on all the green leds.
*/
void green_leds_on();

/*
* Resets all the flags of the buttons.
*/
void reset_all_buttons_flags();

/*
* Controls the fading of a led by passing its pin number.
*/
void fading(int);

/* 
* Set the difficulty as 1 - the level decided by the trimmer divided by 10.
  So in the specific case of the game the difficulty range is (0.9 - 0.6)
*/
float set_difficulty();

/*
* Puts arduino in deep sleep.
*/
void sleep_now();

/*
* Wakes up arduino.
*/
void wake_up();

/*
* Shows the difficulty level.
*/
void show_difficulty();

#endif
