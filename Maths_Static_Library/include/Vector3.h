///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Vector3.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				A simple vector 3 class - Overloading opperators, Dot and Cross Product
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\====================================================================================================
//\ Vector3 - 3 Dimensional Vector Class 
//\====================================================================================================

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	//\----------------------------------------------------------------------------------
	//\ Member Variables 
	//\----------------------------------------------------------------------------------
	float x; float y; float z;

	//\----------------------------------------------------------------------------------
	//\ Constructors 
	//\----------------------------------------------------------------------------------
	Vector3();																	// Default Constructor
	Vector3(const float a_x, const float a_y, const float a_z);					// Custom Constructor (float values)
	Vector3(const Vector3& a_v3);												// Copy Constructor
	//\----------------------------------------------------------------------------------
	//\ Destructor 
	//\----------------------------------------------------------------------------------
	~Vector3();

//\====================================================================================================
// -- OPERATOR OVERLOADS
//\====================================================================================================
	//\----------------------------------------------------------------------------------
	//\ Equivalence Operators 
	//\----------------------------------------------------------------------------------
	bool				operator ==			(const Vector3& a_v3) const;
	bool				operator !=			(const Vector3& a_v3) const;
	//\----------------------------------------------------------------------------------
	//\ Negate Operator 
	//\----------------------------------------------------------------------------------
	const Vector3		operator -			()const ;
	//\----------------------------------------------------------------------------------
	//\ Addition Operators 
	//\----------------------------------------------------------------------------------
	Vector3				operator +			(const Vector3& a_v3) const;
	Vector3				operator +			(const float a_scalar) const;
	Vector3				operator +=			(const Vector3& a_v3);
	//\----------------------------------------------------------------------------------
	//\ Subtraction Operators 
	//\----------------------------------------------------------------------------------
	Vector3				operator -			(const Vector3& a_v3)const;

//\====================================================================================================
// -- VECTOR 3 FUNCTIONALITY
//\====================================================================================================

	//\----------------------------------------------------------------------------------
	//\ DOT Product Functionality 
	//\----------------------------------------------------------------------------------
	float				Dot(const Vector3& a_v3) const;
	friend float		Dot(const Vector3& a_v3A, const Vector3& a_v3B);
	//\----------------------------------------------------------------------------------
	//\ CROSS Product 
	//\----------------------------------------------------------------------------------
	Vector3				Cross(const Vector3& b) const;
	friend Vector3		Cross(const Vector3& a_v3A, const Vector3& a_v3B);
	//\----------------------------------------------------------------------------------
	//\ Multiplication Operators - Allows us to multiply Vector3 by a scalar Value
	//\----------------------------------------------------------------------------------
	Vector3				operator *			(const float& a_scalar) const;
	Vector3				operator *			(const Vector3& s_v30) const;
	//\----------------------------------------------------------------------------------
	//\ Get the Length of Vector 
	//\----------------------------------------------------------------------------------
	float				Length() const;
	//\----------------------------------------------------------------------------------
	//\ Normalize the Vector - modifies variables ( non const function 
	//\----------------------------------------------------------------------------------
	void				Normalize();
	friend Vector3		Normalize(const Vector3& a_vec3) ;
	//\----------------------------------------------------------------------------------
	//\ Linear Interpolate 
	//\----------------------------------------------------------------------------------
	friend Vector3		Lerp(const Vector3& a_v3A, const Vector3& a_v3B, const float a_t);
	//\----------------------------------------------------------------------------------
	//\ Reflect one Vector around another 
	//\----------------------------------------------------------------------------------
	friend Vector3		Reflect(const Vector3& a_v3A, const Vector3& a_v3B);
};
#endif