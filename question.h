#include <string.h>

#define cat1 "Rock"
#define cat2 "Pop"
#define cat3 "Science"
#define cat4 "Sports"

struct Question;

struct Question * question_new();
int get_question_number(struct Question *question);
char * get_question_category(struct Question *question);
char * get_question_statement(struct Question *question);
void set_question_number(struct Question *question, int number);
void set_question_category(struct Question *question, const char c[30], int number);
