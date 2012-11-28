#include "poker.h"

/* shuffle cards in deck */

void shuffle (int wDeck[][N_FACES]) {
	short row    = 0;   /* row number */
	short column = 0;   /* column number */
	short card   = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 0; card < N_CARDS_ON_DECK; card++) {
		/* choose new random location until unoccupied slot found */
		do {
			row = RandomInteger (0, N_SUITS - 1);
			column = RandomInteger (0, N_FACES - 1);
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card + 1;
	}
}

/* deal cards in deck */
void deal (const int wDeck[][N_FACES], const char *wFace[], 
	       const char *wSuit[], Card hand[][N_CARDS_ON_HAND]) {
	short row    = 0;   /* row number */
	short column = 0;   /* column number */
	short player = 0;   /* player number */
	short card   = 0;   /* card counter */
	short i      = 0;   /* count number of cards on hand for each player */
	
	/* deal each of the 52 cards */
	for (i = 0, card = 1; i < N_CARDS_ON_HAND; i++, card++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row < N_SUITS; row++) {

			/* loop through columns of wDeck for current row */
			for (column = 0; column < N_FACES; column++) {

				/* if slot contains current card, display card */
				if (wDeck[row][column] == card) {
					//printf ("Player %d: %5s of %-8s\n", player+1, wFace[column], wSuit[row]);
					printf ("%5s of %-8s%c", wFace[column], wSuit[row], player == N_PLAYERS - 1 ? '\n' : '\t');
					hand[player][i].suitIndex = row;
					hand[player][i].faceIndex = column;
					hand[player][i].cardNumber = card;
				}
			}
		}

		player++;

		/* resets player to 0 when each player got a card */
		if (player == N_PLAYERS) player = 0;

		/* deals one card at a time per player */
		if (player != 0) i--;
	}
}

void countSuitsAndFaces (int wSuit[][N_SUITS], int wFace[][N_FACES], 
	                     Card hand[][N_CARDS_ON_HAND]) {
	int i = 0, j = 0;

	for (i = 0; i < N_PLAYERS; i++) 
		for (j = 0; j < N_CARDS_ON_HAND; j++) {
			wSuit[i][hand[i][j].suitIndex]++;
			wFace[i][hand[i][j].faceIndex]++;
		}
}

/**
 * (b) (5 pts) Write a function to determine if the hand contains a pair.
 */
Boolean isOnePair (const int wFace[]) {
	int i = 0, count = 0;
	Boolean result = False;
	
	/* loops through all 13 card numbers */
	/* 4 cards did not form any pair */
	while (i < N_FACES && count != 4) {

		/* 2 or greater means there is a pair */
		if (wFace[i] >= 2) {
			result = True;
			break;
		}

		/* counts total card located */
		count += wFace[i++];
	}

	return result;
}

/**
 * (c) (5 pts) Write a function to determine if the hand contains two pairs.
 */
Boolean isTwoPair (const int wFace[]) {
	int i = 0, count = 0;
	Boolean result = False;
	
	/* loops through all 13 card numbers */
	while (i < N_FACES) {

		/* 4 or greater means no two pair exists */
		if (wFace[i] >= 4) break;

		/* finds first one pair less than 4 */
		/* 3 cards did not form any pair */
		if (wFace[i] >= 2 && count != 3) {
			i++;
			/* loops through all 13 card numbers*/
			/* 4 cards did not form two pair */
			while (i < N_FACES && count != 4) {
				/* 2 or greater means there is 2nd pair */
				if (wFace[i] >= 2) {
					result = True;
					break;
				}

				/* counts total card located */
				count += wFace[i++];
			}
			break;
		}

		/* counts total card located */
		count += wFace[i++];
		
	}

	return result;
}

/**
 * (d) (5 pts) Write a function to determine if the hand contains three of a 
 *     kind (e.g. three jacks).
 */
Boolean isThreeOfAKind (const int wFace[]) {
	int i = 0, count = 0;
	Boolean result = False;
	
	/* loops through all 13 card numbers */
	/* 3 cards did not form three of a kind */
	while (i < N_FACES && count != 3) {
		/* 3 or greater means there is a three of a kind */
		if (wFace[i] >= 3) {
			result = True;
			break;
		}

		/* counts total card located */
		count += wFace[i++];
	}

	return result;
}

/**
 * (e) (5 pts) Write a function to determine if the hand contains four of a 
 *     kind (e.g. four aces).
 */
Boolean isFourOfAKind (const int wFace[]) {
	int i = 0, count = 0;
	Boolean result = False;
	
	/* loops through all 13 card numbers */
	/* 4 cards did not form four of a kind */
	while (i < N_FACES && count != 4) {
		/* 4 or greater means there is a four of a kind */
		if (wFace[i] >= 4) {
			result = True;
			break;
		}

		/* counts total card located */
		count += wFace[i++];
	}

	return result;
}

/**
 * (f) (5 pts) Write a function to determine if the hand contains a flush 
 *     (i.e. all five cards of the same suit).
 */
Boolean isFlush (const int wSuit[]) {
	int i = 0;
	Boolean result = True;

	/* loops through all 4 types of suits */
	while (i < N_SUITS) {
		/* 1 to 4 cards with the same suit means is not a flush */
		if (wSuit[i] > 0 && wSuit[i] < 5) {
			result = False;
			break;
		}
		i++;
	}

	return result;
}

/**
 * (g) (5 pts) Write a function to determine if the hand contains a straight 
 *     (i.e. five cards of consecutive face values).
 */
Boolean isStraight (const int wFace[]) {
	int i = 0, j = 0;
	Boolean result = False;

	/* loops through all faces */
	/* a face with a minimum of a pair is automatically not a straight */
	while (i < N_FACES && wFace[i] < 2) {
		/* first face with 1 located */
		if (wFace[i] == 1) {
			/* check that there is enough to form a straight */
			if ((i + 4) < N_FACES) {
				result = True;
				/* loop to check that it forms a straight */
				for (j = i + 1; j < i + 4; j++) {
					if (wFace[j] != 1) {
						result = False;
						break;
					}
				}
			} 

			/* check that is starts on an Ace */
			/* check that the previous loop didn't pass the first test */
			/* check that result is False */
			if (i == 0 && j == i + 1 && result == False) {
				result = True;
				/* loop to check that it forms a straight */
				for (j = N_FACES - 4; j < N_FACES; j++) {
					if (wFace[j] != 1) {
						result = False;
						break;
					}
				}
			}

			break;
		}
		i++;
	}

	return result;
}