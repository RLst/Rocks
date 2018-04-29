#include "GameDefines.h"
#include <iostream>

int Random(int min, int max)
{
	return min + rand() % (max-min+1);
}

float rads(float degrees)
{
	return degrees * (PI / 180.0f);
}
