#include "question.h"
#include <stdlib.h>


struct Question
{
	int number;
	enum category c;
};

struct Question * question_new()
{
	struct Question *question;

	question = (struct Question *) malloc (sizeof (struct Question));
	if (question == NULL)
		return question;
	question->number = -1;
	question->c = Rock;
	return question;
}

void set_question_number(struct Question *question, int number)
{
	question->number = number;
}

void set_question_category(struct Question *question, enum category c)
{
	question->c = c;
}

int get_question_number(struct Question *question)
{
	return question->number;
}

enum category get_question_category(struct Question *question)
{
	return question->c;
}
