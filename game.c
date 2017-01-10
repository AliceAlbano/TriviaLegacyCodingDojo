#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 6

const char* c1 = "Pop";
const char* c2 = "Science";
const char* c3 = "Sports";
const char* c4 = "Rock";

static void ask_question (struct Category *category);
static struct Category * current_category (struct Game *game);
static bool did_player_win (struct Game *game);

struct Game
{
	int places[MAX_PLAYERS];
	int purses[MAX_PLAYERS];
	bool in_penalty_box[MAX_PLAYERS];
	int player_num;
//TODO: Correct this horrible bug of a 50 pointers array :(
	char * players[50];
	int current_player;
	bool is_getting_out_of_penalty_box;
	struct Category *pop;
	struct Category *science;
	struct Category *sports;
	struct Category *rock;
};

int get_place(struct Game *game, int i)
{
	return game->places[i];
}

int get_purse(struct Game *game, int i)
{
	return game->purses[i];
}

bool get_in_penalty_box(struct Game *game, int i)
{
	return game->in_penalty_box[i];
}

int get_player_num(struct Game *game)
{
	return game->player_num;
}

int get_current_player(struct Game *game)
{
	return game->current_player;
}

int get_available_places(struct Game *game)
{
	return (MAX_PLAYERS - game->player_num);
}

struct Game *game_new ()
{
	struct Game *game;

	game = (struct Game *) malloc (sizeof (struct Game));
	//TODO: test return value of malloc and return NULL if fail
	game->player_num = 0;
	game->current_player = 0;

	game->pop = category_new(c1);
	game->science = category_new(c2);
	game->sports = category_new(c3);
	game->rock = category_new(c4);

	return game;
}

bool game_is_playable (struct Game *game)
{
	if (game->player_num >= 2)
		return true;
	else
		return false;
}

bool game_add (struct Game *game, const char * player_name)
{
	int player_num = game->player_num;
	if (player_num >= MAX_PLAYERS)
		return false;
	game->players[player_num] = strdup (player_name);
	game->places[player_num] = 0;
	game->purses[player_num] = 0;
	game->in_penalty_box[player_num] = false;
	game->player_num ++;

	printf ("%s was added\n", player_name);
	printf ("%s is  number %d\n", player_name, game->player_num);

	return true;
}

void game_roll (struct Game *game, int roll)
{
	char * current_player = game->players[game->current_player];
	int player_place = game->places[game->current_player];
	printf ("%s is the current player\n", current_player);
	printf ("They have rolled a %d\n", roll);

	if (game->in_penalty_box[game->current_player])
	{
		if (roll % 2 != 0)
		{
			game->is_getting_out_of_penalty_box = true;

			printf ("%s is getting out of the penalty box\n",
					current_player);
			game->places[game->current_player] = player_place + roll;
			if (player_place > 11)
				game->places[game->current_player] = player_place - 12;

			printf ("%s's new location is %d\n",
					current_player,
					player_place);
			printf ("The category is %s\n", get_category_name(current_category (game)));
			ask_question(current_category(game));
		}
		else
		{
			printf ("%s is not getting out of the penalty box\n",
					current_player);
			game->is_getting_out_of_penalty_box = false;
		}
	}
	else
	{
		game->places[game->current_player] =
			player_place + roll;
		if (player_place > 11)
			game->places[game->current_player] =
				player_place - 12;

		printf ("%s's new location is %d\n",
				current_player,
				player_place);
		printf ("The category is %s\n", get_category_name(current_category (game)));
		ask_question(current_category(game));
	}

}

void ask_question (struct Category *category)
{
	set_next_question(category);
	printf ("%s\n", get_question_statement(get_next_question(category)));
}

struct Category * current_category (struct Game *game)
{
	if (game->places[game->current_player] == 0)
		return game->pop;
	if (game->places[game->current_player] == 4)
		return game->pop;
	if (game->places[game->current_player] == 8)
		return game->pop;
	if (game->places[game->current_player] == 1)
		return game->science;
	if (game->places[game->current_player] == 5)
		return game->science;
	if (game->places[game->current_player] == 9)
		return game->science;
	if (game->places[game->current_player] == 2)
		return game->sports;
	if (game->places[game->current_player] == 6)
		return game->sports;
	if (game->places[game->current_player] == 10)
		return game->sports;
	return game->rock;
}

bool game_was_correctly_answered (struct Game *game)
{
	if (game->in_penalty_box[game->current_player])
	{
		if (game->is_getting_out_of_penalty_box)
		{
			printf ("Answer was correct!!!!\n");
			game->purses[game->current_player]++;
			printf ("%s now has %d Gold Coins.\n",
					game->players[game->current_player],
					game->purses[game->current_player]);
			bool winner = did_player_win (game);
			game->current_player++;
			if (game->current_player == game->player_num)
				game->current_player = 0;

			return winner;
		}
		else
		{
			game->current_player++;
			if (game->current_player == game->player_num)
				game->current_player = 0;
			return true;
		}



	}
	else
	{

		printf ("Answer was corrent!!!!\n");
		game->purses[game->current_player]++;
		printf ("%s now has %d Gold Coins.\n",
				game->players[game->current_player],
				game->purses[game->current_player]);

		bool winner = did_player_win (game);
		game->current_player++;
		if (game->current_player == game->player_num)
			game->current_player = 0;

		return winner;
	}
}

bool game_wrong_answer (struct Game *game)
{
	printf ("Question was incorrectly answered\n");
	printf ("%s was sent to the penalty box\n",
			game->players[game->current_player]);
	game->in_penalty_box[game->current_player] = true;

	game->current_player++;
	if (game->current_player == game->player_num)
		game->current_player = 0;
	return true;
}


bool did_player_win (struct Game *game)
{
	return !(game->purses[game->current_player] == 6);
}
