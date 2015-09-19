/**
 *  storyevent.h - folly
 *
 *  This module defines events in the unfolding story. These are printed lines of texted displayed
 *  to let the player know what is happening in the game.
 *
 */

#ifndef STORYEVENT_H_
#define STORYEVENT_H_


/*typedef enum {
    INSTANT,
    FAST,
    SLOW
} PrintSpeed;*/


typedef struct _StoryEvent StoryEvent;
struct _StoryEvent {
    char* text;
    int isNew;

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
StoryEvent* initStoryEvent(char* text);

/**
 * Deletes story event and frees alocated memory
 */
void deleteStoryEvent(StoryEvent** eventRef);

/**
 * Initializes a new story stack
 */
StoryStack* initStoryStack(char* bossName);

/**
 * Deletes story stack and frees alocated memory
 */
void deleteStoryStack(StoryStack** stackRef);

/**
 * Push a story event on the stack
 */
void pushStoryStack(StoryStack* stack, StoryEvent* event);




#endif // STORYEVENT_H_
