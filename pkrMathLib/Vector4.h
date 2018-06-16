//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once
class Vector2;
#include "Vector3.h"

class Vector4
{
public:
	union
	{
		//Homogenous
		struct {
			float x, y, z, w;
		};

		//Colour
		struct {
			float r, g, b, alpha;
		};

		//Array
		float data[4];
	};
	static const float DEF_TOLERANCE;

	Vector4();															//Default
	Vector4(float x, float y, float z, float w = 1);					//Initialiser (automatic 3D or 4D)
	Vector4(const Vector3& other);										//3D Copy Constructor
	Vector4(const Vector4& other);										//4D Copy Constructor
	~Vector4();															//Destructor

	//Operators
	Vector4		operator - () const;									//UNARY minus
	Vector4		operator + (const Vector4 &other) const;				//Point/Vector to Vector add (point translated by a vector)
	Vector4		operator - (const Vector4 &other) const;				//Point/Vector to Vector subtract (point translated by a vector)
	
	Vector4		operator * (float scalar) const;						//POST Scalar multiply (vector scale)
	Vector4		operator / (float scalar) const;						//POST Scalar divide (vector scale)
	friend Vector4 operator * (float scalar, const Vector4 &other);		//PRE Scalar multiply (vector scale)

	Vector4&	operator += (const Vector4 &other);						//Point/Vector to Vector add assign
	Vector4&	operator -= (const Vector4 &other);						//Point/Vector to Vector subtract assign
	Vector4&	operator *= (float scalar);								//Scalar multiply assign
	Vector4&	operator /= (float scalar);								//Scalar divide assign
	
	Vector4&	operator = (const Vector3 &other);						//Assignment by Vector3
	Vector4&	operator = (const Vector4 &other);						//Assignment by Vector4
	bool		operator == (const Vector4 &other);						//Equality check
	bool		operator != (const Vector4 &other);						//Inequality check
	bool		equal(const Vector4 &other, float tolerance = DEF_TOLERANCE);			//Equality check with tolerance
	bool		notEqual(const Vector4 &other, float tolerance = DEF_TOLERANCE);		//Inequality check with tolerance

	//Subscript
	float		operator [] (int index) const;							//Inspector; Returns value at index
	float&		operator [] (int index);								//Mutator; Returns address of index for assignment

	//Casts
	operator	float*();												//Mutator float pointer cast
	operator	const float*() const;									//Inspector float pointer cast

	//Dot
	float		dot(const Vector4 &other) const;						//Dot product
	float		dot(const Vector4 &a, const Vector4 &b);				//Dot product with non-members

	//Cross
	Vector4		cross(const Vector4 &other) const;						//Cross product
	Vector4		cross(const Vector4 &a, const Vector4 &b);				//Cross product with non-members

	//Angle between
	float		angleBetween(const Vector4 &other) const;				//Returns angle between this and another vector
	float		angleBetween(const Vector4 &a, const Vector4 &b);		//Returns angle between two vectors

	//Magnitude
	float		magnitude();											//Returns magnitude of vector
	float		magnitude(const Vector4 &vec);							//Returns magnitude of input vector
	float		magnitudeSqr() const;									//Squared magnitude squared for efficient comparison

	//Distance
	float		distance(const Vector4 &vec) const;						//Returns distance between this vector and another
	float		distance(const Vector4 &a, const Vector4 &b);			//Returns distance between two vectors
	float		distanceSqr(const Vector4 &vec) const;					//Returns distance squared for efficient comparison
	
	//Normalise
	void		normalise();											//Self normalise
	Vector4		normalised() const;										//Returns a normalised copy of this vector
	Vector4		normalised(const Vector4& vec);							//Returns a normalised copy of input vector
	
	//Absolute
	void		absolute();												//Self absolute
	Vector4		getAbsolute() const;									//Returns an absolute copy of current vector
	Vector4		getAbsolute(const Vector4 &vec);						//Returns an absolute copy of input vector
};