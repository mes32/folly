/**
 *  eventwindow.c - folly
 *
 *  This module defines the game event window that displays story events and narration as the player interacts with the game
 *
 */

#include "debugfolly.h"
#include "eventwindow.h"
#include "mapcoordinate.h"
#include "ncwindow.h"
#include "storyevent.h"


static void printEvent(StoryEvent* event, int y);

/**
 * Displays the game story events (i.e. event feed) in a section near the bottom of the game window
 */
void displayEventWindow(WINDOW* window, StoryStack* storyEvents) {
    int maxY = 24;
    int maxX = 80;
    getmaxyx(window, maxY, maxX);

    for (int y=maxY-3; y <= maxY; y++) {
        for (int x=0; x <= maxX; x++) {
            MapCoordinate position = initMapCoordinate(x, y);
            printChar(' ', position, BLACK_ON_WHITE);
        }
    }

    // Print three most recent story events
    if (storyEvents != NULL) {
        StoryEvent* event0 = storyEvents->head;
        if (event0 != NULL) {
            printEvent(event0, maxY - 3);
            StoryEvent* event1 = event0->eventBefore;
            if (event1 != NULL) {
                printEvent(event1, maxY - 2);
                StoryEvent* event2 = event1->eventBefore;
                if (event2 != NULL) {
                    printEvent(event2, maxY - 1);
                }
            }
        }
    }
}

/**
 * Prints one story event in the story event section near the bottom of the game window
 */
static void printEvent(StoryEvent* event, int y) {
    char* text = event->text;

    int x = 0;
    char character = text[x];
    MapCoordinate position = initMapCoordinate(x, y);

    while (character != '\0') {
        printChar(character, position, BLACK_ON_WHITE);
        x++;
        character = text[x];
        position = initMapCoordinate(x, y);
    }
}





