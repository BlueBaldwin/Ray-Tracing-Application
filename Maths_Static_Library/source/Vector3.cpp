///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Vector3.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				A simple vector 3 class - Overloading opperators, Dot and Cross Product
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include "Vector3.h"
#include "math.h"
//\------------------------

//\====================================================================================================
//\ Vector2 - 2 Dimensional Vector Class 
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Default Constructor 
//\----------------------------------------------------------------------------------
Vector3::Vector3()
{
	x = 0.f; y = 0.f; z = 0.f;
}
//\----------------------------------------------------------------------------------
//\ Constructor with X, Y Values
//\----------------------------------------------------------------------------------
Vector3::Vector3(const float a_x, const float a_y, const float a_z)
{
	x = a_x;
	y = a_y;
	z = a_z;
}
//\----------------------------------------------------------------------------------
//\ Copy constructor 
//\----------------------------------------------------------------------------------
Vector3::Vector3(const Vector3& a_v3)
{
	x = a_v3.x;
	y = a_v3.y;
	z = a_v3.z;
}
//\----------------------------------------------------------------------------------
//\ Destructor 
//\----------------------------------------------------------------------------------
Vector3::~Vector3()
{
	//nothing new, nothing to delete
}

//\====================================================================================================
// -- OPERATOR OVERLOADS
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Equivalence operators
//\----------------------------------------------------------------------------------
bool Vector3::operator==(const Vector3& a_v3) const
{
	return ( x == a_v3.x && y == a_v3.y && z == a_v3.z);
}
bool Vector3::operator!=(const Vector3& a_v3) const
{
	return (x != a_v3.x || y != a_v3.y || z != a_v3.z);
}
//\----------------------------------------------------------------------------------
//\ Negate
//\----------------------------------------------------------------------------------
const Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}
//\----------------------------------------------------------------------------------
//\ Addition + Subtraction -
//\----------------------------------------------------------------------------------
Vector3 Vector3::operator+(const Vector3& a_v3) const
{
	return Vector3(x + a_v3.x, y + a_v3.y, z + a_v3.z);
}
Vector3			Vector3::operator -			(const Vector3& a_v3)const
{
	return Vector3(x - a_v3.x, y - a_v3.y, z - a_v3.z);
}
Vector3 Vector3::operator+(const float a_scalar) const
{
	return Vector3(x + a_scalar, y + a_scalar, z + a_scalar);
}

Vector3	Vector3::operator +=	(const Vector3& a_v3)
{
	x += a_v3.x;
	y += a_v3.y;
	z += a_v3.z;
	return *this;
}
//\----------------------------------------------------------------------------------
//\ MULTIPLICATION
//\----------------------------------------------------------------------------------
Vector3 Vector3::operator*(const float& a_scalar) const
{
	return Vector3(x * a_scalar, y * a_scalar, z * a_scalar);
}
Vector3 Vector3::operator*(const Vector3& a_v3) const
{
	return Vector3(a_v3.x * x, a_v3.y * y, a_v3.z * z);
}

//\====================================================================================================
// -- VECTOR 4 FUNCTIONALITY
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Dot Product - projection of one vector along another 
//\				  or the cosine value of the angle between two vectors 
//\----------------------------------------------------------------------------------
float Vector3::Dot(const Vector3& a_v3) const
{
	return (x * a_v3.x + y * a_v3.y + z * a_v3.z);
}
//\----------------------------------------------------------------------------------
//\ Dot Product - Freind function allows use to do the following in code 
//\				  Vector2 result = Dot( vec2A, vec2B );		
//				  notice the lack of "Vector2::" prior to the function name 
//\----------------------------------------------------------------------------------
float Dot(const Vector3& a_v3A, const  Vector3& a_v3B)
{
	return a_v3A.Dot(a_v3B);
}
//\----------------------------------------------------------------------------------
//\ CROSS PRODUCT 
//\----------------------------------------------------------------------------------
Vector3 Vector3::Cross( const Vector3& b) const 
{
	return Vector3 (y*b.z - z*b.y,
					z*b.x - x*b.z,
					x*b.y - y*b.x);
}
Vector3 Cross(const Vector3& a_v3A, const  Vector3& a_v3B)
{
	return a_v3A.Cross(a_v3B);
}

//\----------------------------------------------------------------------------------
//\ Get the length (Magnitude) of the Vector 
//\----------------------------------------------------------------------------------
float Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);		
}
//\----------------------------------------------------------------------------------
//\ Normalize the Vector
//\----------------------------------------------------------------------------------
void Vector3::Normalize()
{
	float length = Length();
	if (length > 0.f)				// If this is false Vector has no length
	{
		float invLen = 1.f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
	}
}
Vector3 Normalize(const Vector3& a_vec3)  
{
	Vector3 n( 0.f, 0.f, 0.f);
	float length = a_vec3.Length();
	if (length > 0.f)				// If this is false Vector has no length
	{
		
		float invLen = 1.f / length;
		n.x = a_vec3.x * invLen;
		n.y = a_vec3.y * invLen;
		n.z = a_vec3.z * invLen;
	}
	return n;
}
//\----------------------------------------------------------------------------------
//\ LERP - Linear Interpolate 
//\----------------------------------------------------------------------------------
Vector3 Lerp(const Vector3& a_v3A, const Vector3& a_v3B, const float a_t)
{
	return (a_v3B - a_v3A) * a_t + a_v3A;
}
//\----------------------------------------------------------------------------------
//\ REFLECT - one Vector around another 
//\----------------------------------------------------------------------------------
Vector3 Reflect(const Vector3& a_v3A, const Vector3& a_v3B)
{
	Vector3 reflect = a_v3A - a_v3B * 2.f * Dot(a_v3A, a_v3B);
	return reflect;
}

