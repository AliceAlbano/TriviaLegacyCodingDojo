all:
	gcc -Wall game.c game_runner.c -o game

clean:
	rm -f game
