#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#define DIM 4
#define T2 8000
#define T3 15000

void generate_pattern();

void add_played_button(int);

bool is_correct();

void reset_played_buttons();

void show_pattern();

int num_played_buttons();

void inserting_pattern();

void end_game();

void init_setup();

#endif
