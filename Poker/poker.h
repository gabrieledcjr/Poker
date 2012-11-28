#ifndef POKER_H
#define POKER_H

#include <stdio.h>

#define N_CARDS_ON_DECK  52     /* Number of cards on deck */
#define N_SUITS          4      /* Number of suits */
#define N_FACES          13     /* Number of card numbers per suit */
#define N_CARDS_ON_HAND  5      /* Number of cards dealt to player */
#define N_PLAYERS        2      /* Number of players including dealer */

typedef enum boolean {
	False, True
} Boolean;

typedef struct card {
	int faceIndex;
	int suitIndex;
	int cardNumber;
} Card;

#include "random.h"
#include "graphics.h"

void shuffle (int wDeck[][N_FACES]);
void deal (const int wDeck[][N_FACES], const char *wFace[], 
	       const char *wSuit[], Card hand[][N_CARDS_ON_HAND]);
void countSuitsAndFaces (int wSuit[][N_SUITS], int wFace[][N_FACES], 
	                     Card hand[][N_CARDS_ON_HAND]);

Boolean isOnePair (const int wFace[]);
Boolean isTwoPair (const int wFace[]);
Boolean isThreeOfAKind (const int wFace[]);
Boolean isFourOfAKind (const int wFace[]);
Boolean isFlush (const int wSuit[]);
Boolean isStraight (const int wFace[]);

#endif