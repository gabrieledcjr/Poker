#include "random.h"

/**
 * Function name : Randomize ()
 * Date Created  : 27 November 2012
 * Usage         : Randomize ();
 * Definition    : This function should be called once in the program
 *                 to establish random sequence
 * Pre-condition : n/a
 * Post-condition: n/a
 */
void Randomize (void) {
	srand ((unsigned int) time (NULL));
}

/**
 * Function name : RandomInteger ()
 * Date Created  : 27 November 2012
 * Usage         : int randomInt = RandomInteger (lowest, highest);
 * Definition    : This function returns a random number within the
 *                 the range specified
 * Pre-condition : n/a
 * Post-condition: n/a
 */
int RandomInteger (int lowest, int highest) {
	if (lowest == 0)
		return rand () % ++highest;
	
	if (lowest > 0)
		return rand () % ++highest + lowest;
}

unsigned int RandomUnsignedInteger (unsigned int lowest, unsigned int highest) {
	if (lowest == 0)
		return rand () % ++highest;
	
	if (lowest > 0)
		return rand () % ++highest + lowest;
}

double RandomReal (double lowest, double highest) {
	return 0.0;
}

/**
 * Function name : RandomChance ()
 * Date Created  : 27 November 2012
 * Usage         : int randomInt = RandomInteger (lowest, highest);
 * Definition    : This function returns 0 or 1 randomly
 * Pre-condition : n/a
 * Post-condition: n/a
 */
short RandomChance (void) {
	return RandomInteger (0, 1);
}

/**
 *
 */
short RandomProbability (double probability, unsigned int sampleRange) {
	double randNumber = (double) RandomUnsignedInteger (1, sampleRange);

	if ((randNumber / (double) sampleRange) <= probability)
		return 1;
	else
		return 0;
}