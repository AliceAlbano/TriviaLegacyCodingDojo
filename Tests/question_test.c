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
	char c1[30] = "Rock";
	char c2[30] = "Pop";
	char c3[30] = "Science";
	char c4[30] = "Sports";
	set_question_category(question, c1, 1);
	c = get_question_category(question);
	ASSERT_EQ(0, strcmp(c1, c));
	set_question_category(question, c2, 1);
	c = get_question_category(question);
	ASSERT_EQ(0, strcmp(c2, c));
	set_question_category(question, c3, 1);
	c = get_question_category(question);
	ASSERT_EQ(0, strcmp(c3, c));
	set_question_category(question, c4, 1);
	c = get_question_category(question);
	ASSERT_EQ(0, strcmp(c4, c));
	free(question);
}

TEST(question, get_statement)
{
	struct Question *question = question_new();
	char *c;
	char c1[30] = "Rock";
	char c2[30] = "Pop";
	char c3[30] = "Science";
	char c4[30] = "Sports";
	set_question_category(question, c1, 1);
	c = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Rock Question 1", c));
	set_question_category(question, c2, 1);
	c = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Pop Question 1", c));
	set_question_category(question, c3, 1);
	c = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Science Question 1", c));
	set_question_category(question, c4, 1);
	c = get_question_statement(question);
	ASSERT_EQ(0, strcmp("Sports Question 1", c));
}
