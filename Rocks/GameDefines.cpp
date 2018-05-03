#include <cassert>
#include <iostream>
#include "GameDefines.h"


int Random(int max) {	//Returns number between 0 and MAX
	//assert(max < 0);	//Error if max is a negative number
	if (max == 0) return 0;		//Returns 0 if input is 0
	if (max < 0)				//Invert if negative number
		max *= -1;
	return rand() % max + 1;
}

int Random(int min, int max)
{
	return min + rand() % (max-min+1);
}

float degTOrads(float degrees)
{
	return degrees * (PI / 180.0f);
}
