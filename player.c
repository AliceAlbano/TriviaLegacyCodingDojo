#include "player.h"
#include <string.h>
#include <stdlib.h>

struct Player
{
	char name[30];
	int place;
	int purse;
	bool in_penalty_box;
};

struct Player * player_new(const char *name)
{
	struct Player *player;
	player = (struct Player *) malloc (sizeof (struct Player));
	strcpy(player->name, name);
	player->place = 0;
	player->purse = 0;
	player->in_penalty_box = false;
	return player;
}

char * get_player_name(struct Player *player)
{
	return player->name;
}
