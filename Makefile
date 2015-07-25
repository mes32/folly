#
# Makefile
#
# Builds the C project named folly
#


#ProjectDir
#    bin\       -- compiled code 
#    src\       -- source code .c and .h 
#         submodule\  -- a potential submodule
#    res\       -- other resources maps or savefiles
#    Makefile   -- makefile script
#    README.md  -- descriptive document

#/src    - source files (test files are within a package 'test' here, or 'test' subpackage of what is being tested)
#/lib    - required libraries
#/doc    - text documentation and development notes
#/build  - where we build (each separate build item within a subfolder here)
#/conf   - configurations (each config, production, test, developer, etc gets a folder in here, and when building Jars and Wars the correct set is copied across)
#/extras - other stuff
#/extras/resources - resources that should be included within generated Jars, e.g., icons

CC=gcc
CFLAGS=-Wall -g
CFLAGS=-Wall -g -ansi -std=c89 -std=c99 -O3
LDFLAGS=-lncurses

OBJECT_FILES= \
    bin/game.o \
    bin/ncwindow.o \

all: start_game

bin/%.o: src/%.c src/%.h Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

start_game: src/main.c $(OBJECT_FILES) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o start_game src/main.c $(OBJECT_FILES)

clean:
	rm -f start_game $(OBJECT_FILES)

