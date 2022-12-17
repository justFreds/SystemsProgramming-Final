CC = gcc
program: src/tictactoe.c
	$(CC) src/tictacoe.c -lpaho-mqtt3c -o tictactoe