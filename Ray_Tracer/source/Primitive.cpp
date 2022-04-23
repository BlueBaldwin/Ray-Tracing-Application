///////////////////////////////////////////////////////////////////////////////////////////////////////
//\	File:				Primative.cpp
//\	Author:				Scott Baldwin
//\	Last Edited:		20-05-21
//\	Brief:				All of the objects our ray can intersect with.
//						All children classes will have their own Matrix4 for position, Rotation and Scale (stored as a Vector3) and
//						they will all be able to perform an intersection test between themselves and a ray projected into the scene
//\
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include "Primitive.h"
#include "Material.h"
//\------------------------

Primitive::Primitive() : m_Transform(Matrix4::IDENTITY), m_Scale()
{
}
Primitive::~Primitive()
{
}

// Get and Set primative matrix
Matrix4 Primitive::GetTransform() const
{
	return m_Transform;
}

void Primitive::SetTransform(const Matrix4& a_m4)
{
	m_Transform = a_m4;
}

Vector3 Primitive::GetPosition() const
{
	return m_Transform.GetColumnV3(3);
}

void Primitive::SetPosition(const Vector3& a_v3)
{
	m_Transform.SetColumnV3(3, a_v3);
}
// Get and set the position of the primative
Vector3 Primitive::GetScale() const
{
	return m_Scale;
}

void Primitive::SetScale(const Vector3& a_v3)
{
	m_Scale = a_v3;
	Matrix4 scale;
	scale.Scale(a_v3);
	m_Transform = m_Transform * scale;
}
//Matrix4 Primitive::GetShear() const
//{
//	return m_Shear;
//}
//void Primitive::SetShear(const float xy, float xz, float yx, float yz, float zx, float zy)
//{
//	m_shear = Shear(xy, xz, yx, yz, zx, zy);
//}

void Primitive::SetMaterial(Material* a_material)
{
	m_material = a_material;
}
