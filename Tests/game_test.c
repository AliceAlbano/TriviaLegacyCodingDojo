#include <gtest/gtest.h>
#include "../game.h"
#include <stdbool.h>


TEST(game_add, first_player)
{
	struct Game *game = game_new();
	ASSERT_EQ(0, 0);
	free(game);
}

