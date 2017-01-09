#include <gtest/gtest.h>
#include "../category.h"

TEST(category, first_case)
{
	struct Category *category = category_new("Rock");
	ASSERT_EQ(2, 2);
	free(category);
}
