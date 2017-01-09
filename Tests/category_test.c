#include <gtest/gtest.h>
#include "../category.h"

TEST(category, get_category_name)
{
	struct Category *category = category_new("Rock");
	char *name = get_category_name(category);
	ASSERT_EQ(0, strcmp(name, "Rock"));
	free(category);
}
