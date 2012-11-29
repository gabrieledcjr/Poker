#include "graphics.h"

/**
 * Function name : ClearScreen ()
 * Date Created  : 27 November 2012
 * Usage         : ClearScreen ();
 * Definition    : This function clears the console screen
 * Pre-condition : Include Windows.h
 * Post-condition: n/a
 */
void ClearScreen (void) {
	system ("cls");
}

/**
 * Function name : Pause ()
 * Date Created  : 27 November 2012
 * Usage         : Pause (milliseconds);
 * Definition    : This function delays drawing on screen
 * Pre-condition : Include Windows.h
 * Post-condition: n/a
 */
void Pause (short milliseconds) {
	Sleep (milliseconds);
}

/**
 * Function name : MoveCursor (short x, short y)
 * Date Created  : 27 November 2012
 * Usage         : MoveCursor (x, y);
 * Definition    : This function moves cursor position to 
 *                 location x, y
 * Code source   : http://www.dreamincode.net/  
 * Subfolder     : forums/topic/92792-problem-with-gotoxy-in-
 *                 visual-studio-professional-2008/
 * Posted by     : bsaunders 
 * Pre-condition : Include Windows.h
 * Post-condition: n/a
 */
void MoveCursor(short x, short y) {
    HANDLE stdOutput;
    COORD pos;

    stdOutput = GetStdHandle (STD_OUTPUT_HANDLE);

    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition (stdOutput, pos);
}

/**
 * Function name : DrawBorder ()
 * Date Created  : 27 November 2012
 * Usage         : DrawBorder (upperX, upperY, lowerX, lowerY);
 * Definition    : This function draws a border on the screen
 * Pre-condition : n/a
 * Post-condition: n/a
 */
void DrawBorder (short upperLeftCornerX, short upperLeftCornerY,
				 short lowerRightCornerX, short lowerRightCornerY) {
	int x = upperLeftCornerX;
	int y = upperLeftCornerY;

	/* upper left border */
	MoveCursor (upperLeftCornerX, upperLeftCornerY);
	printf ("%c", 201); 

	/* upper right border */
	MoveCursor (lowerRightCornerX, upperLeftCornerY);
	printf ("%c", 187);

	/* lower left border */
	MoveCursor (upperLeftCornerX, lowerRightCornerY);
	printf ("%c", 200);

	/* lower right border */
	MoveCursor (lowerRightCornerX, lowerRightCornerY);
	printf ("%c", 188);

	/* top and bottom side border */
	while (x < lowerRightCornerX - 1)
	{
		MoveCursor (++x, upperLeftCornerY);
		printf ("%c", 205);
		MoveCursor (x, lowerRightCornerY);
		printf ("%c", 205);
	}

	/* left and right side border */
	while (y < lowerRightCornerY - 1)
	{
		MoveCursor (upperLeftCornerX, ++y);
		printf ("%c", 186);
		MoveCursor (lowerRightCornerX, y);
		printf ("%c", 186);
	}

	/* clears whats inside the border */
	for (y = upperLeftCornerY + 1; y < lowerRightCornerY; y++)
		for (x = upperLeftCornerX + 1; x < lowerRightCornerX; x++) {
			MoveCursor (x, y);
			printf (" ");
		}

	/* moves cursor to the upper left corner of the border */
	MoveCursor (upperLeftCornerX + 1, upperLeftCornerY + 1);
}

/**
 * Function name : DrawBorderFill ()
 * Date Created  : 28 November 2012
 * Usage         : DrawBorderFill (upperX, upperY, lowerX, lowerY, fill);
 * Definition    : This function draws a border on the screen and user
 *                 specifies type of fill
 * Pre-condition : n/a
 * Post-condition: n/a
 */
void DrawBorderFill (short upperLeftCornerX, short upperLeftCornerY,
				     short lowerRightCornerX, short lowerRightCornerY, 
					 char fill) {
	int x = upperLeftCornerX;
	int y = upperLeftCornerY;

	/* upper left border */
	MoveCursor (upperLeftCornerX, upperLeftCornerY);
	printf ("%c", 201); 

	/* upper right border */
	MoveCursor (lowerRightCornerX, upperLeftCornerY);
	printf ("%c", 187);

	/* lower left border */
	MoveCursor (upperLeftCornerX, lowerRightCornerY);
	printf ("%c", 200);

	/* lower right border */
	MoveCursor (lowerRightCornerX, lowerRightCornerY);
	printf ("%c", 188);

	/* top and bottom side border */
	while (x < lowerRightCornerX - 1)
	{
		MoveCursor (++x, upperLeftCornerY);
		printf ("%c", 205);
		MoveCursor (x, lowerRightCornerY);
		printf ("%c", 205);
	}

	/* left and right side border */
	while (y < lowerRightCornerY - 1)
	{
		MoveCursor (upperLeftCornerX, ++y);
		printf ("%c", 186);
		MoveCursor (lowerRightCornerX, y);
		printf ("%c", 186);
	}

	/* clears whats inside the border */
	for (y = upperLeftCornerY + 1; y < lowerRightCornerY; y++)
		for (x = upperLeftCornerX + 1; x < lowerRightCornerX; x++) {
			MoveCursor (x, y);
			printf ("%c", fill);
		}

	/* moves cursor to the upper left corner of the border */
	MoveCursor (upperLeftCornerX + 1, upperLeftCornerY + 1);
}