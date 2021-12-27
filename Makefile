.PHONY: all test clean coverage bear

CC = clang
CFLAGS = -Wall -Wextra -Og -g3 -std=c11 -pedantic -Wimplicit-fallthrough

PROG = x
SRCS = test.c string_to_double.c double_to_string.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
GCNO = $(SRCS:.c=.gcno)
GCDA = $(SRCS:.c=.gcda)
GCOV = $(SRCS:.c=.c.gcov)
LDFLAGS = -fuse-ld=lld -lm

all: $(PROG)

coverage: CFLAGS += --coverage
coverage: all
	./$(PROG)
	for gcda in $(GCDA); do llvm-cov gcov $$gcda; done

bear: clean
	bear -- $(MAKE) all

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

clean:
	rm -f $(PROG) $(OBJS) $(DEPS) $(GCNO) $(GCDA) $(GCOV) \
		compile_commands.json

test: all
	./$(PROG)

-include $(DEPS)
