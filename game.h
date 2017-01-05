#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

struct Game;
struct Game *game_new ();

int get_place(struct Game *game, int i);
int get_purse(struct Game *game, int i);
bool get_in_penalty_box(struct Game *game, int i);
int get_player_num(struct Game *game);
int get_current_player(struct Game *game);

bool game_is_playable (struct Game *game);
bool game_add (struct Game *game, const char *player_name);

void game_roll (struct Game *game, int roll);

bool game_was_correctly_answered (struct Game *game);
bool game_wrong_answer (struct Game *game);

#endif /* GAME_H */
