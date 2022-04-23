///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				IntersectionResponse.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				A small structure to conatin all the rays hit variables; 
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once 
#ifndef IntersectionResponse_H

#include <MathLib.h>
class Material;

struct IntersectResponse
{
	Vector3		HitPos;					// The location in worldspace of the intersection
	Vector3		SurfaceNormal;			// The surface normal at the intersection location
	bool		frontFace;				// The distance to the hit location
	float		distance;				// The distance to the hit location
	Material*	material;				// The material property of the intersected object
	float		currentRefInd;			// current refractive index
};

#endif // !IntersectionResponse_H