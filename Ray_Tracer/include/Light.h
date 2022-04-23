///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Light.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				It is the base class for all lighting that we will implemented within the scene. This base abstract 
//						class has a simple implementation where we set and get functions of the member variables of the 
//						light (matrix, and colour), as well as being able to set the position part of the transform 
//						directly. All surfaces that faces the direction of a light will be lit.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//\------------------------
//\ INCLUDES
//\------------------------
#include <MathLib.h>
#include "ColourRGB.h"
#include "IntersectionResponse.h"
//\------------------------

class Light
{
public: 
	//\----------------------------------------------------------------------------------
	//\ -- Constructors / Destructors
	//\----------------------------------------------------------------------------------
	Light();
	Light(const Matrix4& a_transform, const ColourRGB& a_colour);
	virtual ~Light();

	//\----------------------------------------------------------------------------------
	//\ Lighting Functions
	//\----------------------------------------------------------------------------------
	// Type of light calculation for its own lighting outcome based off it's type
	virtual ColourRGB calculateLighting(const IntersectResponse& a_intersectResponse, const Vector3& a_eyePos, float a_shadowFactor = 1.0) const = 0;
	// Function to get the direction to the light from a light origin (a_point)
	virtual Vector3 GetDirectionToLight(const Vector3& a_point = Vector3(0.f, 0.f, 0.f)) const;
	
	//\----------------------------------------------------------------------------------
	// -- GETTERS AND SETTERS
	//\----------------------------------------------------------------------------------
	Matrix4 GetTransform() const;
	void SetTransform(const Matrix4& a_m4);
	//\----------------------------------------------------------------------------------
	// Get and set the position of the light
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& a_v3);
	//\----------------------------------------------------------------------------------
	// Set and get the colour of the light (Implemented here)
	const ColourRGB& GetColour()const { return m_colourRGB; }
	void SetColour(const ColourRGB& a_colour) { m_colourRGB = a_colour; }

protected:
	Matrix4 m_Transform;		// transform of the light
	ColourRGB m_colourRGB;		// Colour of the light

};
