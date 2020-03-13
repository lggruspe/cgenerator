CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
CPPFLAGS = -I./include
TARGETS = iterators coroutines

.PHONY:	all
all:	$(TARGETS)

$(TARGETS):	%:	examples/%.c include/generator.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm -rf $(TARGETS)
