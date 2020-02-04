CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

.PHONY:	all
all:	example coroutines_example

example:	example.c generator.h
	$(CC) $(CFLAGS) -o $@ $<

coroutines_example:	coroutines_example.c generator.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm -rf example coroutines_example
