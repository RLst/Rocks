#pragma once

//Game settings and constatns
const unsigned int const SCREEN_WIDTH = 1680;
const unsigned int const SCREEN_HEIGHT = 1080;
const float PI = 3.1415927f;

//Enums
enum RockType {
	SML_ROCK = 1,
	MED_ROCK,
	LGE_ROCK
};

//Core functions
int Random(int min, int max);

float rads(float degrees); 

namespace pkr {	//pokoro
//Flexi vector

//typename<typename T>
union vector2
{
	//Position and trajectories
	struct {
		float x;
		float y;
	};

	//Velocity (Speed and angle)
	struct {
		float m;	//magnitude
		float a;	//angle
	};

	//Operator overloads (only have to do for x,y since the share mem with m,a)
	//Getting HAIRY!!!..
	vector2& operator + (const vector2 &other) {
		vector2 add;
		add.x += other.x;
		add.y += other.y;
		return add;
	}
	vector2& operator - (const vector2 &other) {
		vector2 sub;
		sub.x -= other.x;
		sub.y -= other.y;
		return sub;
	}
	vector2& operator * (const vector2 &other) {
		vector2 mult;
		mult.x *= other.x;
		mult.y *= other.y;
		return mult;
	}
	vector2& operator / (const vector2 &other) {
		vector2 div;
		div.x *= other.x;
		div.y *= other.y;
		return div;
	}
	bool operator == (vector2 const &other) {
		return (x == other.x && y == other.y);
	}
	vector2& operator = (vector2 const &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}

};


}
