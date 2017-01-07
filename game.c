#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 6

static void ask_question (struct Game *game, const char *category);
static const char * next_question(struct Game *game, const char *category);
static const char * current_category (struct Game *game);
static bool did_player_win (struct Game *game);

typedef char Question[255];

Question pop_questions[50];
Question science_questions[50];
Question sports_questions[50];
Question rock_questions[50];

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
	Question * pop_question;
	Question * science_question;
	Question * sports_question;
	Question * rock_question;
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
	int i;
	struct Game *game;

	game = (struct Game *) malloc (sizeof (struct Game));
	//TODO: test return value of malloc and return NULL if fail
	game->player_num = 0;
	game->current_player = 0;

	game->pop_question = pop_questions;
	game->science_question = science_questions;
	game->sports_question = sports_questions;
	game->rock_question = rock_questions;

	for (i = 0; i < 50; i++)
	{
		sprintf (pop_questions[i], "Pop Question %d", i);
		sprintf (science_questions[i], "Science Question %d", i);
		sprintf (sports_questions[i], "Sports Question %d", i);
		sprintf (rock_questions[i], "Rock Question %d", i);
	}

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
			printf ("The category is %s\n", current_category (game));
			ask_question (game, current_category(game));
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
		printf ("The category is %s\n", current_category (game));
		ask_question (game, current_category(game));
	}

}

const char * next_question(struct Game *game, const char *category)
{
	if (!strcmp (category, "Pop"))
	{
		return *(++game->pop_question);
	}
	if (!strcmp (category, "Science"))
	{
		return *(++game->science_question);
	}
	if (!strcmp (category, "Sports"))
	{
		return *(++game->sports_question);
	}
	if (!strcmp (category, "Rock"))
	{
		return *(++game->rock_question);
	}

	/* XXX : By default we returns a Rock question. Every body loves rock !*/
	return *(++game->rock_question);
}

void ask_question (struct Game *game, const char *category)
{
	printf ("%s\n", next_question(game, category));
}

const char * current_category (struct Game *game)
{
	if (game->places[game->current_player] == 0)
		return "Pop";
	if (game->places[game->current_player] == 4)
		return "Pop";
	if (game->places[game->current_player] == 8)
		return "Pop";
	if (game->places[game->current_player] == 1)
		return "Science";
	if (game->places[game->current_player] == 5)
		return "Science";
	if (game->places[game->current_player] == 9)
		return "Science";
	if (game->places[game->current_player] == 2)
		return "Sports";
	if (game->places[game->current_player] == 6)
		return "Sports";
	if (game->places[game->current_player] == 10)
		return "Sports";
	return "Rock";
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
