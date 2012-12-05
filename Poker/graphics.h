/*==============================================================================
 | Filename: graphics.h                                                     
 | Programmer: Gabriel V. de a Cruz Jr.                                  
 | Class: CptS 121, Fall 2012 ; Lab Section 7                            
 | Programming Assignment 7: Poker (5-Card Draw)                    
 | Date: November 27, 2012                                                 
 +------------------------------------------------------------------------------
 | Description: This file is paired with graphics.c for the purpose of reusing 
 |              these functions for future programs. 
 +==============================================================================*/
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <Windows.h>

#define SCREEN_HEIGHT 24
#define SCREEN_WIDTH  79

void   ClearScreen     (void);
void   Pause           (short milliseconds);
void   MoveCursor      (short x, short y);
void   DrawBorder      (short upperLeftCornerX, short upperLeftCornerY,
				        short lowerRightCornerX, short lowerRightCornerY);
void   DrawBorderFill  (short upperLeftCornerX, short upperLeftCornerY,
				        short lowerRightCornerX, short lowerRightCornerY, char fill);

#endif