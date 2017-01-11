#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 6

const char* c1 = "Pop";
const char* c2 = "Science";
const char* c3 = "Sports";
const char* c4 = "Rock";

static void ask_question(struct Category *category);
static struct Category * current_category(struct Game *game);
static bool did_player_win(struct Game *game);
static void initialize_player(struct Game *game);
static void set_player_num(struct Game *game, int n);
static void set_current_player(struct Game *game, int n);
static void set_next_player(struct Game *game);

struct Game
{
	struct Player *players[MAX_PLAYERS];
	int player_num;
	int current_player;
	bool is_getting_out_of_penalty_box;
	struct Category *pop;
	struct Category *science;
	struct Category *sports;
	struct Category *rock;
};

int get_player_num(struct Game *game)
{
	return game->player_num;
}

void set_player_num(struct Game *game, int n)
{
	game->player_num = n;
}

void set_current_player(struct Game *game, int n)
{
	game->current_player = n;
}
int get_current_player(struct Game *game)
{
	return game->current_player;
}

int get_available_places(struct Game *game)
{
	return (MAX_PLAYERS - game->player_num);
}

struct Game *game_new()
{
	struct Game *game;

	game = (struct Game *) malloc(sizeof(struct Game));
	//TODO: test return value of malloc and return NULL if fail

	initialize_player(game);

	game->pop = category_new(c1);
	game->science = category_new(c2);
	game->sports = category_new(c3);
	game->rock = category_new(c4);

	return game;
}

void initialize_player(struct Game *game)
{
	int i;
	for (i=0; i < MAX_PLAYERS; i++)
	{
		game->players[i] = player_new();
	}
	game->player_num = 0;
	game->current_player = 0;
}

bool game_is_playable(struct Game *game)
{
	if(get_player_num(game) >= 2)
		return true;
	else
		return false;
}

bool game_add(struct Game *game, char * player_name)
{
	int player_num = get_player_num(game);
	if (player_num >= MAX_PLAYERS)
		return false;
	set_player_id(game->players[player_num], player_num);
	set_player_name(game->players[player_num], player_name);
	set_player_num(game, player_num + 1);

	printf("%s was added\n", player_name);
	printf("%s is  number %d\n", player_name, get_player_num(game));

	return true;
}

void game_roll(struct Game *game, int roll)
{
	char * current_player_name = get_player_name(game->players[get_current_player(game)]);
	int current_player = get_current_player(game);
	struct Player *player = player_new();
	player = game->players[current_player];
	printf("%s is the current player\n", current_player_name);
	printf("They have rolled a %d\n", roll);

	if(get_player_in_penalty_box(player))
	{
		if (roll % 2 != 0)
		{
			game->is_getting_out_of_penalty_box = true;

			printf("%s is getting out of the penalty box\n",
					current_player_name);
			move_player(player, roll);
			printf("The category is %s\n", get_category_name(current_category(game)));
			ask_question(current_category(game));
		}
		else
		{
			printf("%s is not getting out of the penalty box\n",
					current_player_name);
			game->is_getting_out_of_penalty_box = false;
		}
	}
	else
	{
		move_player(player, roll);
		printf("The category is %s\n", get_category_name(current_category(game)));
		ask_question(current_category(game));
	}

}

void ask_question(struct Category *category)
{
	set_next_question(category);
	printf("%s\n", get_question_statement(get_next_question(category)));
}

struct Category * current_category(struct Game *game)
{
	int place = get_player_place(game->players[game->current_player]);
	if ((place% 4) == 0)
		return game->pop;
	if ((place % 4) == 1)
		return game->science;
	if ((place % 4) == 2)
		return game->sports;
	return game->rock;
}

bool game_was_correctly_answered(struct Game *game)
{
	struct Player *player = player_new();
	player = game->players[get_current_player(game)];
	if (get_player_in_penalty_box(player))
	{
		if (game->is_getting_out_of_penalty_box)
		{
			correct_answer(player);
			bool winner = did_player_win(game);
			set_next_player(game);
			return winner;
		}
		else
		{
			set_next_player(game);
			return true;
		}
	}
	else
	{

		correct_answer(player);
		bool winner = did_player_win(game);
		set_next_player(game);
		return winner;
	}
}

void set_next_player(struct Game *game)
{
		set_current_player(game, get_current_player(game) + 1);
		if (get_current_player(game) == get_player_num(game))
			set_current_player(game, 0);

}

bool game_wrong_answer(struct Game *game)
{
	printf("Question was incorrectly answered\n");
	printf("%s was sent to the penalty box\n",
			get_player_name(game->players[get_current_player(game)]));
	set_player_in_penalty_box(game->players[get_current_player(game)], true);

	set_current_player(game, get_current_player(game) + 1);
	if (get_current_player(game) == get_player_num(game))
		set_current_player(game, 0);
	return true;
}


bool did_player_win(struct Game *game)
{
	return !(get_player_purse(game->players[ get_current_player(game)]) == 6);
}
