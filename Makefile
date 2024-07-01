CFLAGS =gcc -Werror -Wextra -Wall
V = -std=c11

all: parse.h stack.h calculate.h
	$(CFLAGS) $(V) calculate.c stack.c parse.c graph.c -o graph 