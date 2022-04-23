///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Vector4.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				A simple vector 4 class - Overloading opperators, Dot and Cross Product
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include <Math.h>

#include "Vector4.h"
//\------------------------

//\----------------------------------------------------------------------------------
//\ Default Constructor 
//\----------------------------------------------------------------------------------
Vector4::Vector4()
{
	x = 0.f; y = 0.f; z = 0.f; w = 0.f;
}
Vector4::Vector4(const float a_x, const float a_y, const float a_z, const float a_w)
{
	x = a_x;
	y = a_y;
	z = a_z;
	w = a_w;
}
//\----------------------------------------------------------------------------------
//\ Construct from Vector 3 
//\----------------------------------------------------------------------------------
Vector4::Vector4(const Vector3& a_v3, float a_w) :
	x(a_v3.x), y(a_v3.y), z(a_v3.z), w(a_w)
{
}
Vector4::Vector4(const Vector4& a_v4)
{
	x = a_v4.x;
	y = a_v4.y;
	z = a_v4.z;
	w = a_v4.w;
	
}
//\----------------------------------------------------------------------------------
//\ Destructor 
//\----------------------------------------------------------------------------------
Vector4::~Vector4()
{
}

//\====================================================================================================
// -- OPERATOR OVERLOADS
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Equivalence operators 
//\----------------------------------------------------------------------------------
bool Vector4::operator==(const Vector4& a_v4) const
{
	return ( x == a_v4.x && y == a_v4.y && z == a_v4.z && w == a_v4.w);
}

bool Vector4::operator!=(const Vector4& a_v4) const
{
	return (x != a_v4.x || y != a_v4.y || z != a_v4.z || w != a_v4.w);
}
//\----------------------------------------------------------------------------------
//\ Neg operator 
//\----------------------------------------------------------------------------------
const Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}
//\----------------------------------------------------------------------------------
//\ Overload Operators for Vector4 Addition 
//\----------------------------------------------------------------------------------
Vector4 Vector4::operator+(const Vector4& a_v4) const
{
	return Vector4(x + a_v4.x, y + a_v4.y, z + a_v4.z, w + a_v4.w);
}
Vector4 Vector4::operator+(const float a_scalar) const
{
	return Vector4(x + a_scalar, y + a_scalar, z + a_scalar, w + a_scalar);
}

Vector4	Vector4::operator +=	(const Vector4& a_v4)
{
	x += a_v4.x;
	y += a_v4.y;
	z += a_v4.z;
	w += a_v4.w;
	return *this;
}

//\----------------------------------------------------------------------------------
//\ Overload Operators for Vector4 Subtraction 
//\----------------------------------------------------------------------------------
Vector4 Vector4::operator-(const Vector4& a_v4) const
{
	return Vector4(x - a_v4.x, y - a_v4.y, z - a_v4.z, w - a_v4.z);
}
Vector4 Vector4::operator-(const float a_scalar) const
{
	return Vector4(x - a_scalar, y - a_scalar, z - a_scalar, w - a_scalar);
}
//\----------------------------------------------------------------------------------
//\ Overload Operators for Vector4 Multiplication 
//\----------------------------------------------------------------------------------
Vector4 Vector4::operator*(const float& a_scalar) const
{
	return Vector4( x * a_scalar, y * a_scalar, z * a_scalar, w * a_scalar);
}
//\----------------------------------------------------------------------------------

//\====================================================================================================
// -- VECTOR 4 FUNCTIONALITY
//\====================================================================================================

//\----------------------------------------------------------------------------------

//\ Dot Product - Vector4 (Cosine value of angle between the two vectors
//\ Will only work if w is not two points 
//\----------------------------------------------------------------------------------
float Vector4::Dot(const Vector4& a_v4) const
{
	return (x * a_v4.x + y * a_v4.y + z * a_v4.z + w * a_v4.w);
}
//\----------------------------------------------------------------------------------
//\ Dot Product - Vector 4 Friend Function 
//\----------------------------------------------------------------------------------
float Dot(const Vector4& a_v4A, const Vector4& a_v4B)
{
	return a_v4A.Dot(a_v4B);
}
//\----------------------------------------------------------------------------------
//\ Vector4 Length Calculation 
//\----------------------------------------------------------------------------------
float Vector4::Length() const
{
	return sqrtf( x * x + y * y + z * z + w * w);
}
//\----------------------------------------------------------------------------------
//\ Normalising 
//\----------------------------------------------------------------------------------
void Vector4::Normalize()
{
	float length = Length();
	// If check to ensure vector has length to Normalize
	if (length > 0.f)
	{
		float nLength = 1.f / length;
		x *= nLength;
		y *= nLength;
		z *= nLength;
		w *= nLength;
	}
}
Vector4 Normalize(const Vector4& a_vec4)
{
	float magnitude = a_vec4.Length();
	if (magnitude > 0.f)
	{
		return Vector4(a_vec4.x / magnitude, a_vec4.y / magnitude, a_vec4.z / magnitude, a_vec4.w / magnitude);
	}
	return Vector4(0.f, 0.f, 0.f, 0.f);
}
//\----------------------------------------------------------------------------------
//\ LERP - Linear Interpolation 
//\----------------------------------------------------------------------------------
Vector4 Lerp(const Vector4 a_v4A, const Vector4& a_v4B, const float a_t)
{
	return (a_v4B - a_v4A) * a_t + a_v4A;
}

Vector3 Vector4::xyz() const
{
	return Vector3(x, y, z);
}