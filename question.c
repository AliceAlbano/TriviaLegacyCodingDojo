#include "question.h"
#include <stdlib.h>
#include <stdio.h>

struct Question
{
	int number;
	char category[15];
	char statement[30];
};

struct Question * question_new()
{
	struct Question *question;

	question = (struct Question *) malloc (sizeof (struct Question));
	return question;
}

void set_question_number(struct Question *question, int number)
{
	question->number = number;
}

void set_question_category(struct Question *question, char c[30], int number)
{
	strcpy(question->category, c);
	sprintf (question->statement, "%s Question %d", question->category, number);
}

int get_question_number(struct Question *question)
{
	return question->number;
}

void get_question_category(struct Question *question, char c[30])
{
	strcpy(c, question->category);
}

