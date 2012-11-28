#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>

void     Randomize      (void);
int      RandomInteger  (int lowest, int highest);
double   RandomReal     (double lowest, double highest);
short    RandomChance   (void);

#endif