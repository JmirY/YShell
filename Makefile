CC = gcc
TARGET = yshell

$(TARGET) : ./src/main.o ./src/command_ls.o
	$(CC) -o $@ $^ 

main.o : ./src/main.c
	$(CC) -c -o $@ $^ 

command_ls.o : ./src/command_ls.c
	$(CC) -c -o $@ $^
