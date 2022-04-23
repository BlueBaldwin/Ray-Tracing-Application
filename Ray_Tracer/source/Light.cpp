///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Light.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				It is the base class for all lighting that we will implemented within the scene. This base abstract 
//						class has a simple implementation where we set and get functions of the member variables of the 
//						light (matrix, and colour), as well as being able to set the position of the transform 
//						directly. All surfaces that faces the direction of a light will be lit.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include "Light.h"
//\------------------------

//\----------------------------------------------------------------------------------
//\ -- Constructors / Destructors
//\----------------------------------------------------------------------------------
Light::Light() : m_Transform(Matrix4::IDENTITY), m_colourRGB(1.f, 1.f, 1.f)
{
}
Light::Light(const Matrix4& a_transform, const ColourRGB& a_colour) : m_Transform(a_transform), m_colourRGB(a_colour)
{
}
Light::~Light()
{
}

//\----------------------------------------------------------------------------------
//\ Lighting Functions
//\----------------------------------------------------------------------------------
Vector3 Light::GetDirectionToLight(const Vector3& a_point) const
{
	return Normalize(GetPosition() - a_point);
}

//\----------------------------------------------------------------------------------
// -- GETTERS AND SETTERS
//\----------------------------------------------------------------------------------
Matrix4 Light::GetTransform() const
{
	return m_Transform;
}
void Light::SetTransform(const Matrix4& a_m4)
{
	m_Transform = a_m4;
}
// Get and set the position of the light
Vector3 Light::GetPosition() const
{
	return m_Transform.GetColumnV3(3);
}

void Light::SetPosition(const Vector3& a_v3)
{
	m_Transform.SetColumnV3(3, a_v3);
}
