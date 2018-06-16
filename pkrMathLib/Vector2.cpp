//pkr Math Library
//Author: Tony Le
//Version: 1.0

#include <cmath>
#include "Vector2.h"
#include "Vector3.h"

const float Vector2::DEF_TOLERANCE = 0.00001f;

Vector2::Vector2() : x(0), y(0)									//Default
{}

Vector2::Vector2(float x, float y) : x{x}, y{y}					//Initialiser
{}

Vector2::Vector2(const Vector2 & other) :						//Copy constructor
	x(other.x), y(other.y)
{}

Vector2::Vector2(const Vector3 & other)	:						//3D Copy
	x(other.x), y(other.y)				//Copy other into 'this' ignoring other.z
{}

Vector2::~Vector2()												//Destructor
{}

Vector2 Vector2::operator-() const
{
	return { -x, -y };
}

Vector2 Vector2::operator+(const Vector2 & other) const			//Addition
{
	return { x + other.x, y + other.y };

	//OR
	//Vector2D(x + other.x, y + other.y);

	//OR
	//Vector2 temp;
	//temp.x + other.x;
	//temp.y + other.y;
	//return temp;
}

Vector2 Vector2::operator-(const Vector2 & other) const			//Subtract
{
	return { x - other.x, y - other.y };
}

Vector2 Vector2::operator*(const float scalar) const			//POST multiply
{
	return { x * scalar, y * scalar };
}

Vector2 Vector2::operator/(const float scalar) const			//POST divide
{
	return { x / scalar, y / scalar };
}

Vector2 operator*(const float scalar, const Vector2 & other)	//PRE multiply
{
	return { other.x * scalar, other.y * scalar };
}

Vector2 operator/(const float scalar, const Vector2 & other)	//PRE divide
{
	return { other.x / scalar, other.y / scalar };
}

Vector2& Vector2::operator+=(const Vector2 & other)				//Addition assign
{
	x += other.x; y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2 & other)				//Subtract assign
{
	x -= other.x; y -= other.y;
	return *this;
}

Vector2& Vector2::operator*=(float scalar)						//Scalar multiply assign
{
	x *= scalar; y *= scalar;
	return *this;
}

Vector2& Vector2::operator/=(float scalar)						//Scalar divide assign
{
	x /= scalar; y /= scalar;
	return *this;
}

Vector2& Vector2::operator=(const Vector2 & other)				//Assign
{
	x = other.x; y = other.y;
	return *this;
}

bool Vector2::operator==(const Vector2 & other)					//Equality check
{
	return (x == other.x && y == other.y);
}

bool Vector2::operator!=(const Vector2 & other)					//Inequality check
{
	return (x != other.x && y == other.y);
}

bool Vector2::equal(const Vector2 & other, float tolerance)		//Equality check with tolerance
{
	if (abs(x - other.x) > tolerance &&
		abs(y - other.y) > tolerance)
		return false;
	return true;
}

bool Vector2::notEqual(const Vector2 & other, float tolerance)	//Inequality check with tolerance
{
	if (abs(x - other.x) < tolerance &&
		abs(y - other.y) < tolerance)
		return false;
	return true;
}

float Vector2::operator[]( int index) const						//Access 
{
	return data[index];
}

float & Vector2::operator[]( int index)							//Return reference
{
	return data[index];
}

Vector2::operator float*()										//Mutator float pointer cast
{
	return data;
}

Vector2::operator const float*() const							//Inspector float pointer cast
{
	return data;
}

float Vector2::dot(const Vector2 & other) const					//Dot product
{
	return x * other.x + y * other.y;
}

float Vector2::dot(const Vector2 & a, const Vector2 & b)		//Dot product of 2 non-members
{
	return a.x * b.x + a.y * b.y;
}

Vector2 Vector2::getPerpendRH() const							//Right hand perpendicular angle
{
	return { -y, x };
}

Vector2 Vector2::getPerpendLH() const							//Left hand perpendicular angle
{
	return { y , -x };
}

float Vector2::angleBetween(const Vector2 & other) const		//Angle between this and another vector
{
	//Normalise
	Vector2 a = normalised();
	Vector2 b = other.normalised();

	//Dot product
	float d = a.x * b.x + a.y * b.y;

	//Return angle
	return acos(d);
}

float Vector2::angleBetween(const Vector2 & a, const Vector2 & b)	//Angle between two non-members
{
	//Normalise and dot product
	float d = dot(normalised(a), normalised(b));

	//Return angle
	return acos(d);
}

float Vector2::magnitude()										//Get length of self
{
	//Minor optimizations (can only be easily done for 2D)
	if (x == 0.0f) {
		return abs(y);
	}
	else if (y == 0.0f) {
		return abs(x);
	}
	return sqrt(x*x + y*y);
}

float Vector2::magnitude(const Vector2 & vec)					//Get length of input vector
{
	//Minor optimizations
	if (vec.x == 0.0f) {
		return abs(y);
	}
	else if (vec.y == 0.0f) {
		return abs(x);
	}
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

float Vector2::magnitudeSqr() const								//Squared magnitude
{
	return (x*x + y*y);
}

float Vector2::distance(const Vector2 & other) const			//Returns distance between this and another vector
{
	return sqrt((x-other.x)*(x-other.x) + (y-other.y)*(y-other.y));
}

float Vector2::distance(const Vector2 & A, const Vector2 & B)	//Returns distance between 2 non-members
{
	return sqrt((B.x - A.x)*(B.x - A.x) + (B.y - A.y)*(B.y - A.y));
}

float Vector2::distanceSqr(const Vector2 & other) const			//Squared distance
{
	return ((x-other.x)*(x-other.x) + (y-other.y)*(y-other.y));
}

void Vector2::normalise()										//Self normalising
{
	//In case of divide by zero
	if (x == 0.0f && y == 0.0f)
		return;

	float mag = sqrt(x*x + y * y);
	x /= mag;
	y /= mag;
}

Vector2 Vector2::normalised() const								//Return copy of normalised self
{
	float mag = sqrt(x*x + y * y);
	return { x / mag, y / mag };
}

Vector2 Vector2::normalised(const Vector2 & vec)				//Return a normalised copy of input vector
{
	//In case of divide by zero
	if (vec.x == 0.0f && vec.y == 0.0f)
		return { 0, 0 };

	float mag = sqrt(vec.x*vec.x + vec.y*vec.y);
	return { vec.x / mag, vec.y / mag };
}

void Vector2::absolute()										//Self absolute
{
	for (int i = 0; i < 2; ++i)
		data[i] = abs(data[i]);
}

Vector2 Vector2::getAbsolute() const							//Return absolute copy
{
	Vector2 result;
	for (int i = 0; i < 2; ++i)
		result.data[i] = abs(data[i]);
	return result;
}

Vector2 Vector2::getAbsolute(const Vector2 & vec)				//Return absolute copy of non-member
{
	Vector2 result;
	for (int i = 0; i < 2; ++i)
		result.data[i] = abs(vec.data[i]);
	return result;
}