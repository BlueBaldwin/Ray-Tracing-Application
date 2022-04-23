///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				DirectionalLight.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				The directional light accepts a directional vector that will be used to set the forward facing direction 
//						of the lights transform Matrix.
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include "Light.h"
#include "IntersectionResponse.h"
#include "MathUtil.h"
//\------------------------

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(const Matrix4& a_transform, const Vector3& a_colour, const Vector3& a_facing);
	virtual ~DirectionalLight();
	// Override the base light class' calculate lighting function
	ColourRGB calculateLighting(const IntersectResponse& a_intersectResponse, const Vector3& a_eyePos, float a_shadowFactor = 1.0) const override;

	// Functionality to set and get the direction of the light
	void SetDirection(const Vector3& a_direction, const Vector3& a_up = Vector3(0.f, 1.f, 0.f));
	Vector3 GetDirection() const;
	Vector3 GetDirectionToLight(const Vector3& a_point = Vector3(0.f, 0.f, 0.f)) const override;
	
protected:
	// Directional Light no additional variables used fwd direction from a_transform for direction.
};
