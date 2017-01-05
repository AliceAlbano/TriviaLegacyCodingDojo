CFLAGS += -Wall
CTESTFLAGS = -isystem ~/git/googletest/googletest/include/ \
             -lpthread
GTEST_LIB = ~/git/googletest/build/googlemock/libgmock_main.a

SOURCES = game.c \
          Tests/game_test.c

all:
	gcc $(CFLAGS) game.c game_runner.c -o game

test: $(SOURCES) game.h
	g++ $(CFLAGS) $(CTESTFLAGS) $(SOURCES) $(GTEST_LIB) -o $@

clean:
	rm -f game test
