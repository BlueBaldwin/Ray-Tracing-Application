///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				DirectionalLight.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				The directional light accepts a directional vector that will be used to set the forward facing direction 
//						of the lights transform Matrix.
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include <cmath>
#include "DirectionalLight.h"
#include "MathUtil.h"
#include "Material.h"
//\------------------------

DirectionalLight::DirectionalLight()
{
	SetDirection(Vector3(0.f, 0.f, 0.f));
}

DirectionalLight::DirectionalLight(const Matrix4& a_transform, const Vector3& a_colour, const Vector3& a_facing)
	: Light(a_transform, a_colour)
{
	SetDirection(a_facing);	
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SetDirection(const Vector3& a_direction, const Vector3& a_up)
{
	m_Transform.SetColumnV3(2, a_direction);
	m_Transform.SetColumnV3(1, a_up);
	m_Transform.Orthonormalise();
}

Vector3 DirectionalLight::GetDirection() const
{
	return m_Transform.GetColumnV3(2);
}

//\----------------------------------------------------------------------------------
//\ Light Implementation - Main function to calculate the lighting
//\----------------------------------------------------------------------------------
ColourRGB DirectionalLight::calculateLighting(const IntersectResponse& a_intersectResponse, const Vector3& a_eyePos, float a_shadowFactor) const
{
	// Work out diffuse -- treat all surfaces the same under this light
	// Ambient = 0.2f;
	// Diffuse = 0.8f;
	// Specular = 0.8f;
	// Specular factor - 200.f;

	// Calculate effective light colour for the diffuse channel (and metallic specular )
	Vector3 effectiveColour = m_colourRGB * a_intersectResponse.material->GetAlbedo();

	ColourRGB ambient = effectiveColour * a_intersectResponse.material->GetAmbient();								//Get ambient colour for surface
	// Light direction is forward axis of light matrix				
	Vector3 lightDirection = -GetDirection();																		// Get direction to light from surace
	float lightDiffuse = MathUtil::Max(0.f, Dot(lightDirection, a_intersectResponse.SurfaceNormal));				// Positive values indicate factors in same dir
	ColourRGB diffuse = effectiveColour * a_intersectResponse.material->GetDiffuse() * lightDiffuse;				// Blend light diffuse with diffuse value and colour														// Blend light diffuse with diffuse value and colour
	// Calculate light specular value
	// For non-metals material colour plays no part in specular highlight
	Vector3 eyeDir = Normalize(a_intersectResponse.HitPos - a_eyePos);												// Get the dir from view to surface
	Vector3 reflectionVec = Reflect(eyeDir, a_intersectResponse.SurfaceNormal);										// Get the reflection vector of the eye around normal
	float specularPower = (1.0f - a_intersectResponse.material->GetRoughness()) * 254.f + 1.0f;
	float specularFactor = std::powf(MathUtil::Max(0.f, Dot(reflectionVec, lightDirection)), specularPower);		// Get the specular value
	ColourRGB specular = m_colourRGB * a_intersectResponse.material->GetSpecular() * specularFactor;

	return ambient + (diffuse + specular) * a_shadowFactor;
}

Vector3 DirectionalLight::GetDirectionToLight(const Vector3& a_point) const
{
	return GetDirection();
}
