#include <gtest/gtest.h>
#include "../category.h"

TEST(category, get_category_name)
{
	struct Category *category = category_new("Rock");
	char *name = get_category_name(category);
	ASSERT_EQ(0, strcmp(name, "Rock"));
	ASSERT_NE(0, strcmp(name, "Ooops"));
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

TEST(category, set_next_question)
{
	char * statement;
	struct Question *question = question_new();
	struct Category *category = category_new("Rock");

	set_next_question(category);
	question = get_next_question(category);
	statement = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Rock Question 1", statement));
	
	set_next_question(category);
	question = get_next_question(category);
	statement = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Rock Question 2", statement));
	free(category);
	free(question);
}

