///////////////////////////////////////////////////////////////////////////////////////////////////////
//\	File:				Primative.h
//\	Author:				Scott Baldwin
//\	Last Edited:		20-05-21
//\	Brief:				All of the objects our ray can intersect with.
//						All children classes will have their own Matrix4 for position, Rotation and Scale (stored as a Vector3) and
//						they will all be able to perform an intersection test between themselves and a ray projected into the scene
//\
///////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PRIMITIVE_H

//\------------------------
//\ INCLUDES
//\------------------------
#include <MathLib.h>
#include "IntersectionResponse.h"
//\------------------------

class Material;		// Forward declaration of the material class

class Primitive
{
public:
	//\====================================================================================================
	//\ Constrcutors / Access / Ellipsoid Property Functions
	//\====================================================================================================
	Primitive();
	virtual ~Primitive();
	// Function to test for intersection and ray - pure virtual only implemented in derived classes
	virtual  bool IntersectTest(const Ray& a_ray, IntersectResponse& a_intersectResponse) const = 0;

	// Get and set primative matrix
	Matrix4 GetTransform() const;
	void SetTransform(const Matrix4& a_m4);

	//Get and Set the position of the primative
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& a_v3);

	//Get and set he position of the primative
	Vector3 GetScale()const;
	void SetScale(const Vector3& a_v3);

	// Get and set the shear dimensions of the primative
	/*Matrix4 GetShear() const;
	void SetShear(float xy, float xz, float yx, float yz, float zx, float zy);*/

	//Get and set the material for this primative
	void SetMaterial(Material* a_material);
	const Material* GetMaterial() { return m_material; }

protected:
	Matrix4 m_Transform;		// Position scale and Rotation
	Vector3 m_Scale;			// Scale Vector
	Matrix4 m_Shear;			// Shear matrix values
	Material* m_material;		// Surface material for the primitive
};

#endif // !PRIMITIVE_H
