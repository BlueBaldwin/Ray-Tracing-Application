///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Matrix4.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				Class that implements a 3 by 3 homogenous matrix in Column major Order 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include <cmath>

#include "Matrix4.h"
#include <math.h>
//\------------------------
#pragma region Constructors
//\----------------------------------------------------------------------------------
//\ Identity Matrix4 
//\----------------------------------------------------------------------------------
const Matrix4 Matrix4::IDENTITY = Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
//\----------------------------------------------------------------------------------
//\ Constructors 
//\----------------------------------------------------------------------------------
Matrix4::Matrix4() : m_11(1.f), m_12(0.f), m_13(0.f), m_14(0.f),
					 m_21(0.f), m_22(1.f), m_23(0.f), m_24(0.f),
					 m_31(0.f), m_32(0.f), m_33(1.f), m_34(0.f),
					 m_41(0.f), m_42(0.f), m_43(0.f), m_44(1.f)
{
}
//\----------------------------------------------------------------------------------
//\ Constructor using pointer to float data 
//\----------------------------------------------------------------------------------
Matrix4::Matrix4(const float* a_mat) :

					m_11(a_mat[0]), m_21(a_mat[1]), m_31(a_mat[2]), m_41(a_mat[3]),
					m_12(a_mat[4]), m_22(a_mat[5]), m_32(a_mat[6]), m_42(a_mat[7]),
					m_13(a_mat[8]), m_23(a_mat[9]), m_33(a_mat[10]), m_43(a_mat[11]),
					m_14(a_mat[12]), m_24(a_mat[13]), m_34(a_mat[14]), m_44(a_mat[15])
{
}
//\----------------------------------------------------------------------------------
//\ Constructor using all components of matrix data structure 
//\----------------------------------------------------------------------------------
Matrix4::Matrix4	(float m11, float m21, float m31, float m41,
					float m12, float m22, float m32, float m42,
					float m13, float m23, float m33, float m43,
					float m14, float m24, float m34, float m44):
					m_11(m11), m_21(m21), m_31(m31), m_41(m41),
					m_12(m12), m_22(m22), m_32(m32), m_42(m42),
					m_13(m13), m_23(m23), m_33(m33), m_43(m43),
					m_14(m14), m_24(m24), m_34(m34), m_44(m44)
{
}
//\----------------------------------------------------------------------------------
//\ Copy Constructor
//\----------------------------------------------------------------------------------
Matrix4::Matrix4(const Matrix4& a_m4) :
					m_11(a_m4.m_11), m_21(a_m4.m_21), m_31(a_m4.m_31), m_41(a_m4.m_41),
                    m_12(a_m4.m_12), m_22(a_m4.m_22), m_32(a_m4.m_32), m_42(a_m4.m_42),
                    m_13(a_m4.m_13), m_23(a_m4.m_23), m_33(a_m4.m_33), m_43(a_m4.m_43),
                    m_14(a_m4.m_14), m_24(a_m4.m_24), m_34(a_m4.m_34), m_44(a_m4.m_44)
{
}

//\----------------------------------------------------------------------------------
//\ Destructor 
//\----------------------------------------------------------------------------------
Matrix4::~Matrix4()
{
}
#pragma endregion
#pragma region Operator_Overloads
//\====================================================================================================
// -- OPERATOR OVERLOADS 
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Member Variable access operator overload 
//\----------------------------------------------------------------------------------
#include <cassert> // Allows our program to assert if the collumn or row is outside the scope of the Matrix class
float& Matrix4::operator()(int a_iColumn, int a_iRow)
{
	// Make sure that column and row are within range			
	assert(a_iColumn >= 0 && a_iColumn < 4);
	assert(a_iRow >= 0 && a_iRow < 4);
	return m[a_iColumn ][a_iRow];
}
float Matrix4::operator()(int a_iColumn, int a_iRow) const
{
	assert(a_iColumn >= 0 && a_iColumn < 4);
	assert(a_iRow >= 0 && a_iRow < 4);
	return m[a_iColumn ][a_iRow];
}
//\----------------------------------------------------------------------------------
//\ Column and Row Access 
//\----------------------------------------------------------------------------------
void Matrix4::SetColumnV3(int a_iCol, const Vector3& a_vCol)
{
	assert(a_iCol >= 0 && a_iCol < 4);
	m[a_iCol][0] = a_vCol.x; m[a_iCol][1] = a_vCol.y; m[a_iCol][2] = a_vCol.z;
}
Vector3 Matrix4::GetColumnV3(int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 4);
	return Vector3(m[a_iCol][0], m[a_iCol][1], m[a_iCol][2]);
}

