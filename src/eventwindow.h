/**
 *  statusbar.c - folly
 *
 *  This module defines the game event window that displays story events and narration as the player interacts with the game
 *
 */

#ifndef EVENTWINDOW_H_
#define EVENTWINDOW_H_

#include "ncwindow.h"
#include "eventwindow.h"
#include "storyevent.h"


/**
 * Displays the game story events (i.e. event feed) in a section near the bottom of the game window
 */
void displayEventWindow(const WINDOW* window, StoryStack* storyEvents);


#endif // EVENTWINDOW_H_
