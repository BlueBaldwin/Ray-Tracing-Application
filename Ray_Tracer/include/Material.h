///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Material.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				This class is used to describe the properties of an objects surface and how that surface behaves 
//						while being illuminated by light. Lighting and material properties: Ambient, diffuse, specular, roughness, 
//						reflectiveness, transparency and refractive Index.
//						
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
#define MATERIAL_H
#pragma once

//\------------------------
//\ INCLUDES
//\------------------------
#include <mathLib.h>
#include "IntersectionResponse.h"
//\------------------------

//\===========================================================================================================
//\ An abstract base material class
//\===========================================================================================================

class Material
{
public:
	Material(const Vector3& a_albedo, float a_ambient, float a_diffuse, float a_specular, float a_roughness, float a_reflective, float a_transparency, float a_refractiveIndex) :
		m_albedo(a_albedo), m_ambient(a_ambient), m_diffuse(a_diffuse), m_specular(a_specular), m_roughness(a_roughness), m_reflective(a_reflective), m_transparency(a_transparency), m_refractiveIndex(a_refractiveIndex){};

	Material() : m_albedo(1.f, 1.f, 1.f), m_ambient(0.f), m_diffuse(0.f), m_specular(0.f), m_roughness(0.f), m_reflective(0.f), m_transparency(0.f), m_refractiveIndex(0.f) {};
	~Material() {};

	bool CalcReflection(const Ray& a_in, const IntersectResponse& a_ir, Ray& a_out) const;
	bool CalcRefraction(const Ray& a_in, const IntersectResponse& a_ir, Ray& a_out) const;

	//\----------------------------------------------------------------------------------
	//\ Getters and Setters 
	//\----------------------------------------------------------------------------------
	const Vector3 GetAlbedo() { return m_albedo; }
	void SetAlbedo(const Vector3& a_albedo) { m_albedo; }

	const float& GetAmbient() const { return m_ambient; }
	void SetAmbient(const float& a_ambient) { m_ambient = a_ambient; }

	const float& GetDiffuse() const { return m_diffuse; }
	void SetDiffuse(const float& a_diffuse) { m_diffuse = a_diffuse; }

	const float& GetSpecular() const { return m_specular; }
	void SetSpecular (const float& a_specular) { m_specular = a_specular; }

	const float& GetRoughness() const { return m_roughness; }
	void SetRoughness(const float& a_roughness) { m_roughness = a_roughness; }

	const float& GetReflective() const { return m_reflective; }
	void SetReflective(const float& a_reflective) { m_reflective = a_reflective; }

	const float& GetRefractiveIndex() const { return m_refractiveIndex; }
	void SetRefractiveIndex(const float& a_refractiveIndex) { m_refractiveIndex = a_refractiveIndex; }

	const float& GetTransparency() const { return m_transparency; }
	void SetTransparency(const float& a_transparency) { m_transparency = a_transparency; }

	float Schlick(const Ray& a_in, const IntersectResponse& a_ir) const;

protected:
	Vector3 m_albedo;						// Material Albedo colour - colour of light reflected from a surface
	float m_ambient;						// Ambient component of material 0 -> 1.0
	float m_diffuse;						// diffuse component of material 0 -> 1.0
	float m_specular;						// specular component of material 0 -> 1.0
	float m_roughness;						// Surface roughness of material 0 -> 1.0
	float m_reflective;						// reflectivity of a surface 0 -> 1.0
	float m_transparency;					// transparency of the surface 0 -> 1
	float m_refractiveIndex;				// refractive Index of the surface (how much light on entering/exiting a surface)
	
	// Refractive index of common materials.
											/*	Water (ice) 	1.31
												Glass (plate)	1.52
												Sapphire		1.778
												Cubic zirconia	2.18
												Tungsten		2.61
												Germanium		4.1*/
};