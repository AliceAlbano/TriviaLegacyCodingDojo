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

