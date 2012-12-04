#include "poker.h"

/* initializing variables */
void init (int deckOfCard[][N_FACES]) {
	int i = 0, j = 0;

	for (i = 0; i < N_SUITS; i++)
		for (j = 0; j < N_FACES; j++)
			deckOfCard[i][j] = 0;
}

void resetSuitCounter (int suit[][N_SUITS]) {
	int i = 0, j = 0;

	for (i = 0; i < N_PLAYERS; i++) 
		for (j = 0; j < N_SUITS; j++)
			suit[i][j] = 0;
}

void resetFaceCounter (int face[][N_FACES]) {
	int i = 0, j = 0;

	for (i = 0; i < N_PLAYERS; i++)
		for (j = 0; j < N_FACES; j++)
			face[i][j] = 0;
}

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
					//printf ("%5s of %-8s%c", wFace[column], wSuit[row], player == N_PLAYERS - 1 ? '\n' : '\t');
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

void sortHand (Card hand[]) {
	int i = 0, j = 0;
	Card temp;

	for (i = 0; i < N_CARDS_ON_HAND; i++) {
		for (j = i + 1; j < N_CARDS_ON_HAND; j++) {
			if (hand[j].faceIndex > hand[i].faceIndex) {
				temp = hand[j];
				hand[j] = hand[i];
				hand[i] = temp;
			}
		}
	}
}

void countSuitsAndFaces (int wSuit[][N_SUITS], int wFace[][N_FACES], 
	                     Card hand[][N_CARDS_ON_HAND]) {
	int i = 0, j = 0;

	/* loops through number of players including dealer */
	for (i = 0; i < N_PLAYERS; i++) 
		/* loops through number of cards per hand */
		for (j = 0; j < N_CARDS_ON_HAND; j++) {
			/* count number of similar suits */
			wSuit[i][hand[i][j].suitIndex]++;
			/* count number of similar faces */
			wFace[i][hand[i][j].faceIndex]++;
		}
}

void drawPlayerCard (short x, short y, short suit, short face) {
	DrawBorder (x, y, x + 11, y + 11);

	drawFaceCharacter (face);
	MoveCursor (face == TEN ? x + 9 : x + 10, y + 10);
	drawFaceCharacter (face);

	drawSuitSymbol (x + 1, y + 3, suit);
}


void drawFaceCharacter (short type) {
	switch (type) {
		case ACE:   printf("A");  break;
		case DEUCE: printf("2");  break;
		case THREE: printf("3");  break;
		case FOUR:  printf("4");  break;
		case FIVE:  printf("5");  break;
		case SIX:   printf("6");  break;
		case SEVEN: printf("7");  break;
		case EIGHT: printf("8");  break;
		case NINE:  printf("9");  break;
		case TEN:   printf("10"); break;
		case JACK:  printf("J");  break;
		case QUEEN: printf("Q");  break;
		case KING:  printf("K");  break;
	}
}

void drawSuitCharacter (short type) {
	switch (type) {
		case HEARTS:   printf("H");  break;
		case DIAMONDS: printf("D");  break;
		case CLUBS:    printf("C");  break;
		case SPADES:   printf("S");  break;
	}
}

void drawSuitSymbol (short x, short y, short type) {
	switch (type) {
		case HEARTS:
			MoveCursor (x, y);
			printf (" **   ** ");
			MoveCursor (x, y + 1);
			printf ("**** ****");
			MoveCursor (x, y + 2);
			printf ("*********");
			MoveCursor (x, y + 3);
			printf ("*********");
			MoveCursor (x, y + 4);
			printf (" ******* ");
			MoveCursor (x, y + 5);
			printf ("  *****  ");
			MoveCursor (x, y + 6);
			printf ("    *    ");
			break;
		case DIAMONDS:
			MoveCursor (x, y);
			printf ("    *    ");
			MoveCursor (x, y + 1);
			printf ("   ***   ");
			MoveCursor (x, y + 2);
			printf ("  *****  ");
			MoveCursor (x, y + 3);
			printf (" ******* ");
			MoveCursor (x, y + 4);
			printf ("  *****  ");
			MoveCursor (x, y + 5);
			printf ("   ***   ");
			MoveCursor (x, y + 6);
			printf ("    *    ");
			break;
		case CLUBS:
			MoveCursor (x, y);
			printf ("   ***   ");
			MoveCursor (x, y + 1);
			printf ("  *****  ");
			MoveCursor (x, y + 2);
			printf ("    *    ");
			MoveCursor (x, y + 3);
			printf (" ******* ");
			MoveCursor (x, y + 4);
			printf ("*********");
			MoveCursor (x, y + 5);
			printf (" ** * ** ");
			MoveCursor (x, y + 6);
			printf ("    *    ");
			break;
		case SPADES:
			MoveCursor (x, y);
			printf ("    *    ");
			MoveCursor (x, y + 1);
			printf ("   ***   ");
			MoveCursor (x, y + 2);
			printf (" ******* ");
			MoveCursor (x, y + 3);
			printf ("*********");
			MoveCursor (x, y + 4);
			printf ("**  *  **");
			MoveCursor (x, y + 5);
			printf ("    *    "); 
			MoveCursor (x, y + 6);
			printf ("   ***   ");
			break;
	}
}

