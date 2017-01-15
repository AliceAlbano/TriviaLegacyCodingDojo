#include <stdlib.h>
#include "category.h"

struct Category
{
	char name[20];
	struct Question * next_question;
	int current_question ;
};

struct Category * category_new(const char * name)
{
	struct Category *category;
	category = (struct Category *) malloc(sizeof(struct Category));
	if (category == NULL)
		return NULL;
	strcpy(category->name, name);
	category->next_question = NULL;
	category->current_question = 0;
	return category;
}

char * get_category_name(struct Category *category)
{
	return category->name;
}

struct Question * get_next_question(struct Category *category)
{
	return category->next_question;
}

void set_next_question(struct Category *category)
{
	category->current_question ++;
	struct Question *question = question_new();
	set_question_category(question, category->name, category->current_question);
	category->next_question = question;
}
