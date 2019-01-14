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

float Random(float min, float max)
{
	float percentage = (rand() % 10000) / 10000.0f;
	return min + ((max - min) * percentage);
}

float Random(float max)
{
	float percentage = (rand() % 10000) / 10000.0f;
	return max * percentage;
}

float getDistance(Vector2 a, Vector2 b)
{
	return ( sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y)) );
}

float getVecMagnitude(Vector2 vec2)
{
	return sqrt(vec2.x * vec2.x + vec2.y * vec2.y);
}

void normalise(Vector2 & input)
{
	input /= sqrt(input.x * input.x + input.y * input.y);
}

float degTOrads(float degrees)
{
	return degrees * (PI / 180.0f);
}