void drawPlayerHand (Card playersHand []) {
	short i = 0;
	short x = 1;

	MoveCursor (1, 1);
	printf ("PLAYER'S HAND");

	for (i = 0; i < N_CARDS_ON_HAND; i++) {
		drawPlayerCard (x, 2, playersHand[i].suitIndex, playersHand[i].faceIndex);
		x += 12;
	}
}

void drawDealerCard (short x, short y, short suit, short face, Boolean showCard) {
	DrawBorderFill (x, y, x + 5, y + 6, showCard ? ' ' : '+');
	
	if (showCard) {
		drawFaceCharacter (face);
		printf ("-");
		drawSuitCharacter (suit);
	}
}

void drawDealerHand (Card playersHand [], Boolean showCard) {
	short i = 0;
	short x = 2;

	/* draws lower border for dealer */
	DrawBorder (1, 14, 32, 23);
	printf ("DEALER'S HAND");

	for (i = 0; i < N_CARDS_ON_HAND; i++) {
		drawDealerCard (x, 16, playersHand[i].suitIndex, playersHand[i].faceIndex, showCard);
		x += 6;
	}
}

void drawOutputBox (const char *message) {
	DrawBorder (33, 14, 78, 23);
	printf ("%s", message);
}

void drawMenu (void) {
	DrawBorder (61, 1, 78, 13);
	printf ("      MENU");
	MoveCursor (62, 4);
	printf ("[ ] PLAY");
	MoveCursor (62, 5);
	printf ("[ ] SWAP CARDS");
	MoveCursor (62, 6);
	printf ("[ ] STATS");
	MoveCursor (62, 7);
	printf ("[ ] QUIT GAME");
}


void playDealerHand (Card playersHand[][N_CARDS_ON_HAND], int wDeck[][N_FACES], 
	                 short *numDealtCard, int wFace[][N_FACES], int wSuit[][N_SUITS]) {
	
	switch (checkHandCategory (wFace[0], wSuit[0])) {

		case ROYAL_FLUSH:

		case STRAIGHT_FLUSH:

		case FOUR_OF_A_KIND:

		case FULL_HOUSE:

		case FLUSH:

		case STRAIGHT:

		case THREE_OF_A_KIND:

		case TWO_PAIR:

		case ONE_PAIR:

		case HIGH_CARD:

	}
}

