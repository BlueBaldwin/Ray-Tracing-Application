﻿///////////////////////////////////////////////////////////////////////////////////////////////////////
//\====================================================================================================
//\ Vector4 4 Dimensional Vector Class 
//\====================================================================================================
//\	File:				Vector4.h
//\	Author:				Scott Baldwin
//\	Last Edited:		20-05-21
//\	Brief:				A simple vector 4 class - Overloading opperators, Dot and Cross Product
//\
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR4_H
#define VECTOR4_H

//\------------------------
//\ INCLUDES
//\------------------------
#include "Vector3.h"
//\------------------------

class Vector4
{
	public:
	//\----------------------------------------------------------------------------------
	//\ Member variables 
	//\----------------------------------------------------------------------------------
	float x; float y; float z; float w;
	//\----------------------------------------------------------------------------------
	//\ Constructors 
	//\----------------------------------------------------------------------------------
	Vector4();																		// Default Constructor
	Vector4(const float a_x, const float a_y, const float a_z, const float a_w);	// Custom Constructor (float values)
	Vector4(const Vector3& a_v3, float a_w = 0.f);									// Copy Constructor - initialising w to 0
	Vector4(const Vector4& a_v4);													// Copy Constructor	
	//\----------------------------------------------------------------------------------	
	//\ Destructor 
	//\----------------------------------------------------------------------------------
	~Vector4();

//\====================================================================================================
// -- OPERATOR OVERLOADS
//\====================================================================================================
	//\----------------------------------------------------------------------------------
	//\ Equivalence Operators 
	//\----------------------------------------------------------------------------------
	bool			operator ==				(const Vector4& a_v4) const;
	bool			operator !=				(const Vector4& a_v4) const;
	//\----------------------------------------------------------------------------------
	//\ Negate operator 
	//\----------------------------------------------------------------------------------
	const Vector4	operator -				() const;
	//\----------------------------------------------------------------------------------
	//\ Addition Operators 
	//\----------------------------------------------------------------------------------
	Vector4			operator +				(const Vector4& a_v4) const;
	Vector4			operator +				(const float a_scalar) const;

	Vector4			operator +=				(const Vector4& a_v4) ;
	//\----------------------------------------------------------------------------------
    //\ Subtraction Operators 
	//\----------------------------------------------------------------------------------
    Vector4			operator -				(const Vector4& a_v4) const;
	Vector4			operator -				(const float a_scalar) const;
	//\----------------------------------------------------------------------------------
	//\ Multiplication Operators 
	//\----------------------------------------------------------------------------------
	Vector4			operator *				(const float& a_scalar) const;
	//\----------------------------------------------------------------------------------
	
//\====================================================================================================
// -- VECTOR 4 FUNCTIONALITY
//\====================================================================================================

	//\----------------------------------------------------------------------------------
	//\ Dot Product  
	//\----------------------------------------------------------------------------------
	float					Dot(const Vector4& a_v4) const;
	friend float			Dot(const Vector4& a_v4A, const Vector4& a_v4B);
	//\----------------------------------------------------------------------------------
	//\ Get Length of Vector 
	//\----------------------------------------------------------------------------------
	float					Length() const;
	//\----------------------------------------------------------------------------------
	//\ Normalize the Vector - modifies member variables (non const function)
	//\----------------------------------------------------------------------------------
	void					Normalize();
	friend Vector4			Normalize(const Vector4& a_vec4);
	//\----------------------------------------------------------------------------------
	//\ Linear Interpolation 
	//\----------------------------------------------------------------------------------
	friend Vector4			Lerp(const Vector4 a_v4A, const Vector4& a_v4B, const float a_t);

	//\----------------------------------------------------------------------------------
	// make Vector 4 into Vector 3
	//\----------------------------------------------------------------------------------
	Vector3 xyz() const;
};
#endif // !VECTOR4_H