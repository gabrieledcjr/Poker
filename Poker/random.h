/*==============================================================================
 | Filename: random.h                                                  
 | Programmer: Gabriel V. de a Cruz Jr.                                  
 | Class: CptS 121, Fall 2012 ; Lab Section 7                            
 | Programming Assignment 7: Poker (5-Card Draw)                    
 | Date: November 27, 2012                                                 
 +------------------------------------------------------------------------------
 | Description: This file is paired with random.c for the purpose of reusing 
 |              these functions for future programs. 
 +==============================================================================*/
#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void     Randomize              (void);
int      RandomInteger          (int lowest, int highest);
long int RandomUnsignedInteger  (int lowest, unsigned int highest);
double   RandomReal             (double lowest, double highest);
short    RandomChance           (void);
short    RandomProbability      (double probability, int sampleRange);

#endif