void Matrix4::SetColumnV4(int a_iCol, const Vector4& a_vCol)
{
	assert(a_iCol >= 0 && a_iCol < 4);
	m[a_iCol][0] = a_vCol.x; m[a_iCol][1] = a_vCol.y; m[a_iCol][2] = a_vCol.z; m[a_iCol][3] = a_vCol.w;
}
Vector4 Matrix4::GetColumnV4(int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 4);
	return Vector4(m[a_iCol][0], m[a_iCol][1], m[a_iCol][2], m[a_iCol][3]);
}

//\----------------------------------------------------------------------------------
//\ EQUIVALENCE - Operator Overload - Matrix Testing for equality 
//\----------------------------------------------------------------------------------
bool Matrix4::operator==(const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11) { return false; }
	if (m_21 != a_m4.m_21) { return false; }
	if (m_31 != a_m4.m_31) { return false; }
	if (m_41 != a_m4.m_41) { return false; }
	
	if (m_12 != a_m4.m_12) { return false; }
	if (m_22 != a_m4.m_22) { return false; }
	if (m_32 != a_m4.m_32) { return false; }
	if (m_42 != a_m4.m_42) { return false; }
	
	if (m_13 != a_m4.m_13) { return false; }
	if (m_23 != a_m4.m_23) { return false; }
	if (m_33 != a_m4.m_33) { return false; }
	if (m_43 != a_m4.m_43) { return false; }
	
	if (m_14 != a_m4.m_14) { return false; }
	if (m_24 != a_m4.m_24) { return false; }
	if (m_34 != a_m4.m_34) { return false; }
	if (m_44 != a_m4.m_44) { return false; }
	return true;
}
bool Matrix4::operator!=(const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11) { return true; }
	if (m_21 != a_m4.m_21) { return true; }
	if (m_31 != a_m4.m_31) { return true; }
	if (m_41 != a_m4.m_41) { return true; }
	if (m_12 != a_m4.m_12) { return true; }
	if (m_22 != a_m4.m_22) { return true; }
	if (m_32 != a_m4.m_32) { return true; }
	if (m_42 != a_m4.m_42) { return true; }
	if (m_13 != a_m4.m_13) { return true; }
	if (m_23 != a_m4.m_23) { return true; }
	if (m_33 != a_m4.m_33) { return true; }
	if (m_43 != a_m4.m_43) { return true; }
	if (m_14 != a_m4.m_14) { return true; }
	if (m_24 != a_m4.m_24) { return true; }
	if (m_34 != a_m4.m_34) { return true; }
	if (m_44 != a_m4.m_44) { return true; }
	return false;
}
//\----------------------------------------------------------------------------------
//\ ADDITION - Operator Overload
//\----------------------------------------------------------------------------------
Matrix4 Matrix4::operator+(const Matrix4& a_m4) const
{
	return Matrix4(	m_11 + a_m4.m_11, m_21 + a_m4.m_21, m_31 + a_m4.m_31, m_41 + a_m4.m_41,
                    m_12 + a_m4.m_12, m_22 + a_m4.m_22, m_32 + a_m4.m_32, m_42 + a_m4.m_42,
                    m_13 + a_m4.m_13, m_23 + a_m4.m_23, m_33 + a_m4.m_33, m_43 + a_m4.m_43,
                    m_14 + a_m4.m_14, m_24 + a_m4.m_24, m_34 + a_m4.m_34, m_44 + a_m4.m_44);
}
const Matrix4& Matrix4::operator+=(const Matrix4& a_m4)
{
					m_11 += a_m4.m_11; m_12 += a_m4.m_12; m_13 += a_m4.m_13; m_14 += a_m4.m_14;
					m_21 += a_m4.m_21; m_22 += a_m4.m_22; m_23 += a_m4.m_23; m_24 += a_m4.m_24;
					m_31 += a_m4.m_31; m_32 += a_m4.m_32; m_33 += a_m4.m_33; m_34 += a_m4.m_34;
					m_41 += a_m4.m_41; m_42 += a_m4.m_42; m_43 += a_m4.m_43; m_44 += a_m4.m_44;
					return *this;
}
//\----------------------------------------------------------------------------------
//\ SUBTRACTION - Operator Overload 
//\----------------------------------------------------------------------------------
Matrix4 Matrix4::operator-(const Matrix4& a_m4) const
{
	return Matrix4(	m_11 - a_m4.m_11, m_21 - a_m4.m_21, m_31 - a_m4.m_31, m_41 - a_m4.m_41,
                    m_12 - a_m4.m_12, m_22 - a_m4.m_22, m_32 - a_m4.m_32, m_42 - a_m4.m_42,
                    m_13 - a_m4.m_13, m_23 - a_m4.m_23, m_33 - a_m4.m_33, m_43 - a_m4.m_43,
                    m_14 - a_m4.m_14, m_24 - a_m4.m_24, m_34 - a_m4.m_34, m_44 - a_m4.m_44);
}
const Matrix4& Matrix4::operator-=(const Matrix4& a_m4)
{
					m_11 -= a_m4.m_11; m_12 -= a_m4.m_12; m_13 -= a_m4.m_13; m_14 -= a_m4.m_14;
					m_21 -= a_m4.m_21; m_22 -= a_m4.m_22; m_23 -= a_m4.m_23; m_24 -= a_m4.m_24;
					m_31 -= a_m4.m_31; m_32 -= a_m4.m_32; m_33 -= a_m4.m_33; m_34 -= a_m4.m_34;
					m_41 -= a_m4.m_41; m_42 -= a_m4.m_42; m_43 -= a_m4.m_43; m_44 -= a_m4.m_44;
					return *this;
}
//\----------------------------------------------------------------------------------
//\ MULTIPLICATION - Operator Overload
//\----------------------------------------------------------------------------------
Matrix4 Matrix4::operator*(const float a_scalar) const
{
	return Matrix4(	m_11 * a_scalar, m_21 * a_scalar, m_31 * a_scalar, m_41 * a_scalar,
					m_12 * a_scalar, m_22 * a_scalar, m_32 * a_scalar, m_42 * a_scalar,
					m_13 * a_scalar, m_23 * a_scalar, m_33 * a_scalar, m_43 * a_scalar,
					m_14 * a_scalar, m_24 * a_scalar, m_34 * a_scalar, m_44 * a_scalar);
}
const Matrix4& Matrix4::operator*=(const float a_scalar)
{
					m_11 *= a_scalar, m_21 *= a_scalar, m_31 *= a_scalar, m_41 *= a_scalar,
					m_12 *= a_scalar, m_22 *= a_scalar, m_32 *= a_scalar, m_42 *= a_scalar,
					m_13 *= a_scalar, m_23 *= a_scalar, m_33 *= a_scalar, m_43 *= a_scalar,
					m_14 *= a_scalar, m_24 *= a_scalar, m_34 *= a_scalar, m_44 *= a_scalar;
					return *this;
}
//\----------------------------------------------------------------------------------
//\ INSERTION - Operator Overload
//\----------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Matrix4& a_m4)
{
	os.setf(std::ios::fixed, std::ios::floatfield); // Set fixed precision of decimal places
	os.precision(3);
	
	os << a_m4.m_11 << "\t" << a_m4.m_12 << "\t" << a_m4.m_13 << "\t" << a_m4.m_14 << std::endl;
	os << a_m4.m_21 << "\t" << a_m4.m_22 << "\t" << a_m4.m_23 << "\t" << a_m4.m_24 << std::endl;
	os << a_m4.m_31 << "\t" << a_m4.m_32 << "\t" << a_m4.m_33 << "\t" << a_m4.m_34 << std::endl;
	os << a_m4.m_41 << "\t" << a_m4.m_42 << "\t" << a_m4.m_43 << "\t" << a_m4.m_44 << std::endl;

	return os;
}
//\----------------------------------------------------------------------------------
//\ Matrix multiplication you simply calculate the dot product 
//\		of each row of the LHS matrix by each column of the RHS matrix.
//\----------------------------------------------------------------------------------
//\ Operator Overloads for Multiplication by Vector4 Value
//\----------------------------------------------------------------------------------
Vector4 Matrix4::operator*(const Vector4& a_v4) const
{
	return Vector4(
		m_11 * a_v4.x + m_12 * a_v4.y + m_13 * a_v4.z + m_14 * a_v4.w,
		m_21 * a_v4.x + m_22 * a_v4.y + m_23 * a_v4.z + m_24 * a_v4.w,
		m_31 * a_v4.x + m_32 * a_v4.y + m_33 * a_v4.z + m_34 * a_v4.w,
		m_41 * a_v4.x + m_42 * a_v4.y + m_43 * a_v4.z + m_44 * a_v4.w);
}
Matrix4 Matrix4::operator*(const Matrix4& a_m4) const
{
	return Matrix4(	m_11 * a_m4.m_11 + m_12 * a_m4.m_21 + m_13 * a_m4.m_31 + m_14 * a_m4.m_41, // Row 1 * Col 1
					m_21 * a_m4.m_11 + m_22 * a_m4.m_21 + m_23 * a_m4.m_31 + m_24 * a_m4.m_41, // Row 2 * Col 1
					m_31 * a_m4.m_11 + m_32 * a_m4.m_21 + m_33 * a_m4.m_31 + m_34 * a_m4.m_41, // Row 3 * Col 1
					m_41 * a_m4.m_11 + m_42 * a_m4.m_21 + m_43 * a_m4.m_31 + m_44 * a_m4.m_41, // Row 4 * Col 1													 
					
					m_11 * a_m4.m_12 + m_12 * a_m4.m_22 + m_13 * a_m4.m_32 + m_14 * a_m4.m_42, // Row 1 * Col 2
					m_21 * a_m4.m_12 + m_22 * a_m4.m_22 + m_23 * a_m4.m_32 + m_24 * a_m4.m_42, // Row 2 * Col 2
					m_31 * a_m4.m_12 + m_32 * a_m4.m_22 + m_33 * a_m4.m_32 + m_34 * a_m4.m_42, // Row 3 * Col 2
					m_41 * a_m4.m_12 + m_42 * a_m4.m_22 + m_43 * a_m4.m_32 + m_44 * a_m4.m_42, // Row 4 * Col 2
										
					m_11 * a_m4.m_13 + m_12 * a_m4.m_23 + m_13 * a_m4.m_33 + m_14 * a_m4.m_43, // Row 1 * Col 3
					m_21 * a_m4.m_13 + m_22 * a_m4.m_23 + m_23 * a_m4.m_33 + m_24 * a_m4.m_43, // Row 2 * col 3
					m_31 * a_m4.m_13 + m_32 * a_m4.m_23 + m_33 * a_m4.m_33 + m_34 * a_m4.m_43, // Row 3 * col 3
					m_41 * a_m4.m_13 + m_42 * a_m4.m_23 + m_43 * a_m4.m_33 + m_44 * a_m4.m_43, // Row 4 * col 3

					m_11 * a_m4.m_14 + m_12 * a_m4.m_24 + m_13 * a_m4.m_34 + m_14 * a_m4.m_44, // Row 1 * Col 4
					m_21 * a_m4.m_14 + m_22 * a_m4.m_24 + m_23 * a_m4.m_34 + m_24 * a_m4.m_44, // Row 2 * Col 4
					m_31 * a_m4.m_14 + m_32 * a_m4.m_24 + m_33 * a_m4.m_34 + m_34 * a_m4.m_44, // Row 3 * Col 4
					m_41 * a_m4.m_14 + m_42 * a_m4.m_24 + m_43 * a_m4.m_34 + m_44 * a_m4.m_44); // Row 4 * Col 4
}
const Matrix4& Matrix4::operator*=(const Matrix4& a_m4)
{
	*this = (*this) * a_m4;
	return *this;
}
#pragma endregion
#pragma region Algebraic_Functionality
//\====================================================================================================
// -- Algebraic Matrix 4 Functionality
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Transpose Matrix - Transform from Row To Column 
//\----------------------------------------------------------------------------------
void Matrix4::Transpose()
{
	float k;
	k = m_12; m_12 = m_21; m_21 = k;
	k = m_13; m_13 = m_31; m_31 = k;
	k = m_23; m_23 = m_32; m_32 = k;
	k = m_14; m_14 = m_41; m_41 = k;
	k = m_24; m_24 = m_42; m_42 = k;
	k = m_34; m_34 = m_43; m_43 = k;
}
Matrix4 Matrix4::GetTranspose() const
{
	return Matrix4( m_11, m_12, m_13, m_14,
                    m_21, m_22, m_23, m_24,
                    m_31, m_32, m_33, m_34,
                    m_41, m_42, m_43, m_44);
}
//\----------------------------------------------------------------------------------
//\ Scale Functionality 
//\----------------------------------------------------------------------------------
void Matrix4::Scale(const Vector4& a_v4)
{
	m_11 = a_v4.x;		m_12 = 0.0f;	m_13 = 0.0f;	m_14 = 0.0f;
	m_21 = 0.0f;		m_22 = a_v4.y;	m_23 = 0.0f;	m_24 = 0.0f;
	m_31 = 0.0f;		m_32 = 0.0f;	m_33 = a_v4.z;	m_34 = 0.0f;
	m_41 = 0.0f;		m_42 = 0.0f;	m_43 = 0.0f;	m_44 = 1.f;
}
void Matrix4::Scale(const float a_fScalar)
{
	Scale(Vector4(a_fScalar, a_fScalar, a_fScalar, a_fScalar));
}
//void Matrix4::Shear(float xy, float xz, float yx, float yz, float zx, float zy)
//{
//	m_11 = 1.f;		m_12 = xy;		m_13 = xz;		m_14 = 0.f;
//	m_21 = yx;		m_22 = 1.f;		m_23 = yz;		m_24 = 0.f;
//	m_31 = zx;		m_32 = zy;		m_13 = 1.f;		m_34 = 0.f;
//	m_41 = 0.f;		m_42 = 0.f;		m_43 = 0.f;		m_44 = 1.f;
//}
//Matrix4 Matrix4::GetShear() const
//{
//	return Matr
//}
//\----------------------------------------------------------------------------------
//\ General Matrix Functions 
//\----------------------------------------------------------------------------------
void Matrix4::Identity()
{
	m_11 = 1.0f;	m_12 = 0.0f;	m_13 = 0.0f;	m_14 = 0.0f;
	m_21 = 0.0f;	m_22 = 1.0f;	m_23 = 0.0f;	m_24 = 0.0f;
	m_31 = 0.0f;	m_32 = 0.0f;	m_33 = 1.0f;	m_34 = 0.0f;
	m_41 = 0.0f;	m_42 = 0.0f;	m_43 = 0.0f;	m_44 = 1.0f;
}

