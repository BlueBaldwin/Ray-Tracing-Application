///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Material.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				This class is used to describe the properties of an objects surface and how that surface behaves 
//						while being illuminated by light. Lighting and material properties: Ambient, diffuse, specular, roughness, 
//						reflectiveness, transparency and refractive Index.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include <Random.h>
#include "Material.h"
#include "IntersectionResponse.h"
//\------------------------

class Material;

// Refraction Calculation
bool Material::CalcReflection(const Ray& a_in, const IntersectResponse& a_ir, Ray& a_out) const
{
	// Generate a random vector in range -1 - 1 for all components 
	Vector3 randomUnitVec = Vector3(Random::RandomRange(-1.f, 1.f), Random::RandomRange(-1.f, 1.f), Random::RandomRange(-1.f, 1.f));
	randomUnitVec.Normalize();
	// Reflected Ray, from hit location 
	Vector3 reflected = Normalize(Reflect(a_in.Direction(), a_ir.SurfaceNormal));
	// Add the random unit vector to the reflected ray based on roughness if smooth then no randomness
	a_out = Ray(a_ir.HitPos, reflected + (randomUnitVec * m_roughness), 0.001f);
	// Return a true if we have not reflected into the surface
	return (Dot(a_out.Direction(), a_ir.SurfaceNormal) > 0.f);
}
// Refraction Calculation
bool Material::CalcRefraction(const Ray& a_in, const IntersectResponse& a_ir, Ray& a_out) const
{
    // Generate a random vector in range -1 : 1 for all components
    Vector3 randomUnitVec = Vector3(Random::RandomRange(-1.f, 1.f), Random::RandomRange(-1.f, 1.f), Random::RandomRange(-1.f, 1.f));
    randomUnitVec.Normalize();											// Ensure Vector is Normalised to make vector unit vector
    // refract the ray from the hit location
    // For this we will assume that on leaving an object the ray enters air refractive index of 1.0
    float refraction_ratio = a_ir.frontFace ? (a_ir.currentRefInd / m_refractiveIndex) : m_refractiveIndex / a_ir.currentRefInd;    // Inversion of n/n1 from snells law
    float cos_i = Dot(-a_in.Direction(), a_ir.SurfaceNormal);									// Angle of incidence from Dot Product

    float sin2_t = refraction_ratio * refraction_ratio * (1.f - cos_i * cos_i);					// sin(theta_t^2 outgoing angle of refracted ray
	if (sin2_t > 1.f) return false;
	float cos_t = sqrtf(fabsf(1.f - sin2_t));
	// Compute direction of outgoing refracted ray
	Vector3 refracted = a_ir.SurfaceNormal * (refraction_ratio * cos_i - cos_t) + a_in.Direction() * refraction_ratio;
	a_out = Ray(a_ir.HitPos, refracted + (randomUnitVec * m_roughness), 0.001f);				//Outgoing refracted ray

	return true;
}

float Material::Schlick(const Ray& a_in, const IntersectResponse& a_ir) const
{
	float cos_i = Dot(-a_in.Direction(), a_ir.SurfaceNormal);
	float refraction_ratio = a_ir.frontFace ? (a_ir.currentRefInd / m_refractiveIndex) : m_refractiveIndex / a_ir.currentRefInd;
	// Calculate Schlicks approximation for Fresnel value
	// Total internal reflection index 1 > refractive index 2
	bool internalReflection = (a_ir.frontFace) ? (a_ir.currentRefInd > m_refractiveIndex) : (m_refractiveIndex > a_ir.currentRefInd);
	{
		float sin2_t = refraction_ratio * refraction_ratio * (1.f - cos_i * cos_i);				// sin (theta_t)^2 outgoing angle of refracted ray
		if (sin2_t > 1.f)																		// Total internal rotation
		{
			return 1.f;
		}
		cos_i = sqrtf(1.f - sin2_t);															// use cos_t instead of cos_i
	}
	float r0 = (1.f - refraction_ratio) / (1.f + refraction_ratio);								// Schlicks approximation
		r0 = r0 * r0;
		return r0 + (1.f - r0) * powf(1.f - cos_i, 5);
}
