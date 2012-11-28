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

	int deckOfCard[N_SUITS][N_FACES] = {0};

	int suitCounter[N_PLAYERS][N_SUITS] = {0};
	int faceCounter[N_PLAYERS][N_FACES] = {0};

	/* Player 0 is Dealer and 1 is Player 1 */
	Card playersHand[N_PLAYERS][N_CARDS_ON_HAND];

	int sampleFace[13] = {0};
	int sampleSuit[4] = {0};

	sampleFace[0] = 1;
	sampleFace[1] = 0;
	sampleFace[8] = 0;
	sampleFace[9] = 2;
	sampleFace[10] = 0;
	sampleFace[11] = 0;
	sampleFace[12] = 1;
	
	sampleSuit[3] = 2;
	sampleSuit[1] = 3;

	printf ("Test>> One Pair: %s\n", isOnePair (sampleFace) ? "YES": "NO");
	printf ("Test>> Two Pairs: %s\n", isTwoPair (sampleFace) ? "YES": "NO");
	printf ("Test>> Three of a Kind: %s\n", isThreeOfAKind (sampleFace) ? "YES": "NO");
	printf ("Test>> Four of a Kind: %s\n", isFourOfAKind (sampleFace) ? "YES": "NO");
	printf ("Test>> Flush: %s\n", isFlush (sampleSuit) ? "YES": "NO");
	printf ("Test>> Straight: %s\n", isStraight (sampleFace) ? "YES": "NO");

	/* seed random-number generator */
	Randomize ();

	/* Shuffles the deck of cards */
	shuffle (deckOfCard);

	/* Deals card to dealer and player(s) */
	deal (deckOfCard, face, suit, playersHand);

	countSuitsAndFaces (suitCounter, faceCounter, playersHand);


	printf ("Player 1>> One Pair: %s\n", isOnePair (faceCounter[0]) ? "YES": "NO");
	printf ("Player 1>> Two Pairs: %s\n", isTwoPair (faceCounter[0]) ? "YES": "NO");
	printf ("Player 1>> Three of a Kind: %s\n", isThreeOfAKind (faceCounter[0]) ? "YES": "NO");
	printf ("Player 1>> Four of a Kind: %s\n", isFourOfAKind (faceCounter[0]) ? "YES": "NO");
	printf ("Player 1>> Flush: %s\n", isFlush (suitCounter[0]) ? "YES": "NO");

	printf ("Player 2>> One Pair: %s\n", isOnePair (faceCounter[1]) ? "YES": "NO");
	printf ("Player 2>> Two Pairs: %s\n", isTwoPair (faceCounter[1]) ? "YES": "NO");
	printf ("Player 2>> Three of a Kind: %s\n", isThreeOfAKind (faceCounter[1]) ? "YES": "NO");
	printf ("Player 2>> Four of a Kind: %s\n", isFourOfAKind (faceCounter[1]) ? "YES": "NO");
	printf ("Player 2>> Flush: %s\n", isFlush (suitCounter[1]) ? "YES": "NO");
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
	and determine who wins. Now use the program to play 10 games against the 
	computer. You should be able to test and modify or refine your Poker game 
	based on these results!
*/
	return 0;
}