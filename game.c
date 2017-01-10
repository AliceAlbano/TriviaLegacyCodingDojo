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
static void initialize_player(struct Game *game);
static void add_player_name(struct Game *game, const char * player_name);
static void set_player_place(struct Game *game, int player_num, int place);
static void set_player_purse(struct Game *game, int player_num, int purse);
static void set_in_penalty_box(struct Game *game, int player_num, bool b);
static void set_player_num(struct Game *game, int n);
static char * get_current_player_name(struct Game *game);
static int get_player_place(struct Game *game, int player_num);
static void set_current_player(struct Game *game, int n);

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

void set_in_penalty_box(struct Game *game, int player_num, bool b)
{
	game->in_penalty_box[player_num] = b;
}

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
char * get_current_player_name(struct Game *game)
{
	return game->players[get_current_player(game)];
}

int get_player_place(struct Game *game, int player_num)
{
	return game->places[player_num];
}

struct Game *game_new ()
{
	struct Game *game;

	game = (struct Game *) malloc (sizeof (struct Game));
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
	game->player_num = 0;
	game->current_player = 0;
}

bool game_is_playable (struct Game *game)
{
	if (get_player_num(game) >= 2)
		return true;
	else
		return false;
}

//TODO: always returns true
bool game_add (struct Game *game, const char * player_name)
{
	int player_num = get_player_num(game);
	if (player_num >= MAX_PLAYERS)
		return false;
	add_player_name(game, player_name);
	set_player_place(game, player_num, 0);
	set_player_purse(game, player_num, 0);
	set_in_penalty_box(game, player_num, false);
	set_player_num(game, player_num + 1);

	printf ("%s was added\n", player_name);
	printf ("%s is  number %d\n", player_name, get_player_num(game));

	return true;
}

void add_player_name(struct Game *game, const char * player_name)
{
	game->players[get_player_num(game)] = strdup (player_name);
}

void set_player_place(struct Game *game, int player_num, int place)
{
	game->places[player_num] = place;
}

void set_player_purse(struct Game *game, int player_num, int purse)
{
	game->purses[player_num] = purse;
}

void game_roll (struct Game *game, int roll)
{
	char * current_player_name = get_current_player_name(game);
	int player_place = get_player_place(game, get_current_player(game));
	int current_player = get_current_player(game);
	printf ("%s is the current player\n", current_player_name);
	printf ("They have rolled a %d\n", roll);

	if (get_in_penalty_box(game, current_player))
	{
		if (roll % 2 != 0)
		{
			game->is_getting_out_of_penalty_box = true;

			printf ("%s is getting out of the penalty box\n",
					current_player_name);

			set_player_place(game, current_player, player_place + roll);
			if (player_place > 11)
				set_player_place(game, current_player, player_place - 12);

			printf ("%s's new location is %d\n",
					current_player_name,
					player_place);
			printf ("The category is %s\n", get_category_name(current_category (game)));
			ask_question(current_category(game));
		}
		else
		{
			printf ("%s is not getting out of the penalty box\n",
					current_player_name);
			game->is_getting_out_of_penalty_box = false;
		}
	}
	else
	{
		set_player_place(game, current_player, player_place + roll);
		if (player_place > 11)
			set_player_place(game, current_player, player_place - 12);

		printf ("%s's new location is %d\n",
				current_player_name,
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
	int place = game->places[game->current_player];
	if ((place% 4) == 0)
		return game->pop;
	if ((place % 4) == 1)
		return game->science;
	if ((place % 4) == 2)
		return game->sports;
	return game->rock;
}

bool game_was_correctly_answered (struct Game *game)
{
	int current_player = get_current_player(game);
	char * current_player_name = get_current_player_name(game);
	if (get_in_penalty_box(game, current_player))
	{
		if (game->is_getting_out_of_penalty_box)
		{
			printf ("Answer was correct!!!!\n");
			set_player_purse(game, current_player, get_purse(game, current_player) + 1);
			printf ("%s now has %d Gold Coins.\n", current_player_name, get_purse(game, current_player));
			bool winner = did_player_win (game);
			set_current_player(game, current_player + 1);
			current_player = get_current_player(game);
			if (current_player == get_player_num(game))
				set_current_player(game, 0);
				current_player = get_current_player(game);

			return winner;
		}
		else
		{
			set_current_player(game, current_player + 1);
			current_player = get_current_player(game);
			if (current_player == get_player_num(game))
				set_current_player(game, 0);
				current_player = get_current_player(game);
			return true;
		}
	}
	else
	{

		printf ("Answer was corrent!!!!\n");
		set_player_purse(game, current_player, get_purse(game, current_player) + 1);
		printf ("%s now has %d Gold Coins.\n",
				current_player_name, get_purse(game, current_player));

		bool winner = did_player_win (game);
		set_current_player(game, current_player + 1);
		current_player = get_current_player(game);
		if (current_player == get_player_num(game))
			set_current_player(game, 0);
			current_player = get_current_player(game);

		return winner;
	}
}

bool game_wrong_answer (struct Game *game)
{
	printf ("Question was incorrectly answered\n");
	printf ("%s was sent to the penalty box\n",
			get_current_player_name(game));
	set_in_penalty_box(game, get_current_player(game), true);

	set_current_player(game, get_current_player(game) + 1);
	if (get_current_player(game) == get_player_num(game))
		set_current_player(game, 0);
	return true;
}


bool did_player_win (struct Game *game)
{
	return !(game->purses[game->current_player] == 6);
}