//\====================================================================================================
//\ ROTATION
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ ROTATION AROUND X AXIS --- PITCH 
//\----------------------------------------------------------------------------------
void Matrix4::RotateX(float a_angle)
{
	const float co = std::cos(a_angle); // When we pass in a_angle, it needs to be in radians not degrees
	const float si = std::sin(a_angle);

	// We rotate around the X axis so X does not change
	m_11 = 1.0f;	m_12 = 0.0f;	m_13 = 0.0f;	m_14 = 0.0f; 
	m_21 = 0.0f;	m_22 = co;		m_23 = si;		m_24 = 0.0f;
	m_31 = 0.0f;	m_32 = -si;		m_33 = co;		m_34 = 0.0f;
	m_41 = 0.0f;	m_42 = 0.0f;	m_43 = 0.0f;	m_44 = 1.0f;
}
void RotateX(Matrix4& a_m4, float a_angle)
{
	a_m4.RotateX(a_angle);
}
//\----------------------------------------------------------------------------------
//\ ROTATION AROUND Y AXIS --- YAW 
//\----------------------------------------------------------------------------------
void Matrix4::RotateY(float a_angle)
{
	const float co = std::cos(a_angle); // When we pass in a_angle, it needs to be in radians not degrees
	const float si = std::sin(a_angle);

	// We rotate around the X axis so X does not change
	m_11 = co;		m_12 = 0.0f;	m_13 = -si;		m_14 = 0.0f; 
	m_21 = 0.0f;	m_22 = 1.0f;	m_23 = 0.0f;	m_24 = 0.0f;
	m_31 = si;		m_32 = 0.0f;	m_33 = co;		m_34 = 0.0f;
	m_41 = 0.0f;	m_42 = 0.0f;	m_43 = 0.0f;	m_44 = 1.0f;
}
void RotateY(Matrix4& a_m4, float a_angle)
{
	a_m4.RotateY(a_angle);
}
//\----------------------------------------------------------------------------------
//\ ROTATION AROUND Z AXIS --- ROLL 
//\----------------------------------------------------------------------------------
void Matrix4::RotateZ(float a_angle)
{
	const float co = std::cos(a_angle); // When we pass in a_angle, it needs to be in radians not degrees
	const float si = std::sin(a_angle);

	// We rotate around the X axis so X does not change							X Roll x Y Roll 
	m_11 = co;		m_12 = si;		m_13 = 0.0f;	m_14 = 0.0f;	// = Qx
	m_21 = -si;		m_22 = co;		m_23 = 0.0f;	m_24 = 0.0f;	// = Qy
	m_31 = 0.0f;	m_32 = 0.0f;	m_33 = 1.0f;	m_34 = 0.0f;	// = Qz
	m_41 = 0.0f;	m_42 = 0.0f;	m_43 = 0.0f;	m_44 = 1.0f;	// = 1
}
void RotateZ(Matrix4& a_m4, float a_angle)
{
	a_m4.RotateZ(a_angle);
}

