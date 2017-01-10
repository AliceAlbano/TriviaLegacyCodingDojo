#include <stdbool.h>

struct Player;

struct Player *player_new(const char *name);
char * get_player_name(struct Player *player);
