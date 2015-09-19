/**
 *  statusbar.c - folly
 *
 *  This module defines a status bar displayed at the top of the game window to summarize the state of the player's character.
 *
 */

#ifndef STATUSBAR_H_
#define STATUSBAR_H_

#include "ncwindow.h"
#include "playercharacter.h"

/**
 *  Displays the status bar at the top of the game window. This status bar summarizes the state of the player character.
 */
void displayStatusBar(const WINDOW* window, const PlayerCharacter* player);


#endif // STATUSBAR_H_
