enum category{Pop, Science, Sports, Rock};

struct Question;

struct Question * question_new();
int get_question_number(struct Question *question);
enum category get_question_category(struct Question *question, enum category c);
void set_question_number(struct Question *question, int number);
void set_question_category(struct Question *question, enum category c);
