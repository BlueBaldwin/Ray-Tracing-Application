///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Ray.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				Ray - Class to store a 3D Ray. 
//						project rays into the screen from each pixel and create an image from the data that each ray collects.
//						
///////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//\------------------------
//\ INCLUDES
//\------------------------
#include <limits>

#include "Vector3.h"
//\------------------------

class Ray
{
private:
	//\----------------------------------------------------------------------------------
	//\ Member Variables 
	//\----------------------------------------------------------------------------------
	Vector3 m_v3Origin;				// Origin is start point of Ray
	Vector3 m_v3Direction;			// Direction is the direction of the ray
	float	m_MaxLength;			// Max Length is the maximal length the ray can project 
	float	m_MinLength;			// Min Length is the minimal length the ray can project 

public:
	//\----------------------------------------------------------------------------------
	//\ Constructors & Destructors
	//\----------------------------------------------------------------------------------
	Ray();
	Ray(const Ray& a_Ray);
	Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction, float a_MinLength = 0.f, float a_maxLength = std::numeric_limits<float>::max() );
	//\----------------------------------------------------------------------------------
	//\ Destructors 
	//\----------------------------------------------------------------------------------
	~Ray();

	//\----------------------------------------------------------------------------------
	//\ Getters 
	//\----------------------------------------------------------------------------------
	Vector3			Origin() const				{ return m_v3Origin; }
	Vector3			Direction() const			{ return m_v3Direction; }
	float			MaxDistance() const			{ return m_MaxLength; }
	float			MinLength() const			{ return m_MinLength; }

	//\----------------------------------------------------------------------------------
	//\ Point At - To return a point a specific distance along the ray
	//\----------------------------------------------------------------------------------
	Vector3			PointAt(float a_distance);		
	//\----------------------------------------------------------------------------------
	//\ Sphere Intersection test 
	//\----------------------------------------------------------------------------------
	float			IntersectSphere(const Vector3& a_center, const float a_radius);

	bool doesIntersectSphere(const Vector3& a_center, const float a_radius);
};

