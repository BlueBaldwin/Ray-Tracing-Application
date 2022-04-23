///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Ellipsoid.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				A dedicated Ellipsoid class derived from Primiative. Using the scale vector variable in the base class to control
//						scalling of the Ellipsoids radius in all three dimensions.				
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PRIMATIVE_H

//\------------------------
//\ INCLUDES
//\------------------------
#include "Primitive.h"
//\------------------------

class Ellipsoid : public Primitive
{
public:
	Ellipsoid();
	Ellipsoid(const Vector3& a_pos, const float& a_radius);
	virtual ~Ellipsoid();

	// This function will Override the Ellipsoid class will be used in place of the function in the base Primitive class
	bool IntersectTest(const Ray& a_ray, IntersectResponse& a_intersectResponse) const override;
	Vector3 m_colour;

private:
	float m_radius;
	
};
#endif // !PRIMATIVE_H