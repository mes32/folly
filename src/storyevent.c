/**
 *  storyevent.c - folly
 *
 *  This module defines events in the unfolding story. These are printed lines of texted displayed
 *  to let the player know what is happening in the game.
 *
 */

#include <stdlib.h>
#include <string.h>

#include "debugfolly.h"
#include "storyevent.h"


/**
 * Initializes a new story event
 */
StoryEvent* initStoryEvent(char* text) {
    StoryEvent* newEvent = malloc(sizeof(StoryEvent));

    size_t len = strlen(text);
    newEvent->text = (char*)malloc(len + 1);
    strncpy(newEvent->text, text, len + 1);

    newEvent->isNew = 1;
    newEvent->eventBefore = NULL;
    newEvent->eventAfter = NULL;

    return newEvent;
}

/**
 * Deletes story event and frees alocated memory
 */
void deleteStoryEvent(StoryEvent** eventRef) {
    free((*eventRef)->text);
    free(*eventRef);
    *eventRef = NULL;
}

/**
 * Initializes a new story stack
 */
StoryStack* initStoryStack(char* bossName) {

    StoryStack* stack = malloc(sizeof(StoryStack));

    stack->head = NULL;
    stack->firstPrinted = NULL;
    stack->lastPrinted = NULL;

    // *** Shouldn't actually deal with composing story events at this level
    StoryEvent* storyOpen = initStoryEvent("In victory or death, your quest to defeat THE WRAITH ends in this place.");
    pushStoryStack(stack, storyOpen);

    storyOpen = initStoryEvent("Beneath the ruins of a small tower you find a maze of dark passageways.");
    pushStoryStack(stack, storyOpen);

    return stack;
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


