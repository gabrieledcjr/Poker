/*==============================================================================
 | Filename: poker.h                                                     
 | Programmer: Gabriel V. de a Cruz Jr.                                  
 | Class: CptS 121, Fall 2012 ; Lab Section 7                            
 | Programming Assignment 7: Poker (5-Card Draw)                    
 | Date: November 27, 2012                                                 
 +------------------------------------------------------------------------------
 | Description: This file the macro constants, standard libraries, structs, 
 |              enums and function headers
 +==============================================================================*/
#ifndef POKER_H
#define POKER_H

#include <stdio.h>
#include <conio.h>

#define DEALER_RISK        .60    /* The higher the number, the riskier the dealer plays */

#define N_CARDS_ON_DECK    52     /* Number of cards on deck */
#define N_SUITS            4      /* Number of suits */
#define N_FACES            13     /* Number of card numbers per suit */
#define N_CARDS_ON_HAND    5      /* Number of cards dealt to player */
#define N_PLAYERS          2      /* Number of players including dealer */
#define N_HAND_CATEGORIES  10

#define N_OF_GAMES         10     /* Number of games */

#define ARROW_KEY_UP       72     /* value for arrow key up */
#define ARROW_KEY_DOWN     80     /* value for arrow key down */
#define SPACE_BAR          32     /* value for space bar */

#define CURSOR_SYMBOL      236    /* ASCII value of infinity symbol */
#define MENU_X             63     /* Menu x coordinate */
#define MENU_Y             4      /* Menu y coordinate */

#define PLAY_GAME          1      /* Menu items */
#define SWAP_CARDS         2
#define STATS              3
#define QUIT_GAME          4

typedef enum hand_category {
	ROYAL_FLUSH, 
	STRAIGHT_FLUSH, 
	FOUR_OF_A_KIND, 
	FULL_HOUSE, 
	FLUSH, 
	STRAIGHT, 
	THREE_OF_A_KIND, 
	TWO_PAIR, 
	ONE_PAIR, 
	HIGH_CARD
} HandCategory;

typedef enum {
	HEARTS, DIAMONDS, CLUBS, SPADES
} Suit;

typedef enum {
	ACE, DEUCE, THREE, FOUR, FIVE, 
	SIX, SEVEN, EIGHT, NINE, TEN, 
	JACK, QUEEN, KING
} Face;

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

void  init                (int deckOfCard[][N_FACES]);
void  resetSuitCounter    (int suit[][N_SUITS]);
void  resetFaceCounter    (int face[][N_FACES]);
void  shuffle             (int wDeck[][N_FACES]);
void  deal                (const int wDeck[][N_FACES], const char *wFace[], 
                           const char *wSuit[], Card hand[][N_CARDS_ON_HAND]);
void  sortHand            (Card hand[]);
void  countSuitsAndFaces  (int wSuit[][N_SUITS], int wFace[][N_FACES], 
                           Card hand[][N_CARDS_ON_HAND]);
void  drawPlayerCard      (short x, short y, short suit, short face);
void  drawFaceCharacter   (short type);
void  drawSuitCharacter   (short type);
void  drawSuitSymbol      (short x, short y, short type);
void  drawPlayerHand      (Card playersHand []);
void  drawDealerCard      (short x, short y, short suit, short face, Boolean showCard);
void  drawDealerHand      (Card playersHand [], Boolean showCard);
void  drawOutputBox       (const char *message);
void  drawMenu            (void);

void  playDealerHand      (Card playersHand[][N_CARDS_ON_HAND], int wDeck[][N_FACES], 
	                       short *numDealtCard, int wFace[][N_FACES], int wSuit[][N_SUITS]);
void  swapCards           (Card playersHand[][N_CARDS_ON_HAND], 
	                       const char *wFace[], const char *wSuit[]);

short selectMenuItem      (void);
short checkHandCategory   (const int wFace[], const int wSuit[]);
short checkWin            (short *winningCategory, const int wFace[][N_FACES], const int wSuit[][N_SUITS]);
short selectSwapMenuItem  (Card playersHand[][N_CARDS_ON_HAND], int wDeck[][N_FACES], 
	                       short *numDealtCard);
Card  dealNextCard        (int wDeck[][N_FACES], short numDealtCard);

Boolean  isOnePair       (const int wFace[]);
Boolean  isTwoPair       (const int wFace[]);
Boolean  isThreeOfAKind  (const int wFace[]);
Boolean  isFourOfAKind   (const int wFace[]);
Boolean  isFlush         (const int wSuit[]);
Boolean  isStraight      (const int wFace[]);
Boolean  isFullHouse     (const int wFace[]);
Boolean  isStraightFlush (const int wFace[], const int wSuit[]);
Boolean  isRoyalFlush    (const int wFace[], const int wSuit[]);

#endif