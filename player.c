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

void set_player_place(struct Player *player, int place)
{
	player->place = place;
}

int get_player_place(struct Player *player)
{
	return player->place;
}

void set_player_purse(struct Player *player, int purse)
{
	player->purse = purse;
}

int get_player_purse(struct Player *player)
{
	return player->purse;
}
