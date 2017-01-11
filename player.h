#include <stdbool.h>

struct Player;

struct Player *player_new();
void set_player_id(struct Player *player, int id);
int get_player_id(struct Player *player);
char * get_player_name(struct Player *player);
void set_player_name(struct Player *player, const char *name);
void set_player_place(struct Player *player, int place);
int get_player_place(struct Player *player);
void set_player_purse(struct Player *player, int purse);
int get_player_purse(struct Player *player);
void set_player_in_penalty_box(struct Player *player, bool b);
bool get_player_in_penalty_box(struct Player *player);
void move_player(struct Player *player, int roll);
void correct_answer(struct Player *player);
bool get_out_of_penalty_box(struct Player *player, int roll);
