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

