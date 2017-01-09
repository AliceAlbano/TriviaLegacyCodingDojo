#include <stdlib.h>
#include <string.h>
#include "category.h"

struct Category
{
	char name[20];
	Question * next_question;
};

//TODO: Test malloc return, and length of the name
struct Category * category_new(const char * name)
{
	struct Category *category;
	category = (struct Category *) malloc (sizeof (struct Category));
	strcpy(category->name, name);
	category->next_question = NULL;
	return category;
}
