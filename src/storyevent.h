/**
 *  storyevent.h - folly
 *
 *  This module defines events in the unfolding story. These are printed lines of texted displayed
 *  to let the player know what is happening in the game.
 *
 */

#ifndef STORYEVENT_H_
#define STORYEVENT_H_

//#include "ncwindow.h"
//#include "eventwindow.h"

/*typedef enum {
    INSTANT,
    FAST,
    SLOW
} PrintSpeed;*/

typedef struct _StoryEvent StoryEvent;
struct _StoryEvent {
    char* text;
    int isNew;
    int isError;
    //PrintSpeed speed;

    StoryEvent* eventBefore;
    StoryEvent* eventAfter;
};

typedef struct _StoryStack {
    StoryEvent* head;
    StoryEvent* firstPrinted;
    StoryEvent* lastPrinted;
} StoryStack;

/**
 * Initializes a new story event
 */
void initStoryEvent(StoryEvent** eventRef, char* text);

/**
 * Deletes story event and frees alocated memory
 */
void deleteStoryEvent(StoryEvent** eventRef);

/**
 * Initializes a new error event
 */
void initErrorEvent(StoryEvent** eventRef, char* text);

/**
 * Deletes error event and frees alocated memory
 */
void deleteErrorEvent(StoryEvent** eventRef);

/**
 * Initializes a new story stack
 */
void initStoryStack(StoryStack** stackRef);

/**
 * Deletes story stack and frees alocated memory
 */
void deleteStoryStack(StoryStack** stackRef);

/**
 * Push a story event on the stack
 */
void pushStoryStack(StoryStack* stack, StoryEvent* event);




#endif // STORYEVENT_H_
