#include <string.h>

struct Question;

struct Question * question_new();
int get_question_number(struct Question *question);
char * get_question_category(struct Question *question);
char * get_question_statement(struct Question *question);
void set_question_number(struct Question *question, int number);
void set_question_category(struct Question *question, char c[30], int number);
