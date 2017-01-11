#include <gtest/gtest.h>
#include "../game.h"
#include <stdbool.h>


TEST(game, game_add)
{
	struct Game *game = game_new();
	int i = get_available_places(game);
	char name[10] = "Alice";
	bool b;
	int j;
	for (j = 0; j < i; j++)
	{
		b = game_add(game, name);
		ASSERT_EQ(b, true);
		ASSERT_EQ(j + 1, get_player_num(game));
	}
	b = game_add(game, name);
	ASSERT_EQ(b, false);
	ASSERT_EQ(j, get_player_num(game));
	free(game);
}

