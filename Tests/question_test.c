#include <gtest/gtest.h>
#include "../question.h"

TEST(question, get_set_question_number)
{
	int number;
	struct Question *question = question_new();
	set_question_number(question, 2);
	number = get_question_number(question);
	ASSERT_EQ(2, number);
	free(question);
}

TEST(question, get_set_question_category)
{
	struct Question *question = question_new();
	char *c;
	set_question_category(question, cat1, 1);
	c = get_question_category(question);
	ASSERT_EQ(0, strcmp(cat1, c));
	set_question_category(question, cat2, 1);
	c = get_question_category(question);
	ASSERT_EQ(0, strcmp(cat2, c));
	set_question_category(question, cat3, 1);
	c = get_question_category(question);
	ASSERT_EQ(0, strcmp(cat3, c));
	set_question_category(question, cat4, 1);
	c = get_question_category(question);
	ASSERT_EQ(0, strcmp(cat4, c));
	free(question);
}

TEST(question, get_statement)
{
	struct Question *question = question_new();
	char *c;
	set_question_category(question, cat1, 1);
	c = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Rock Question 1", c));
	set_question_category(question, cat2, 1);
	c = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Pop Question 1", c));
	set_question_category(question, cat3, 1);
	c = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Science Question 1", c));
	set_question_category(question, cat4, 1);
	c = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Sports Question 1", c));
}
