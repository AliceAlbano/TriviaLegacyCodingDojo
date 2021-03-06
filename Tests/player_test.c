#include <gtest/gtest.h>
#include "../player.h"

TEST(player, get_set_player_name)
{
	struct Player *player = player_new();
	set_player_name(player, "Alice");
	char *name = get_player_name(player);
	ASSERT_EQ(0, strcmp(name, "Alice"));
	ASSERT_NE(0, strcmp(name, "Ooops"));
	free(player);
}

TEST(player, get_set_player_id)
{
	struct Player *player = player_new();
	ASSERT_EQ(-1, get_player_id(player));
	set_player_id(player, 12);
	ASSERT_EQ(12, get_player_id(player));
	free(player);
}

TEST(player, get_set_player_place)
{
	struct Player *player = player_new();
	ASSERT_EQ(0, get_player_place(player));
	set_player_place(player, 12);
	ASSERT_EQ(12, get_player_place(player));
	free(player);
}

TEST(player, get_set_player_purse)
{
	struct Player *player = player_new();
	ASSERT_EQ(0, get_player_purse(player));
	set_player_purse(player, 12);
	ASSERT_EQ(12, get_player_purse(player));
	free(player);
}

TEST(player, get_set_in_penalty_box)
{
	struct Player *player = player_new();
	ASSERT_EQ(false, get_player_in_penalty_box(player));
	set_player_in_penalty_box(player, true);
	ASSERT_EQ(true, get_player_in_penalty_box(player));
	set_player_in_penalty_box(player, false);
	ASSERT_EQ(false, get_player_in_penalty_box(player));
	free(player);
}

TEST(player, move_player)
{
	struct Player *player = player_new();
	set_player_place(player, 3);
	move_player(player, 4);
	ASSERT_EQ(7, get_player_place(player));
	move_player(player, 5);
	ASSERT_EQ(0, get_player_place(player));
	move_player(player, 6);
	ASSERT_EQ(6, get_player_place(player));
	move_player(player, 5);
	ASSERT_EQ(11, get_player_place(player));
	move_player(player, 3);
	ASSERT_EQ(2, get_player_place(player));
	free(player);
}

TEST(player, correct_answer)
{
	struct Player *player = player_new();
	set_player_name(player, "Alice");
	correct_answer(player);
	ASSERT_EQ(1, get_player_purse(player));
	correct_answer(player);
	ASSERT_EQ(2, get_player_purse(player));
	correct_answer(player);
	ASSERT_EQ(3, get_player_purse(player));
	free(player);
}

TEST(player, set_player_in_penalty_box)
{
	struct Player *player = player_new();
	bool b;
	set_player_name(player, "Alice");
	set_player_in_penalty_box(player, true);
	b = get_out_of_penalty_box(player, 2);
	ASSERT_EQ(false, b);
	ASSERT_EQ(true, get_player_in_penalty_box(player));
	b = get_out_of_penalty_box(player, 1);
	ASSERT_EQ(true, b);
	ASSERT_EQ(false, get_player_in_penalty_box(player));
	free(player);
}
