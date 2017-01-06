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
	set_question_category(question, Rock);
	ASSERT_EQ(Rock, get_question_category(question));
	set_question_category(question, Science);
	ASSERT_EQ(Science, get_question_category(question));
	set_question_category(question, Sports);
	ASSERT_EQ(Sports, get_question_category(question));
	set_question_category(question, Pop);
	ASSERT_EQ(Pop, get_question_category(question));
	free(question);
}
