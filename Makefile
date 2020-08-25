CC=gcc
CFLAGS=-I.
DEPS = parse.h y.tab.h
OBJ = y.tab.o lex.yy.o parse.o example.o
FLAGS = -g -Wall

default:all

all: example echo_server echo_client

lex.yy.c: lexer.l
	flex $^

y.tab.c: parser.y
	yacc -d $^

%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -c -o $@ $< $(CFLAGS)

example: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

echo_server:
	$(CC) echo_server.c -o echo_server -Wall -Werror

echo_client:
	$(CC) echo_client.c -o echo_client -Wall -Werror

clean:
	rm -f *~ *.o example lex.yy.c y.tab.c y.tab.h echo_server echo_client
