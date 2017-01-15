#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "game.h"

static bool not_a_winner;

int main()
{
	struct Game *a_game = game_new();
	srand((unsigned)time(0));

	game_add(a_game, "Chet");
	game_add(a_game, "Pat");
	game_add(a_game, "Sue");

	if (game_is_playable(a_game) == 0)
		return EXIT_FAILURE;
	do
	{
		game_roll(a_game, rand() % 5 + 1);

		if (rand() % 9 == 7)
		{
			not_a_winner = game_wrong_answer(a_game);
		}
		else
		{
			not_a_winner = game_correct_answer(a_game);
		}
	}
	while (not_a_winner);
	return EXIT_SUCCESS;
}
