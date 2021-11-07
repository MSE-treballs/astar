SRCDIR = src/
OBJDIR = obj/
EXECUTS = astar astar.debug astar.profile

SOURCES = $(wildcard $(SRCDIR)*.c)
DEPENDS	= $(wildcard $(SRCDIR)*.h)
OBJECTS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SOURCES:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -pedantic -Ofast
LFLAGS = -lm
CDEBUGFLAGS = -D DEBUG -ggdb -g3 -O0
CPROFILEFLAGS = -pg

astar: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(DEPENDS)
	$(CC) $(CFLAGS) -c $< -o $@

release.tar.gz: $(SOURCES) $(DEPENDS) Makefile
	tar -czvf $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(EXECUTS) release.tar.gz *.out

.PHONY: all
all: $(EXECUTS)

.PHONY: debug
debug: astar.debug

astar.debug: $(SOURCES) $(DEPENDS)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -o $@ $(SOURCES) $(LFLAGS)

.PHONY: profile
profile: astar.profile

astar.profile: $(SOURCES) $(DEPENDS)
	$(CC) $(CFLAGS) $(CPROFILEFLAGS) -o $@ $(SOURCES) $(LFLAGS)

