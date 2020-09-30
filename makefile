CC = gcc
LIBS = -lpthread -lcurses
SOURCE = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, ${SOURCE})
CFLAGS = -Wall -std=gnu11 -Ofast
snake: ${OBJS}
	${CC} -o snake ${OBJS} ${LIBS}
clean:
	rm -f snake ${OBJS}