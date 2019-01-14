//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once
class Vector3;

class Vector2
{
	static const float DEFAULT_TOLERANCE;
public:
	union
	{
		//Standard
		struct {
			float x, y;
		};

		//Angle and magnitude
		struct {
			float a, M;
		};

		//Rotation
		struct {
			float xa, ya;
		};

		//Array
		float data[2];
	};
	static const float DEF_TOLERANCE;

	Vector2();															//Default
	Vector2(float x, float y);											//Initialiser
	Vector2(const Vector2& other);										//Copy
	Vector2(const Vector3& other);										//3D Copy
	~Vector2();															//Destructor

	//Operators
	Vector2		operator - () const;									//UNARY minus
	Vector2		operator + (const Vector2 &other) const;				//Point/Vector to Vector add (point translated by a vector)
	Vector2		operator - (const Vector2 &other) const;				//Point/Vector to Vector subtract (point translated by a vector)

	Vector2		operator * (float scalar) const;					 	//POST Scalar multiply (vector scale)
	Vector2		operator / (float scalar) const;					 	//POST Scalar divide (vector scale)
	friend Vector2 operator * (float scalar, const Vector2 &other);		//PRE Scalar multiply (vector scale)

	Vector2&	operator += (const Vector2 &other);						//Point/Vector to Vector add assign
	Vector2&	operator -= (const Vector2 &other);						//Point/Vector to Vector subtract assign
	Vector2&	operator *= (float scalar);								//Scalar multiply assign
	Vector2&	operator /= (float scalar);								//Scalar divide assign

	Vector2&	operator = (const Vector2 &other);						//Assignment
	bool		operator == (const Vector2 &other);						//Equality check
	bool		operator != (const Vector2 &other);						//Inequality check
	bool		equal(const Vector2 &other, float tolerance = DEF_TOLERANCE);			//Equality check with tolerance
	bool		notEqual(const Vector2 &other, float tolerance = DEF_TOLERANCE);		//Inequality check with tolerance

	//Subscript
	float		operator [] (int index) const;							//Inspector; Returns value at index
	float&		operator [] (int index);								//Mutator; Returns address of index for assignment

	//Casts
	operator	float*();												//Mutator float pointer cast
	operator	const float*() const;									//Inspector float pointer cast

	//Dot
	float		dot(const Vector2 &other) const;						//Dot product
	float		dot(const Vector2 &a, const Vector2 &b);				//Dot product with non-members
																		
	//Perpendiculars
	Vector2		getPerpendRH() const;									//2D Cross product equivalent
	Vector2		getPerpendLH() const;									//2D Cross product equivalent

	//Angle between
	float		angleBetween(const Vector2 &other) const;				//Returns angle between this and another vector
	float		angleBetween(const Vector2 &a, const Vector2 &b);		//Returns angle between two vectors

	//Magnitude
	float		magnitude();											//Returns magnitude of vector
	float		magnitude(const Vector2 &vec);							//Returns magnitude of input vector
	float		magnitudeSqr() const;									//Squared magnitude squared for efficient comparison

	//Distance
	float		distance(const Vector2 &other) const;					//Returns distance between this vector and another
	float		distance(const Vector2 &a, const Vector2 &b);			//Returns distance between two vectors
	float		distanceSqr(const Vector2 &other) const;				//Returns distance squared for efficient comparison				 		
																		
	//Normalise															
	void		normalise();											//Self normalise
	Vector2		normalised() const;										//Returns a normalised copy of this vector
	Vector2		normalised(const Vector2 &vec);							//Returns a normalised copy of input vector							 		

	//Absolute
	void		absolute();												//Self absolute
	Vector2		getAbsolute() const;									//Returns an absolute copy of current vector
	Vector2		getAbsolute(const Vector2 &vec);						//Returns an absolute copy of input vector
};