#include "player.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Player
{
	int id;
	char name[30];
	int place;
	int purse;
	bool in_penalty_box;
};

struct Player * player_new()
{
	struct Player *player;
	player = (struct Player *) malloc (sizeof (struct Player));
	player->id = -1;
	strcpy(player->name, "");
	player->place = 0;
	player->purse = 0;
	player->in_penalty_box = false;
	return player;
}

void set_player_id(struct Player *player, int id)
{
	player->id = id;
}

int get_player_id(struct Player *player)
{
	return player->id;
}

char * get_player_name(struct Player *player)
{
	return player->name;
}

void set_player_name(struct Player *player, const char *name)
{
	strcpy(player->name, name);
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

void set_player_in_penalty_box(struct Player *player, bool b)
{
	player->in_penalty_box = b;
}

bool get_player_in_penalty_box(struct Player *player)
{
	return player->in_penalty_box;
}

void move_player(struct Player *player, int roll)
{
		int player_place = get_player_place(player);
		set_player_place(player, player_place + roll);
		if (get_player_place(player) > 11)
			set_player_place(player, get_player_place(player) - 12);
		printf ("%s's new location is %d\n", get_player_name(player), get_player_place(player));
}
