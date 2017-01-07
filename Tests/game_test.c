#include <gtest/gtest.h>
#include "../game.h"
#include <stdbool.h>


TEST(game_add, first_player)
{
	struct Game *game = game_new();
	bool is_added;

	is_added = game_add(game, "First Player");
	ASSERT_EQ(true, is_added);
	ASSERT_EQ(get_player_num(game), 1);
	ASSERT_EQ(get_place(game, 0), 0);
	ASSERT_EQ(get_purse(game, 0), 0);
	ASSERT_EQ(get_in_penalty_box(game, 0), false);
	free(game);
}

