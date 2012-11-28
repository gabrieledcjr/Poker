#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <Windows.h>

void   ClearScreen (void);
void   Pause       (short milliseconds);
void   MoveCursor  (short x, short y);
void   DrawBorder  (short upperLeftCornerX, short upperLeftCornerY,
				    short lowerRightCornerX, short lowerRightCornerY);

#endif