short selectMenuItem (void) {
	short cursorX = MENU_X,
          cursorY = MENU_Y,
          menuItem = PLAY_GAME;
	char ch = '\0';

	MoveCursor (cursorX, cursorY);
	printf ("%c", CURSOR_SYMBOL);
	MoveCursor (cursorX, cursorY);

	do {
		ch = getch ();
		switch(ch) { 
			case ARROW_KEY_UP: 
				/* UP arrow key is pressed */
				if (cursorY == MENU_Y) {
					MoveCursor (cursorX, cursorY);
					printf (" ");
					cursorY = MENU_Y + 3;
					MoveCursor (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					MoveCursor (cursorX, cursorY);

					menuItem = QUIT_GAME;
				} else if (cursorY > MENU_Y) {
					MoveCursor (cursorX, cursorY);
					printf (" ");
					cursorY--;
					MoveCursor (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					MoveCursor (cursorX, cursorY);

					menuItem--;
				} 		
				break;

			case ARROW_KEY_DOWN: 
				/* DOWN arrow key is pressed */
				if (cursorY < MENU_Y + 3) {
					MoveCursor (cursorX, cursorY);
					printf (" ");
					cursorY++;
					MoveCursor (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					MoveCursor (cursorX, cursorY);

					menuItem++;
				} else if (cursorY == MENU_Y + 3) {
					MoveCursor (cursorX, cursorY);
					printf (" ");
					cursorY = MENU_Y;
					MoveCursor (cursorX, cursorY);
					printf ("%c", CURSOR_SYMBOL);
					MoveCursor (cursorX, cursorY);

					menuItem = PLAY_GAME;
				}
				break; 
		}
	} while (ch != 13);

	return menuItem;
}

short checkHandCategory (const int wFace[], const int wSuit[]) {
	short category = 0;

	if (isRoyalFlush (wFace, wSuit))         
		category = ROYAL_FLUSH;
	else if (isStraightFlush (wFace, wSuit)) 
		category = STRAIGHT_FLUSH;
	else if (isFourOfAKind (wFace))
		category = FOUR_OF_A_KIND;
	else if (isFullHouse (wFace))
		category = FULL_HOUSE;
	else if (isFlush (wSuit))
		category = FLUSH;
	else if (isStraight (wFace))
		category = STRAIGHT;
	else if (isThreeOfAKind (wFace))
		category = THREE_OF_A_KIND;
	else if (isTwoPair (wFace))
		category = TWO_PAIR;
	else if (isOnePair (wFace))
		category = ONE_PAIR;
	else
		category = HIGH_CARD;

	return category;
}

short checkWin (short *winningCategory, const int wFace[][N_FACES], const int wSuit[][N_SUITS]) {
	int player = -1;
	short category[2] = {-1};
	short i = 0;

	for (player = 0; player < N_PLAYERS; player++) {
		category[player] = checkHandCategory (wFace[player], wSuit[player]);
	}

	if (category[0] < category[1]) { player = 0; } 
	else if (category[0] == category[1]) {
		switch (category [0]) {

			case FOUR_OF_A_KIND:
				/* checks if either player has four of a kind ACE card */
				if (wFace[0][ACE] == 4)      { player = 0; } 
				else if (wFace[1][ACE] == 4) { player = 1; }
				else {
					for (i = N_FACES - 1; i >= 0 ; i--) {

						/* checks that either face is not zero */
						if (wFace[0][i] != 0 || wFace[1][i] != 0) {

							/* Dealer has higher card */
							if (wFace[0][i] == 4) {
								player = 0;
								break;
							}

							/* Player has higher card */
							if (wFace[1][i] == 4) {
								player = 1;
								break;
							}
						}
					}
				}
				break;

			case STRAIGHT_FLUSH: /* will be checked the same way as straight */
			case STRAIGHT:
				for (i = N_FACES - 1; i >= 0 ; i--) {
					/* checks that either face is not zero */
					if (wFace[0][i] != 0 || wFace[1][i] != 0) {
						/* If highest face is equal */
						if (wFace[0][i] == wFace[1][i]) {
							/* i is King */
							if (i == KING) {
								/* check if ACE is 1 */
								if ((wFace[0][ACE] == 1) && (wFace[1][ACE] == 1))
									player = 2;
								else if ((wFace[0][ACE] == 1) && (wFace[1][ACE] == 0))
									player = 0;
								else if ((wFace[0][ACE] == 0) && (wFace[1][ACE] == 1))
									player = 1;
								else /* No ACE, King is highest for both player */
									player = 2;

							} else { player = 2; } /* highest suit are equal */

							/* Breaks out of loop */
							/* Only need to check highest face card */
							break;
						}

						/* Dealer has higher card */
						if (wFace[0][i] == 1 && wFace[1][i] == 0) {
							player = 0;
							break;
						}

						/* Player has higher card */
						if (wFace[0][i] == 0 && wFace[1][i] == 1) {
							player = 1;
							break;
						}
					}
				}
				break;

			case FULL_HOUSE: /* will be checked the same way as three of a kind */
			case THREE_OF_A_KIND:
				/* checks if either player has three of a kind ACE card */
				if (wFace[0][ACE] == 3)      { player = 0; } 
				else if (wFace[1][ACE] == 3) { player = 1; }
				else {
					for (i = N_FACES - 1; i >= 0 ; i--) {

						/* checks that either face is not zero */
						if (wFace[0][i] != 0 || wFace[1][i] != 0) {

							/* Dealer has higher card */
							if (wFace[0][i] == 3) {
								player = 0;
								break;
							}

							/* Player has higher card */
							if (wFace[1][i] == 3) {
								player = 1;
								break;
							}
						}
					}
				}
				break;

			case TWO_PAIR:
				/* checks if either player has pair of ACE card */
				if (wFace[0][ACE] == 2 && wFace[1][ACE] < 2)      { player = 0; }
				else if (wFace[0][ACE] < 2 && wFace[1][ACE] == 2) { player = 1; }
				else {
					for (i = N_FACES - 1; i >= 0 ; i--) {
						/* checks that either face is not zero */
						if (wFace[0][i] != 0 || wFace[1][i] != 0) {

							/* Dealer has higher card */
							if (wFace[0][i] == 2 && wFace[1][i] < 2) {
								player = 0;
								break;
							}

							/* Player has higher card */
							if (wFace[0][i] < 2 && wFace[1][i] == 2) {
								player = 1;
								break;
							}

							/* Player has the same first pair */
							if (wFace[0][i] == 2 && wFace[1][i] == 2) {
								/* loops through the remaining cards */
								for (i = i - 1; i >= 0; i--) {

									/* checks that either face is not zero */
									if (wFace[0][i] != 0 || wFace[1][i] != 0) {

										/* Dealer has higher card */
										if (wFace[0][i] == 2 && wFace[1][i] < 2) {
											player = 0;
											break;
										}

										/* Player has higher card */
										if (wFace[0][i] < 2 && wFace[1][i] == 2) {
											player = 1;
											break;
										}

										/* Player also has the same second pair */
										if (wFace[0][i] == 2 && wFace[1][i] == 2) {
											/* loops through the remaining cards */
											for (i = i - 1; i >= 0; i--) {

												/* checks that either face is not zero */
												if (wFace[0][i] != 0 || wFace[1][i] != 0) {

													/* Dealer has higher card */
													if (wFace[0][i] == 1 &&  wFace[1][i] == 0) {
														player = 0;
														break;
													}

													/* Player has higher card */
													if (wFace[0][i] == 0 &&  wFace[1][i] == 1) {
														player = 1;
														break;
													}
												}
											}
										}
									}
								}
							}

						}
					}

					/* Players all have the same card */
					if (player == -1) player = 2;
					break;
				}
				break;

			case ONE_PAIR:
				/* checks if either player has pair of ACE card */
				if (wFace[0][ACE] == 2 && wFace[1][ACE] < 2)      { player = 0; }
				else if (wFace[0][ACE] < 2 && wFace[1][ACE] == 2) { player = 1; }
				else {
					for (i = N_FACES - 1; i >= 0 ; i--) {

						/* checks that either face is not zero */
						if (wFace[0][i] != 0 || wFace[1][i] != 0) {

							/* Dealer has higher card */
							if (wFace[0][i] == 2 && wFace[1][i] < 2) {
								player = 0;
								break;
							}

							/* Player has higher card */
							if (wFace[0][i] < 2 && wFace[1][i] == 2) {
								player = 1;
								break;
							}

							/* Player has the same pair */
							if (wFace[0][i] == 2 && wFace[1][i] == 2) {
								/* loops through the remaining cards */
								for (i = i - 1; i >= 0; i--) {

									/* checks that either face is not zero */
									if (wFace[0][i] != 0 || wFace[1][i] != 0) {

										/* Dealer has higher card */
										if (wFace[0][i] == 1 &&  wFace[1][i] == 0) {
											player = 0;
											break;
										}

										/* Player has higher card */
										if (wFace[0][i] == 0 &&  wFace[1][i] == 1) {
											player = 1;
											break;
										}
									}
								}
							}
						}
					}

					/* Players all have the same card */
					if (player == -1) player = 2;
					break;
				}
				break;

			case FLUSH: /* Flush will be check the same way as high card */
			case HIGH_CARD:
				/* checks if either player has an ACE card */
				if (wFace[0][ACE] == 1 && wFace[1][ACE] == 0)      { player = 0; }
				else if (wFace[0][ACE] == 0 && wFace[1][ACE] == 1) { player = 1; }
				else {
					for (i = N_FACES - 1; i >= 0; i--) {

						/* checks that either face is not zero */
						if (wFace[0][i] != 0 || wFace[1][i] != 0) {

							/* Dealer has higher card */
							if (wFace[0][i] == 1 &&  wFace[1][i] == 0) {
								player = 0;
								break;
							}

							/* Player has higher card */
							if (wFace[0][i] == 0 &&  wFace[1][i] == 1) {
								player = 1;
								break;
							}
						}
					}

					/* Players all have the same card */
					if (player == -1) player = 2;
				} 
				break;
		}
	} else { player = 1; }

	*winningCategory = category[player == 2 ? 0 : player];
	return player;
}

void swapCards (Card playersHand[][N_CARDS_ON_HAND], const char *wFace[], const char *wSuit[]) {
	short i = 0, j = 0;

	drawOutputBox (" ");
	printf ("SELECT CARDS TO SWAP");

	for (i = 0; i < N_CARDS_ON_HAND; i++) {
		MoveCursor (34, 16 + i);
		printf ("  [ ] %s of %s", wFace[playersHand[1][i].faceIndex], wSuit[playersHand[1][i].suitIndex]);
	}

	MoveCursor (34, 16 + i);
	printf (" Use SPACEBAR to select/deselect");
	MoveCursor (34, 16 + i + 1);
	printf (" Press ENTER to continue");
}

short selectSwapMenuItem (Card playersHand[][N_CARDS_ON_HAND], int wDeck[][N_FACES], 
	                     short *numDealtCard) {
	Card hand;
	short countSwap = 0;
	short cursorX = 37,
		  cursorY = 16;
	short holdCard[5] = {0};
	char ch = '\0';

	int i = 0;

	MoveCursor (cursorX, cursorY);

	do {
		ch = getch ();
		switch(ch) { 
			case ARROW_KEY_UP: 
				/* UP arrow key is pressed */
				if (cursorY == 16) {
					cursorY = cursorY + 4;
					MoveCursor (cursorX, cursorY);
				} else if (cursorY > 16) {
					cursorY--;
					MoveCursor (cursorX, cursorY);
				} 		
				break;

			case ARROW_KEY_DOWN: 
				/* DOWN arrow key is pressed */
				if (cursorY < 20) {
					cursorY++;
					MoveCursor (cursorX, cursorY);
				} else if (cursorY == 20) {
					cursorY = 16;
					MoveCursor (cursorX, cursorY);
				}
				break; 

			case SPACE_BAR:
				/* SPACEBAR key is pressed */
				if (!(holdCard [cursorY % 16])) {
					printf ("X");
					MoveCursor (cursorX, cursorY);
				} else {
					printf (" ");
					MoveCursor (cursorX, cursorY);
				}

				holdCard [cursorY % 16] = !(holdCard [cursorY % 16]);
				break;
		}
	} while (ch != 13);

	drawOutputBox (" ");
	for (i = 0; i < N_CARDS_ON_HAND; i++) {
		if (holdCard[i] == 1) { 
			countSwap++;
			*numDealtCard += 2; /* burn a card then deal the next card */
			hand = dealNextCard (wDeck, *numDealtCard);
			playersHand[1][i].cardNumber = hand.cardNumber;
			playersHand[1][i].faceIndex = hand.faceIndex;
			playersHand[1][i].suitIndex = hand.suitIndex;
		}
	}

	return countSwap;
}

Card dealNextCard (int wDeck[][N_FACES], short numDealtCard) {
	Card hand = {0, 0, 0};
	short row = 0, column = 0;

	/* loop through rows of wDeck */
	for (row = 0; row < N_SUITS; row++) {

		/* loop through columns of wDeck for current row */
		for (column = 0; column < N_FACES; column++) {

			/* if slot contains current card, display card */
			if (wDeck[row][column] == numDealtCard) {
				hand.suitIndex = row;
				hand.faceIndex = column;
				hand.cardNumber = numDealtCard;
			}
		}
	}

	return hand;
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

Boolean isFullHouse (const int wFace[]) {
	int i = 0, count = 0;
	Boolean result = False;
	
	/* loops through all 13 card numbers */
	/* if 1 card is different or 4 have the same face value, 
	   then automaticaly it's not a full house*/
	while (i < N_FACES && count != 1 && count != 4) {
		/* 3 means there is a three of a kind */
		if (wFace[i] == 3) {
			i++;
			/* loops again to find a pair */
			/* count gets a value other than zero, means not a fullhouse */
			while (i < N_FACES && count == 0) {
				/* found a pair */
				if (wFace[i] == 2) {
					result = True;
					break;
				}
				count += wFace[i++];
			}
			break;
		}
		/* 2 means there is a pair */
		if (wFace[i] == 2) {
			i++;
			/* loops again to find a three of a kind */
			/* count gets a value other than zero, means not a fullhouse */
			while (i < N_FACES && count == 0) {
				/* found a three of a kind */
				if (wFace[i] == 3) {
					result = True;
					break;
				}
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
				for (j = i + 1; j < i + 5; j++) {
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

Boolean isStraightFlush (const int wFace[], const int wSuit[]) {
	Boolean result = False;

	if (isStraight (wFace) && isFlush (wSuit)) 
		result = True;

	return result;
}

Boolean isRoyalFlush (const int wFace[], const int wSuit[]) {
	Boolean result = False;

	if (isStraight (wFace) && isFlush (wSuit) && wFace[0] == 1) 
		result = True;

	return result;
}