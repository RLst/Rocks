//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once

class Vector2;
class Vector4;

class Vector3
{
	static const float DEFAULT_TOLERANCE;	//Have to set the value in the cpp file
public:
	union
	{
		//Standard
		struct {
			float x, y;
			union {	//Homogeneous
				float z;
				float w;
			};
		};

		//Rotation
		struct {
			float xa, ya, za;
		};

		//Colour
		struct {
			float r, g, b;
		};

		//Array
		float data[3];
	};
	static const float DEF_TOLERANCE;

	Vector3();															//Default
	Vector3(float x, float y, float z);									//Initialiser
	Vector3(const Vector2 &other);										//2D Copy Constructor
	Vector3(const Vector3 &other);										//3D Copy Constructor
	Vector3(const Vector4 &other);										//4D Copy Constructor
	~Vector3();															//Destructor

	//Operators
	Vector3		operator - () const;									//UNARY minus
	Vector3		operator + (const Vector3 &other) const;				//Point/Vector to Vector add (point translated by a vector)
	Vector3		operator - (const Vector3 &other) const;				//Point/Vector to Vector subtract (point translated by a vector)
	
	Vector3		operator * (float scalar) const;						//POST Scalar multiply (vector scale)
	Vector3		operator / (float scalar) const;						//POST Scalar divide (vector scale)
	friend Vector3 operator * (float scalar, const Vector3 &other);		//PRE Scalar multiply (vector scale)

	Vector3&	operator += (const Vector3 &other);						//Point/Vector to Vector add assign
	Vector3&	operator -= (const Vector3 &other);						//Point/Vector to Vector subtract assign
	Vector3&	operator *= (float scalar);								//Scalar multiply assign
	Vector3&	operator /= (float scalar);								//Scalar divide assign

	Vector3&	operator = (const Vector3 &other);						//Assignment
	bool		operator == (const Vector3 &other);						//Equality check
	bool		operator != (const Vector3 &other);						//Inequality check
	bool		equal(const Vector3 &other, float tolerance = DEF_TOLERANCE);			//Equality check with tolerance
	bool		notEqual(const Vector3 &other, float tolerance = DEF_TOLERANCE);		//Inequality check with tolerance

	//Subscript
	float		operator [] (int index) const;							//Inspector; Returns value at index
	float&		operator [] (int index);								//Mutator; Returns address of index for assignment

	//Casts
	operator	float*();												//Mutator float pointer cast
	operator	const float*() const;									//Inspector float pointer cast

	//Dot
	float		dot(const Vector3 &other) const;						//Dot product
	float		dot(const Vector3 &a, const Vector3 &b);				//Dot product with non-members

	//Cross
	Vector3		cross(const Vector3 &other) const;						//Cross product
	Vector3		cross(const Vector3 &a, const Vector3 &b);				//Cross product with non-members

	//Angle between
	float		angleBetween(const Vector3 &other) const;				//Returns angle between this and another vector
	float		angleBetween(const Vector3 &a, const Vector3 &b);		//Returns angle between two vectors

	//Magnitude
	float		magnitude();											//Returns magnitude of vector
	float		magnitude(const Vector3 &vec);							//Returns magnitude of input vector
	float		magnitudeSqr() const;									//Squared magnitude squared for efficient comparison
	
	//Distance
	float		distance(const Vector3 &other) const;					//Returns distance between this vector and another
	float		distance(const Vector3 &a, const Vector3 &b);			//Returns distance between two vectors
	float		distanceSqr(const Vector3 &vec) const;					//Returns distance squared for efficient comparison

	//Normalise
	void		normalise();											//Self normalise
	Vector3		normalised() const;										//Returns a normalised copy of this vector
	Vector3		normalised(const Vector3 &vec);							//Returns a normalised copy of input vector; FAULTY FUNCTION

	//Absolute
	void		absolute();												//Self absolute
	Vector3		getAbsolute() const;									//Returns an absolute copy of current vector
	Vector3		getAbsolute(const Vector3 &vec) const;					//Returns an absolute copy of input vector; FAULTY FUNCTION
};