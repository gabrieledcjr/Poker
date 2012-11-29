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