///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Ellipsoid.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				A dedicated Ellipsoid class derived from Primiative. Using the scale vector variable in the base class to control
//						scalling of the Ellipsoids radius in all three dimensions.				
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Ellipsoid.h"

Ellipsoid::Ellipsoid() : m_radius(1.f)
{	
}

Ellipsoid::Ellipsoid(const Vector3& a_position, const float& a_radius) : m_radius(a_radius)
{
	SetPosition(a_position);
	SetScale(Vector3(m_radius, m_radius, m_radius));
}

Ellipsoid::~Ellipsoid()
{
}

// Function to calculate the point of intersection with an ellipsoid and a ray
// Returns true if an intersection occurs, tests for intersections in front of the ray (not behind)
bool Ellipsoid::IntersectTest(const Ray& a_ray, IntersectResponse& a_intersectResponse) const
{
	// The normal matrix is the inverse transpose of the transform
	Matrix4 normalMatrix = m_Transform.GetTranspose().Inverse();

	Matrix4 invTx = m_Transform.Inverse();									//Get the inverse of the transform matrix
	Vector4 rayOrigin = invTx * Vector4(a_ray.Origin(), 1.f);				//Multiply ray origin by inverse to get in local space
	Vector4 rayDir = Normalize(invTx * Vector4(a_ray.Direction()));			//Get ray direction in local space

	Vector3 OC = rayOrigin.xyz();				//Vector from Ray Origin to Center of sphere
	float b = Dot(OC, rayDir.xyz());			//Dot product of direction with vector to center of sphere
	float c = Dot(OC, OC) - 1.f;				// Dot product of OC subtract radius squared (radius of 1 for unit sphere
	float discriminant = b * b - c;				// Discriminent part under sqrt of quadratic (b - c)
	if (discriminant < 0.f)
	{
		return false;							// If less than 0 we have no intersections
	}
	else
	{
		// test for both intersection points to see if intersection occurs behind ray origin
		// discard negative intersection distance as intersection occurs behind ray
		float dist = -1.f;						//Start with distance initiallised as a negative
		float i0 = -b - sqrt(discriminant);		//Complete negative part of the quadratic equation
		float i1 = -b + sqrt(discriminant);		//Complete positive part of quadratic equation

		if (i0 > 0.f)							// Is first intersection point in front of ray origin
		{
			dist = i0;
		}
		else if (i1 > 0.f)						// if first point not in front of origin is second intersection point
		{
			dist = i1;
		}
		else
		{		return false;		}			// Both intersection points behind ray origin

			// Now that we have chosen positive intersection point
			Vector4 hp = rayOrigin + rayDir * dist;											// Calculate hit point in local space to ellipsoid
			Vector3 sn = Normalize(hp.xyz());												// Normalize this point provides direction of surface normal
			hp = m_Transform * hp;															// Multiply point by transform matrix to get in world space
			a_intersectResponse.HitPos = Vector3(hp.x, hp.y, hp.z);							// Nearest hitpoint on surface of ellipsoid to ray
			a_intersectResponse.SurfaceNormal = (normalMatrix * sn).xyz();					// Convert Normal into world space normal by multiplying with normal matrix
			a_intersectResponse.SurfaceNormal.Normalize();									// Convert normal into world space by multiplying with normal matrix
			a_intersectResponse.frontFace = Dot(a_intersectResponse.SurfaceNormal,			// If Normal and incoming ray in same direction then not front on
				a_ray.Direction()) < 0.f;
			a_intersectResponse.distance = (a_ray.Origin() - hp.xyz()).Length();			// Record distance to intersection in intersection response
			a_intersectResponse.material = m_material;
			return true;																	// return true as ray intersected ellipsoid
		}
		return false;																		// No intersections here
	}