//\====================================================================================================
// -- RAY TRACING SPECIFIC - Matrix 4 Functionality
//\====================================================================================================

float Matrix4::Determinant() const
{
	float fA = m_11 * (	m_22 * (m_33 * m_44 - m_34 * m_43) +
						m_23 * (m_34 * m_42 - m_32 * m_44) +
						m_24 * (m_32 * m_43 - m_33 * m_42)	);
	
	float fB = m_12 * (	m_21 * (m_33 * m_44 - m_34 * m_43) +
						m_23 * (m_34 * m_41 - m_31 * m_44) +
						m_24 * (m_31 * m_43 - m_33 * m_41)	);

	float fC = m_13 * (	m_21 * (m_32 * m_44 - m_34 * m_42) +
                        m_22 * (m_34 * m_41 - m_31 * m_44) +
                        m_24 * (m_31 * m_42 - m_32 * m_41)	);

	float fD = m_14 * (	m_21 * (m_32 * m_43 - m_33 * m_42) +
                        m_22 * (m_33 * m_41 - m_31 * m_43) +
                        m_23 * (m_31 * m_42 - m_32 * m_41)	);
	
	return fA - fB + fC - fD;
}
Matrix4 Matrix4::Inverse() const // Calculating the inverse of a 4x4 matrix to create an Identity Matrix 
{
	const float fDet = Determinant();
	if (fDet != 0.0f)
	{
		const float fInvDet = 1.f/fDet;

		Matrix4 mat;
		mat.m_11 = (m_22 * (m_33 * m_44 - m_34 * m_43) +
					m_23 * (m_34 * m_42 - m_32 * m_44) +
					m_24 * (m_32 * m_43 - m_33 * m_42)) * fInvDet;
		
		mat.m_21 = (m_21 * (m_33 * m_44 - m_34 * m_43) +
                    m_23 * (m_34 * m_41 - m_31 * m_44) +
                    m_24 * (m_31 * m_43 - m_33 * m_42)) * -fInvDet;

		mat.m_31 = (m_21 * (m_32 * m_44 - m_34 * m_42) +
                    m_22 * (m_34 * m_41 - m_31 * m_44) +
                    m_24 * (m_31 * m_42 - m_32 * m_41)) * fInvDet;

		mat.m_41 = (m_21 * (m_32 * m_43 - m_33 * m_42) +
                    m_22 * (m_33 * m_41 - m_31 * m_43) +
                    m_23 * (m_31 * m_42 - m_32 * m_41)) * -fInvDet;

		
		mat.m_12 = (m_12 * (m_33 * m_44 - m_34 * m_43) +
                    m_13 * (m_34 * m_42 - m_32 * m_44) +
                    m_14 * (m_32 * m_43 - m_33 * m_42)) * -fInvDet;

		mat.m_22 = (m_11 * (m_33 * m_44 - m_34 * m_43) +
                    m_13 * (m_34 * m_41 - m_31 * m_44) +
                    m_14 * (m_31 * m_43 - m_33 * m_41)) * fInvDet;

		mat.m_32 = (m_11 * (m_32 * m_44 - m_34 * m_42) +
                    m_12 * (m_34 * m_41 - m_31 * m_44) +
                    m_14 * (m_31 * m_42 - m_32 * m_41)) * -fInvDet;

		mat.m_42 = (m_11 * (m_32 * m_43 - m_33 * m_42) +
                    m_12 * (m_33 * m_41 - m_32 * m_43) +
                    m_13 * (m_31 * m_42 - m_32 * m_41)) * fInvDet;

		
		mat.m_13 = (m_12 * (m_23 * m_44 - m_24 * m_43) +
                    m_13 * (m_24 * m_42 - m_22 * m_44) +
                    m_14 * (m_22 * m_43 - m_23 * m_42)) * fInvDet;

		mat.m_23 = (m_11 * (m_23 * m_44 - m_24 * m_43) +
                    m_13 * (m_24 * m_41 - m_21 * m_44) +
                    m_14 * (m_21 * m_43 - m_23 * m_41)) * -fInvDet;

		mat.m_33 = (m_11 * (m_22 * m_44 - m_24 * m_42) +
                    m_12 * (m_24 * m_41 - m_21 * m_44) +
                    m_14 * (m_21 * m_42 - m_22 * m_41)) * fInvDet;

		mat.m_43 = (m_11 * (m_22 * m_43 - m_23 * m_42) +
                    m_12 * (m_23 * m_41 - m_21 * m_43) +
                    m_13 * (m_21 * m_42 - m_22 * m_41)) * -fInvDet;

		
		mat.m_14 = (m_12 * (m_23 * m_34 - m_24 * m_33) +
                    m_13 * (m_24 * m_32 - m_22 * m_34) +
                    m_14 * (m_22 * m_33 - m_23 * m_32)) * -fInvDet;

		mat.m_24 = (m_11 * (m_23 * m_34 - m_24 * m_33) +
                    m_13 * (m_24 * m_31 - m_21 * m_34) +
                    m_14 * (m_21 * m_33 - m_23 * m_31)) * fInvDet;

		mat.m_34 = (m_11 * (m_22 * m_34 - m_24 * m_32) +
                    m_12 * (m_24 * m_31 - m_21 * m_34) +
                    m_14 * (m_21 * m_32 - m_22 * m_31)) * -fInvDet;

		mat.m_44 = (m_11 * (m_22 * m_33 - m_23 * m_32) +
                    m_12 * (m_23 * m_31 - m_21 * m_33) +
                    m_13 * (m_21 * m_32 - m_22 * m_31)) * fInvDet;

		return mat;
	}
	else
	{
		return Matrix4::IDENTITY;
	}
	
}
#pragma endregion
#pragma region Camera_Projection_Functions
//\====================================================================================================
// -- Camera Projection Functions 
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Camera Projection Functions 
//\ Sets Projection Matrix following the right-handed (native) way:
//\
//\	|	w		0		0				0		|                                                                                                                                              	 
//\----------------------------------------------------------------------------------
bool Matrix4::Perspective(float fRadFovY,
	float fAspectRatio,
	float fZNear,
	float fZFar)
{
	float tanHalFov = tanf(fRadFovY * 0.5f);
	if (fabsf(fZFar - fZNear) < 0.01f)
	{
		return false;
	}
	const float w = 1.f / (fAspectRatio * tanHalFov);
	const float h = 1.f / tanHalFov;

	const float r = 1.0f / (fZFar - fZNear);
	//  X Axis Collumn
	m_11 = w;				m_21 = 0.0f;			m_31 = 0.0f;						m_41 = 0.0f;
	// Y Axis Collumn
	m_12 = 0.0f;			m_22 = h;				m_32 = 0.0f;						m_42 = 0.0f;
	// Z Axis Column
	m_13 = 0.0f;			m_23 = 0.0f;			m_33 = -(fZFar + fZNear) * r;		m_43 = -1.f;
	// Transpose Column
	m_14 = 0.0f;			m_24 = 0.0f;			m_34 = -(2.0 * fZFar * fZNear) * r;	m_44 = 0.0f;

	return true;
}
//\----------------------------------------------------------------------------------
//\ Sets Orthographic Projection Matrix
//\----------------------------------------------------------------------------------
// Open GL Way:
//
//	|	2/r-1			0				0			-r+1/r-1	 |
//	|	  0			  2/t-b				0			-t+b/t-b	 |
//	|	  0				0			  -2/f-n		-f+n/f-n	 |
//	|	  0				0				0				1		 |
//	
//\----------------------------------------------------------------------------------
bool Matrix4::Orthographic(float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar)
{
	float		deltaX = fRight - fLeft;
	float		deltaY = fTop	- fBottom;
	float		deltaZ = fFar	- fNear;

	//X Axis Column
	m_11 = 2.0f	/ deltaX;	m_21 = 0.0f;	m_31 = 0.0f;	m_41 = 0.0f;
	m_12 = 0.0f;	m_22 = 2.0f / deltaY;	m_32 = 0.0f;	m_42 = 0.0f;
	m_13 = 0.0f;	m_23 = 0.0f;	m_33 = -2.0f / deltaZ;	m_43 = 0.0f;
	// Transpose Column
	m_14 = -((fRight + fLeft) / deltaX);
	m_24 = -((fTop + fBottom) / deltaY);
	m_34 = -((fFar + fNear) / deltaZ);
	m_44 = 1.0f;

	return true;
}
//\----------------------------------------------------------------------------------
//\ Camera Projection Functions
//\ Sets View Matrix following the native right-handed way:
//\ 
//\	|	rx	ux	lx	-(r.e)	|		--> r = right vector
//\ |	ry	uy	ly	-(u.e)	|		--> u = Up vector
//\	|	rz	uz	lz	(l.e)	|		--> l = Look vector
//\ |	0	0	0	  1		|		--> e = Eye Position		
//\----------------------------------------------------------------------------------

