#include <gtest/gtest.h>
#include "../player.h"

TEST(player, get_player_name)
{
	struct Player *player = player_new("Alice");
	char *name = get_player_name(player);
	ASSERT_EQ(0, strcmp(name, "Alice"));
	ASSERT_NE(0, strcmp(name, "Ooops"));
	free(player);
}

TEST(player, get_set_player_place)
{
	struct Player *player = player_new("Alice");
	ASSERT_EQ(0, get_player_place(player));
	set_player_place(player, 12);
	ASSERT_EQ(12, get_player_place(player));
	free(player);
}
