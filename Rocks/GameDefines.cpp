#include "GameDefines.h"
#include <iostream>

int Random(int min, int max)
{
	return min + rand() % (max-min+1);
}
