#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#define DIM 4
#define T2 8000
#define T3 15000

/*
* Generates the pattern of leds to turn off.
*/
void generate_pattern();

/*
* Adds the button played to the sequence.
*/
void add_played_button(int);

/*
* Controls if the sequence played is correct.
*/
bool is_correct();

/*
* Reset the sequence of played buttons.
*/
void reset_played_buttons();

/*
* Shows the pattern generated.
*/
void show_pattern();

/*
* Returns the number of buttons already played.
*/
int num_played_buttons();

/*
* Manages the game phase of pressing the buttons.
*/
void inserting_pattern();

/*
* Manages the end of the game.
*/
void end_game();

/*
* Initializes the setup of the game.
*/
void init_setup();

#endif
