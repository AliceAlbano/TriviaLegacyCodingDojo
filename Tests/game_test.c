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

TEST(game, game_roll)
{
	struct Game *game = game_new();
	char name1[10] = "Alice";
	char name2[10] = "Bob";
	char name3[10] = "IA3";
	bool b;
	game_add(game, name1);
	game_add(game, name2);
	b = game_add(game, name3);
	EXPECT_EQ(b, true);
	game_roll(game, 2);
	game_correct_answer(game);
	ASSERT_EQ(1, get_current_player(game));

	game_roll(game, 1);
	game_wrong_answer(game);
	ASSERT_EQ(2, get_current_player(game));

	game_roll(game, 4);
	game_correct_answer(game);
	ASSERT_EQ(0, get_current_player(game));

	game_roll(game, 1);
	game_correct_answer(game);
	ASSERT_EQ(1, get_current_player(game));

	free(game);
}

