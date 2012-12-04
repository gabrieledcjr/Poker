/*==============================================================================
 | Filename: main.c                                                      
 | Programmer: Gabriel V. de a Cruz Jr.                                  
 | Class: CptS 121, Fall 2012 ; Lab Section 7                            
 | Programming Assignment 7: Poker (5-Card Draw)                    
 | Date: November 27, 2012                                                 
 +------------------------------------------------------------------------------
 | Description:                              
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

	int deckOfCard[N_SUITS][N_FACES]    = {0};
	int suitCounter[N_PLAYERS][N_SUITS] = {0};
	int faceCounter[N_PLAYERS][N_FACES] = {0};

	short player = -1;
	short numDealtCard = 0;
	short menu = -1;
	short swapStatus = 0;
	short winningCategory = -1;

	/* Player 0 is Dealer and 1 is Player 1 */
	Card playersHand[N_PLAYERS][N_CARDS_ON_HAND];

	/* seed random-number generator */
	Randomize ();

	/* draws border on the screen */
	DrawBorder (0, 0, 79, 24);

	/* play number of games specified by macro constant value */
	while (True) {
		/* initialization */
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
		drawDealerHand (playersHand [0], True);

		while (True) {

			/* draws border for output box */
			drawOutputBox ("> Use ARROW KEYS to select from MENU");

			/* draws player menu */
			drawMenu ();
		
			switch (selectMenuItem ()) {

				case PLAY_GAME:
					/* DEALER */
					playDealerHand (playersHand, deckOfCard, &numDealtCard, faceCounter, suitCounter);

					/* resets suit and face counter to 0 */
					resetSuitCounter (suitCounter);
					resetFaceCounter (faceCounter);

					/* count repetitions of suits and faces */
					countSuitsAndFaces (suitCounter, faceCounter, playersHand);

					player = checkWin (&winningCategory, faceCounter, suitCounter);
					if (player == 0) { /* Dealer wins */
						strcpy (winMessage, "> Dealer wins with ");
						strcat (winMessage, category[winningCategory]);
					}
					else if (player == 1) { /* Player wins */
						strcpy (winMessage, "> Player wins with ");
						strcat (winMessage, category[winningCategory]);
					} else { /* Draw */
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
					if (swapStatus == 0) {
						swapCards (playersHand, face, suit);
						if (selectSwapMenuItem (playersHand, deckOfCard, &numDealtCard) > 0) {
							sortHand (playersHand [1]);
							drawPlayerHand (playersHand [1]);

							swapStatus = 1;
						}
					} else {
						drawOutputBox ("> ERROR: You already swap card(s)!");
						MoveCursor (34, 16);
						printf ("> Press <ENTER> to continue");
						getch ();
					}
					break;

				case STATS:

				case QUIT_GAME:
					ClearScreen();
					exit (1);
					break;
			}

			if (player != -1) break;
		}
	}

	getch ();
	ClearScreen ();

/**
(2) (20 pts) Use the functions developed in (1) to deal two five-card poker 
    hands, evaluate each hand, and determine which is the better hand.
	    
(3) (25 pts) Simulate the dealer. The dealer's five-card hand is dealt 
    "face down" so the player cannot see it. The program should then 
	evaluate the dealer's hand, and based on the quality of the hand, the 
	dealer should draw one, two, or three more cards to replace the 
	corresponding number of unneeded cards in the original hand. The 
	program should then re-evaluate the dealer's hand.

(4) (20 pts) Make the program handle the dealer's five-card hand 
    automatically. The player should be allowed to decide which cards of 
	the player's hand to replace. The program should then evaluate both hands 
	and determine who wins. 
	
	// SEMI-COMPLETED
	Now use the program to play 10 games against the 
	computer. You should be able to test and modify or refine your Poker game 
	based on these results!
*/
	return 0;
}



	/************ TEST SECTION ************/
	//int sampleFace[13] = {0};
	//int sampleSuit[4] = {0};

	//sampleFace[0] = 3;
	//sampleFace[1] = 0;
	//sampleFace[8] = 0;
	//sampleFace[9] = 0;
	//sampleFace[10] = 0;
	//sampleFace[11] = 0;
	//sampleFace[12] = 2;
	//
	//sampleSuit[3] = 2;
	//sampleSuit[1] = 3;

	//printf ("Test>> One Pair: %s\n", isOnePair (sampleFace) ? "YES": "NO");
	//printf ("Test>> Two Pairs: %s\n", isTwoPair (sampleFace) ? "YES": "NO");
	//printf ("Test>> Three of a Kind: %s\n", isThreeOfAKind (sampleFace) ? "YES": "NO");
	//printf ("Test>> Full House: %s\n", isFullHouse (sampleFace) ? "YES": "NO");
	//printf ("Test>> Four of a Kind: %s\n", isFourOfAKind (sampleFace) ? "YES": "NO");
	//printf ("Test>> Flush: %s\n", isFlush (sampleSuit) ? "YES": "NO");
	//printf ("Test>> Straight: %s\n", isStraight (sampleFace) ? "YES": "NO");
	/************ TEST SECTION ************/