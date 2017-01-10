CFLAGS += -Wall
CTESTFLAGS = -isystem ~/git/googletest/googletest/include/ \
             -lpthread
GTEST_LIB = ~/git/googletest/build/googlemock/libgmock_main.a

SOURCES = game.c \
          Tests/game_test.c \
          question.c \
          Tests/question_test.c \
          category.c \
          Tests/category_test.c

all:
	gcc $(CFLAGS) game.c question.c category.c game_runner.c -o game

test: $(SOURCES) game.h question.h category.h
	g++ $(CFLAGS) $(CTESTFLAGS) $(SOURCES) $(GTEST_LIB) -o $@

clean:
	rm -f game test
