/*==============================================================================
 | Filename: main.c                                                      
 | Programmer: Gabriel V. de a Cruz Jr.                                  
 | Class: CptS 121, Fall 2012 ; Lab Section 7                            
 | Programming Assignment 7: Poker (5-Card Draw)                    
 | Date: November 27, 2012                                                 
 +------------------------------------------------------------------------------
 | Description: This program is a Five-card draw poker game. Its a two player 
 |              game between a player and the computer who is the dealer. The 
 |              player and the dealer is dealt with 5 cards. The player will 
 |              have one chance per game to swap cards. The program also 
 |              simulates the dealer swapping cards if the program deems 
 |              necessary. When player chooses to play, the program will check 
 |              both the player and dealer's hand for the winner.
 +==============================================================================*/
#include "poker.h"


int main (void) 
{
	/* initialize suit array */
	const char *suit[N_SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};

	/* initialize face array */
	const char *face[N_FACES] = {"Ace", "Deuce", "Three", "Four", "Five", 
		                         "Six", "Seven", "Eight", "Nine", "Ten", 
							     "Jack", "Queen", "King"};
	
	/* hand categories */
	const char *category[N_HAND_CATEGORIES] = {"ROYAL FLUSH", 
	                                           "STRAIGHT FLUSH", 
	                                           "FOUR OF A KIND", 
	                                           "FULL HOUSE", 
	                                           "FLUSH", 
	                                           "STRAIGHT", 
	                                           "THREE OF A KIND", 
	                                           "TWO PAIR", 
	                                           "ONE PAIR", 
	                                           "HIGH CARD"};

	char winMessage [30];

	int deckOfCard[N_SUITS][N_FACES]    = {0};   /* represents deck of cards */
	int suitCounter[N_PLAYERS][N_SUITS] = {0};   /* counts how many times a suit repeats on hand */
	int faceCounter[N_PLAYERS][N_FACES] = {0};   /* counts how many times a face repeats on hand */

	int playerWinStats[2] = {0};   /* counts number of wins 0 for dealer, 1 for player */
	int numOfGames = 0;            /* counts number of games played */

	short player = -1;             /* tracks player */
	short numDealtCard = 0;        /* count number of dealt cards */
	short menu = -1;               /* menu chosen */
	short swapStatus = 0;          /* player choses to swap cards */
	short winningCategory = -1;    /* the category player or dealer won */

	/* Player 0 is Dealer and 1 is Player 1 */
	Card playersHand[N_PLAYERS][N_CARDS_ON_HAND];

	/* seed random-number generator */
	Randomize ();

	/* draws border on the screen */
	DrawBorder (0, 0, 79, 24);

	/* play number of games specified by macro constant value */
	while (True) {
		/* initialization */
		numOfGames++;
		player = -1;
		winningCategory = -1;
		swapStatus = 0;
		strcpy (winMessage, "");

		/* initializes deck, suit and face counter to 0 */
		init (deckOfCard);
		resetSuitCounter (suitCounter);
		resetFaceCounter (faceCounter);

		/* shuffles the deck of cards */
		shuffle (deckOfCard);
		
		/* deals card to dealer and player(s) */
		deal (deckOfCard, face, suit, playersHand);
		
		/* number of dealt card is 10 */
		numDealtCard = N_PLAYERS * N_CARDS_ON_HAND;

		/* sorts hand descendingly */
		sortHand (playersHand [0]);
		sortHand (playersHand [1]);

		/* count repetitions of suits and faces */
		countSuitsAndFaces (suitCounter, faceCounter, playersHand);

		/* draws player's card */
		drawPlayerHand (playersHand [1]);

		/* draws simulated cards for dealer */
		drawDealerHand (playersHand [0], False);

		while (True) {

			/* draws border for output box */
			drawOutputBox ("> Use ARROW KEYS to select from MENU");

			/* draws player menu */
			drawMenu ();
		
			switch (selectMenuItem ()) {

				case PLAY_GAME:
					/* simulates dealer making decision */
					playDealerHand (playersHand, deckOfCard, &numDealtCard, faceCounter, suitCounter);

					/* resets suit and face counter to 0 */
					resetSuitCounter (suitCounter);
					resetFaceCounter (faceCounter);

					/* count repetitions of suits and faces */
					countSuitsAndFaces (suitCounter, faceCounter, playersHand);

					player = checkWin (&winningCategory, faceCounter, suitCounter);
					if (player == 0) { /* Dealer wins */
						playerWinStats[0]++;
						strcpy (winMessage, "> Dealer wins with ");
						strcat (winMessage, category[winningCategory]);
					}
					else if (player == 1) { /* Player wins */
						playerWinStats[1]++;
						strcpy (winMessage, "> Player wins with ");
						strcat (winMessage, category[winningCategory]);
					} else { /* Draw */
						playerWinStats[0]++;
						playerWinStats[1]++;
						strcpy (winMessage, "> It's a draw!");
					}

					/* draws simulated cards for dealer */
					drawDealerHand (playersHand [0], True);

					drawOutputBox (winMessage);
					MoveCursor (34, 16);
					printf ("> Press <ENTER> for another game");
					getch ();
					break;

				case SWAP_CARDS:
					/* Player choses to swap cards */
					if (swapStatus == 0) {
						swapCards (playersHand, face, suit);
						if (selectSwapMenuItem (playersHand, deckOfCard, &numDealtCard) > 0) {
							sortHand (playersHand [1]);
							drawPlayerHand (playersHand [1]);

							swapStatus = 1;
						}
					} else {
						/* player only allows to swap card once per game */
						drawOutputBox ("> ERROR: You already swap card(s)!");
						MoveCursor (34, 16);
						printf ("> Press <ENTER> to continue");
						getch ();
					}
					break;

				case STATS:
					/* prints out player and dealer stats */
					drawOutputBox ("> STATS");
					MoveCursor (34, 16);
					printf ("> PLAYER: %d win(s) out of %d games", playerWinStats[1], numOfGames - 1);
					MoveCursor (34, 17);
					printf ("> DEALER: %d win(s) out of %d games", playerWinStats[0], numOfGames - 1);
					MoveCursor (34, 18);
					printf ("> Press <ENTER> to continue");
					getch ();
					break;

				case QUIT_GAME:
					/* exits the game */
					ClearScreen ();
					exit (1);
					break;
			}

			if (player != -1) break;
		}
	}

	return 0;
}