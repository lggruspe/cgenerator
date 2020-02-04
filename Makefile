CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

example:	example.c generator.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm -rf example
