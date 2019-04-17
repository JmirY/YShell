CC = gcc
TARGET = yshell

$(TARGET) : ./src/main.o ./src/cmd_ls.o ./src/cmd_cd.o
	$(CC) -o $@ $^ 

main.o : ./src/main.c
	$(CC) -c -o $@ $^ 

cmd_ls.o : ./src/cmd_ls.c
	$(CC) -c -o $@ $^

cmd_cd.o : ./src/cmd_cd.c
	$(CC) -c -o $@ $^

clean :
	rm src/*.o
	rm $(TARGET)
