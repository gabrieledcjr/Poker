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