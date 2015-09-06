/**
 *  storyevent.c - folly
 *
 *  This module defines events in the unfolding story. These are printed lines of texted displayed
 *  to let the player know what is happening in the game.
 *
 */

#include <stdlib.h>
#include <string.h>

#include "storyevent.h"
/*#include "mapcoordinate.h"
#include "ncwindow.h"*/


/**
 * Initializes a new story event
 */
void initStoryEvent(StoryEvent** eventRef, char* text) {
    *eventRef = (StoryEvent*)malloc(sizeof(StoryEvent));
    StoryEvent* newEvent = *eventRef;

    size_t len = strlen(text);
    newEvent->text = (char*)malloc(len + 1);
    strncpy(newEvent->text, text, len + 1);

    newEvent->isNew = 1;
    newEvent->isError = 0;
    newEvent->eventBefore = NULL;
    newEvent->eventAfter = NULL;
}

/**
 * Deletes story event and frees alocated memory
 */
void deleteStoryEvent(StoryEvent** eventRef) {
    // *** Need to free text field correctly
    free((*eventRef)->text);
    free(*eventRef);
    *eventRef = NULL;
}

/**
 * Initializes a new error event
 */
void initErrorEvent(StoryEvent** eventRef, char* text) {
    *eventRef = (StoryEvent*)malloc(sizeof(StoryEvent));
    StoryEvent* newEvent = *eventRef;

    size_t len = strlen(text);
    newEvent->text = (char*)malloc(len + 1);
    strncpy(newEvent->text, text, len + 1);

    newEvent->isNew = 1;
    newEvent->isError = 1;
    newEvent->eventBefore = NULL;
    newEvent->eventAfter = NULL;
}

/**
 * Deletes error event and frees alocated memory
 */
void deleteErrorEvent(StoryEvent** eventRef) {
    deleteStoryEvent(eventRef);
}

/**
 * Initializes a new story stack
 */
void initStoryStack(StoryStack** stackRef) {
    *stackRef = (StoryStack*)malloc(sizeof(StoryStack));
    StoryStack* newStack = *stackRef;

    newStack->head = NULL;
    newStack->firstPrinted = NULL;
    newStack->lastPrinted = NULL;
}

/**
 * Deletes story stack and frees alocated memory
 */
void deleteStoryStack(StoryStack** stackRef) {

    StoryStack* stack = *stackRef;

    while (stack->head != NULL) {
        StoryEvent* oldHead = stack->head;
        stack->head = oldHead->eventBefore;
        deleteStoryEvent(&oldHead);
    }

    free(*stackRef);
    *stackRef = NULL;
}

/**
 * Push a story event on the stack
 */
void pushStoryStack(StoryStack* stack, StoryEvent* event) {
    StoryEvent* oldHead = stack->head;
    event->eventBefore = oldHead;
    if (oldHead != NULL) {
        oldHead->eventAfter = event;
    }
    stack->head = event;
}


