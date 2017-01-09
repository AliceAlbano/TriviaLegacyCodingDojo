#include "question.h"
#include <string.h>

struct Category;

struct Category * category_new(const char *name);
char * get_category_name(struct Category *category);
struct Question * get_next_question(struct Category *category);