Matrix4 Matrix4::LookAt(const Vector3& a_v3EyePos, const Vector3& a_v3Target, const Vector3& a_v3Up)
{
	Vector3 vRight;
	Vector3 vForward;
	Vector3 vUp;

	vForward = a_v3Target - a_v3EyePos;
	vForward.Normalize();

	vRight = Cross(vForward, a_v3Up);
	vRight.Normalize();
	vUp = Cross(vRight, vForward);
	vUp.Normalize();
	Matrix4 mat = Matrix4::IDENTITY;
	// X Axis Column
	mat.m_11 = vRight.x; mat.m_21 = vRight.y; mat.m_31 = vRight.z; mat.m_41 = 0.0f;
	// Y Axis column
	mat.m_12 = vUp.x; mat.m_22 = vUp.y; mat.m_32 = vUp.z; mat.m_42 = 0.0f;
	// Z Axis Column
	mat.m_13 = -vForward.x; mat.m_23 = -vForward.y; mat.m_33 = -vForward.z; mat.m_43 = 0.0f;
	mat.Transpose();
	mat.m_14 = -Dot(vRight, a_v3EyePos);
	mat.m_24 = -Dot(vUp, a_v3EyePos);
	mat.m_34 = Dot(vForward, a_v3EyePos);
	mat.m_44 = 1.0f;

	return mat;
}
#pragma endregion
#pragma region Lighting_Specific_Functions
//\----------------------------------------------------------------------------------
//\ Orthonormalization - Gram-Schmidt 
// -- This function ensures that we can keep our transform matrix orthogonal (all three basis axis perpendicular to each other)
//\----------------------------------------------------------------------------------
void Matrix4::Orthonormalise()
{
	Vector3 XBasis(m_11, m_21, m_31);							// Get current Right
	Vector3 YBasis(m_12, m_22, m_32);							// Get Current Left
	Vector3 ZBasis(m_13, m_23, m_33);							// Get Current Forward

	// Asumtion is that the forward vector is the primary axis, orthonormalize around this axis being true
	YBasis = YBasis - (ZBasis + Dot(ZBasis, YBasis));			//Work out what Up should be based off forward
	YBasis.Normalize();											// Normalise UP Vector
	YBasis = Cross(YBasis, ZBasis);								// Get Right Vector for Up and Forward Vectors
	XBasis.Normalize();											// Should be normalized already but safely first

	// Set the orthogonal vector axis back into the matrix columns
	m_11 = XBasis.x; m_21 = XBasis.y; m_31 = XBasis.z;
	m_12 = YBasis.x; m_22 = YBasis.y; m_32 = YBasis.z;
	m_13 = ZBasis.x; m_23 = ZBasis.y; m_33 = ZBasis.z;
}
#pragma endregion 
