CFLAGS += -Wall
CTESTFLAGS = -isystem ~/git/googletest/googletest/include/ \
             -lpthread
GTEST_LIB = ~/git/googletest/build/googlemock/libgmock_main.a

all:
	gcc $(CFLAGS) game.c game_runner.c -o game

test: Tests/simple_test.c
	g++ $(CFLAGS) $(CTESTFLAGS) $^ $(GTEST_LIB) -o $@

clean:
	rm -f game
