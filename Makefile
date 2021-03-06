#
#  Makefile - folly
#
#  This is the main makefile for building the C-language project named 'folly'
#


CC=gcc
CFLAGS=-Wall -g -std=c99 -O3
#CFLAGS=-Wall -Wextra -g -std=c99 -O3
LDFLAGS=-lncurses

OBJECT_FILES= \
    bin/debugfolly.o \
    bin/titlescreen.o \
    bin/helpscreen.o \
    bin/game.o \
    bin/ncwindow.o \
    bin/map.o \
    bin/mapcoordinate.o \
    bin/maptile.o \
    bin/playercharacter.o \
    bin/statusbar.o \
    bin/storyevent.o \
    bin/enemies.o \
    bin/eventwindow.o \
    bin/randfolly.o \
    bin/bresenhamline.o \

all: start_game

bin/%.o: src/%.c src/%.h Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

start_game: src/main.c $(OBJECT_FILES) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o start_game src/main.c $(OBJECT_FILES)

clean:
	rm -f start_game $(OBJECT_FILES)

