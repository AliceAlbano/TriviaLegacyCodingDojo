#include <stdbool.h>

struct Player;

struct Player *player_new(const char *name);
char * get_player_name(struct Player *player);
void set_player_place(struct Player *player, int place);
int get_player_place(struct Player *player);
void set_player_purse(struct Player *player, int purse);
int get_player_purse(struct Player *player);
void set_player_in_penalty_box(struct Player *player, bool b);
bool get_player_in_penalty_box(struct Player *player);
