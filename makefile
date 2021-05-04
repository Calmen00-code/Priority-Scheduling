CC = gcc
CFLAGS = -Werror -Wall -ansi -pedantic -g
OBJ = main.o file.o sort.o schedule.o
EXEC = main

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c header.h file.h Task.h sort.h schedule.h
	$(CC) $(CFLAGS) -c main.c

file.o : file.c file.h header.h Task.h
	$(CC) $(CFLAGS) -c file.c

sort.o : sort.c Task.h
	$(CC) $(CFLAGS) -c sort.c

schedule.o : schedule.c schedule.h Task.h header.h
	$(CC) $(CFLAGS) -c schedule.c

clean:
	rm -f $(EXEC) $(OBJ)
