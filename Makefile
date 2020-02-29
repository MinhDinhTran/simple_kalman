LIBS = "-lm"
CC = gcc

matrix.o: matrix.c matrix.h
	$(CC) -c matrix.c

kalman.o: kalman.c kalman.h
	$(CC) -c kalman.c

main.0: main.c util.h
	$(CC) $(LIBS) -o $@S

kalman: main.o kalman.o matrix.o
	$(CC) main.o factorial.o hello.o -o kalman

clean:
	-rm *.o

