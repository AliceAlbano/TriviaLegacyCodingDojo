#include <gtest/gtest.h>
#include "../category.h"

TEST(category, get_category_name)
{
	struct Category *category = category_new("Rock");
	char *name = get_category_name(category);
	ASSERT_EQ(0, strcmp(name, "Rock"));
	free(category);
}

TEST(category, get_next_question)
{
	struct Question *question = question_new();
	struct Category *category = category_new("Rock");
	question = get_next_question(category);
	ASSERT_EQ(NULL, question);
	free(category);
	free(question);
}
