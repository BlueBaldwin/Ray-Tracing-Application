///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Matrix3.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				Class that implements a 3 by 3 homogenous matrix in Column major Order 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include <cassert> // Allows our program to assert if the collumn or row is outside the scope of the Matrix class
#include <cmath>

#include "Matrix3.h"
#include "Vector3.h"
#include "iostream"
//\------------------------
#pragma region Constructors
//\----------------------------------------------------------------------------------
//\ Identity Matrix3
//\----------------------------------------------------------------------------------
// A constant static variable to use to quickly set/get an identity matrix
const Matrix3 Matrix3::IDENTITY = Matrix3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.1f);
//\----------------------------------------------------------------------------------
//\ Default Constructor - by default init to identity 
//\----------------------------------------------------------------------------------
Matrix3::Matrix3() :	m_11(1.f), m_21(0.f), m_31(0.f),
						m_12(0.f), m_22(1.f), m_32(0.f),
						m_13(0.f), m_23(0.f), m_33(1.f)
{
}
//\----------------------------------------------------------------------------------
//\ Constructor using pointer to float data 
//\----------------------------------------------------------------------------------
Matrix3::Matrix3(const float* a_mat):	m_11(a_mat[0]), m_21(a_mat[1]), m_31(a_mat[2]),
										m_12(a_mat[3]), m_22(a_mat[4]), m_32(a_mat[5]),
										m_13(a_mat[6]), m_23(a_mat[7]), m_33(a_mat[8])
{
}
//\----------------------------------------------------------------------------------
//\ Constructor using all components of matrix data structure 
//\----------------------------------------------------------------------------------
Matrix3::Matrix3	(float a_m11, float a_m21, float a_m31,
					float a_m12, float a_m22, float a_m32,
					float a_m13, float a_m23, float a_m33):
					m_11(a_m11), m_21(a_m21), m_31(a_m31), 
					m_12(a_m12), m_22(a_m22), m_32(a_m32),
					m_13(a_m13), m_23(a_m23), m_33(a_m33)
{
}
//\----------------------------------------------------------------------------------
//\ Construct from Axis angle vectors 
//\----------------------------------------------------------------------------------
Matrix3::Matrix3(const Vector3& a_xAxis, const Vector3& a_yAxis, const Vector3& a_zAxis) :
	m_xAxis(a_xAxis), m_yAxis(a_yAxis), m_zAxis(a_zAxis)
{
}
//\----------------------------------------------------------------------------------
//\ Copy Constructor 
//\----------------------------------------------------------------------------------
Matrix3::Matrix3(const Matrix3& a_m3) :
	m_11(a_m3.m_11), m_21(a_m3.m_21), m_31(a_m3.m_31),
	m_12(a_m3.m_12), m_22(a_m3.m_22), m_32(a_m3.m_32),
	m_13(a_m3.m_13), m_23(a_m3.m_23), m_33(a_m3.m_33)
{
}
//\----------------------------------------------------------------------------------
//\ Destructor 
//\----------------------------------------------------------------------------------
Matrix3::~Matrix3()
{
}
#pragma endregion
#pragma region Getters_Setters
//\====================================================================================================
// -- Accessing Matrix / Getters and Setters
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ IMPLEMENTATION OF THE ACCESSOR FUNCTION 

//\ This will allow us to write code the following way:		float value = mat3(2,3); 
//\ where the value will equal the individual matrix component stored at column 2 row 3.
//\ Member Variable access operator overload 
//\----------------------------------------------------------------------------------

float& Matrix3::operator() (int a_col, int a_row) 
{
	// Make sure that column and row is within range
	assert(a_col >= 0 && a_col < 3);
	assert(a_row >= 0 && a_row < 3);
	return m[a_col - 1][a_row - 1];
}
float Matrix3::operator() (int a_iRow, int a_iCol) const
{
	// Malke sure that column and row is within range
	assert(a_iCol >= 0 && a_iCol < 3);
	assert(a_iRow >= 0 && a_iRow < 3);
	return m[a_iCol - 1][a_iRow - 1];
}
//\----------------------------------------------------------------------------------
//\ Column and Row Access 
//\----------------------------------------------------------------------------------
void Matrix3::SetColumn(int a_iCol, const Vector3& a_vCol)
{
	assert(a_iCol >= 0 && a_iCol < 3);
	m[a_iCol][0] = a_vCol.x; m[a_iCol][1] = a_vCol.y; m[a_iCol][2] = a_vCol.z;
}
Vector3 Matrix3::GetColumn(int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 3);
	return Vector3(m[a_iCol][0], m[a_iCol][1], m[a_iCol][2]);
}
#pragma endregion
#pragma region Operator_Overloads
//\====================================================================================================
// -- OPERATOR OVERLOADS
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Equivalence Operators - Matrix Testing for equality 
//\----------------------------------------------------------------------------------
bool Matrix3::operator == (const Matrix3& a_m3) const
{
	if (m_11 != a_m3.m_11) { return false; }
	if (m_21 != a_m3.m_21) { return false; }
	if (m_31 != a_m3.m_31) { return false; }
	if (m_12 != a_m3.m_12) { return false; }
	if (m_22 != a_m3.m_22) { return false; }
	if (m_32 != a_m3.m_32) { return false; }
	if (m_13 != a_m3.m_13) { return false; }
	if (m_23 != a_m3.m_23) { return false; }
	if (m_33 != a_m3.m_33) { return false; }
	return true;
}
bool Matrix3::operator != (const Matrix3& a_m3) const
{
	if (m_11 != a_m3.m_11) { return true; }
	if (m_21 != a_m3.m_21) { return true; }
	if (m_31 != a_m3.m_31) { return true; }
	if (m_12 != a_m3.m_12) { return true; }
	if (m_22 != a_m3.m_22) { return true; }
	if (m_32 != a_m3.m_32) { return true; }
	if (m_13 != a_m3.m_13) { return true; }
	if (m_23 != a_m3.m_23) { return true; }
	if (m_33 != a_m3.m_33) { return true; }
	return false;
}
//\----------------------------------------------------------------------------------
//\ Operator Overloads for Addition 
//\----------------------------------------------------------------------------------
Matrix3 Matrix3::operator+(const Matrix3& a_m3) const
{
	return Matrix3(	m_11 + a_m3.m_11, m_21 + a_m3.m_21, m_31 + a_m3.m_31,
					m_12 + a_m3.m_12, m_22 + a_m3.m_22, m_32 + a_m3.m_32,
					m_13 + a_m3.m_13, m_23 + a_m3.m_23, m_33 + a_m3.m_33);
}

const Matrix3& Matrix3::operator+=(const Matrix3& a_m3)
{
					m_11 += a_m3.m_11; m_12 += a_m3.m_12; m_13 += a_m3.m_13;
					m_21 += a_m3.m_21; m_22 += a_m3.m_22; m_23 += a_m3.m_23;
					m_31 += a_m3.m_31; m_32 += a_m3.m_32; m_33 += a_m3.m_33;
					return *this;
}
//\----------------------------------------------------------------------------------
//\ Operator Overloads for Subtraction 
//\----------------------------------------------------------------------------------
Matrix3 Matrix3::operator-(const Matrix3& a_m3) const
{
	return Matrix3(	m_11 - a_m3.m_11, m_21 - a_m3.m_21, m_31 - a_m3.m_31,
					m_12 - a_m3.m_12, m_22 - a_m3.m_22, m_32 - a_m3.m_32,
					m_13 - a_m3.m_13, m_23 - a_m3.m_23, m_33 - a_m3.m_33);
}
const Matrix3& Matrix3::operator-=(const Matrix3& a_m3)
{
	m_11 -= a_m3.m_11; m_12 -= a_m3.m_12; m_13 -= a_m3.m_13;
	m_21 -= a_m3.m_21; m_22 -= a_m3.m_22; m_23 -= a_m3.m_23;
	m_31 -= a_m3.m_31; m_32 -= a_m3.m_32; m_33 -= a_m3.m_33;
	return *this;
}
//\----------------------------------------------------------------------------------
//\ Operator Overloads for Multiplication 
//\----------------------------------------------------------------------------------
Matrix3 Matrix3::operator*(const float a_fScalar) const
{
	return Matrix3(	m_11 * a_fScalar, m_21 * a_fScalar, m_31 * a_fScalar,
					m_12 * a_fScalar, m_22 * a_fScalar, m_32 * a_fScalar,
					m_13 * a_fScalar, m_23 * a_fScalar, m_33 * a_fScalar);
}
const Matrix3& Matrix3::operator*=(float a_fScalar)
{
	m_11 *= a_fScalar; m_12 *= a_fScalar; m_13 *= a_fScalar;
	m_21 *= a_fScalar; m_22 *= a_fScalar; m_23 *= a_fScalar;
	m_31 *= a_fScalar; m_32 *= a_fScalar; m_33 *= a_fScalar;
	return *this;
}
//\----------------------------------------------------------------------------------
//\ Matrix multiplication you simply calculate the dot product 
//\		of each row of the LHS matrix by each column of the RHS matrix.
//\----------------------------------------------------------------------------------
//\ Operator Overloads for Multiplication by Vector3 Value
//\----------------------------------------------------------------------------------
Vector3 Matrix3::operator*(const Vector3& a_v3) const
{
	return Vector3(
		m_11 * a_v3.x + m_12 * a_v3.y + m_13 * a_v3.z,
		m_21 * a_v3.x + m_22 * a_v3.y + m_23 * a_v3.z,
		m_31 * a_v3.x + m_32 * a_v3.y + m_33 * a_v3.z);
}
//\----------------------------------------------------------------------------------
//\ Operator overloads for multiplication by Matrix3 
//\----------------------------------------------------------------------------------
Matrix3 Matrix3::operator*(const Matrix3& a_m3) const
{
	return Matrix3(	m_11 * a_m3.m_11 + m_12 * a_m3.m_21 + m_13 * a_m3.m_31,
					m_21 * a_m3.m_11 + m_22 * a_m3.m_21 + m_23 * a_m3.m_31,
					m_32 * a_m3.m_11 + m_32 * a_m3.m_21 + m_33 * a_m3.m_31,

					m_11 * a_m3.m_12 + m_12 * a_m3.m_22 + m_13 * a_m3.m_32,
					m_21 * a_m3.m_12 + m_22 * a_m3.m_22 + m_23 * a_m3.m_32,
					m_31 * a_m3.m_12 + m_32 * a_m3.m_22 + m_33 * a_m3.m_32,

					m_11 * a_m3.m_13 + m_12 * a_m3.m_23 + m_13 * a_m3.m_33,
					m_21 * a_m3.m_13 + m_22 * a_m3.m_23 + m_23 * a_m3.m_33,
					m_31 * a_m3.m_13 + m_32 * a_m3.m_23 + m_33 * a_m3.m_33);
}
const Matrix3& Matrix3::operator*=(const Matrix3& a_m3)
{
	*this = (*this) * a_m3;
	return *this;
}
std::ostream& operator<<(std::ostream& os, const Matrix3& a_m3)
{
	os.setf(std::ios::fixed, std::ios::floatfield); // Set fixed precision of decimal places
	os.precision(3);
	
	os << a_m3.m_11 << "\t" << a_m3.m_12 << "\t" << a_m3.m_13 << std::endl;
	os << a_m3.m_21 << "\t" << a_m3.m_22 << "\t" << a_m3.m_23 << std::endl;
	os << a_m3.m_31 << "\t" << a_m3.m_32 << "\t" << a_m3.m_33 << std::endl;

	return os;
}
#pragma endregion
#pragma region Algebraic_Functionality
//\====================================================================================================
// -- Algebraic Matrix 3 Functionality
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Transpose Matrix - Transform from Row To Column 
//\----------------------------------------------------------------------------------
void Matrix3::Transpose()
{
	float k;
	k = m_12; m_12 = m_21; m_21 = k;
	k = m_13; m_13 = m_31; m_31 = k;
	k = m_23; m_23 = m_32; m_32 = k;
}
Matrix3 Matrix3::GetTranspose() const
{
	return Matrix3( m_11, m_12, m_13,
					m_21, m_22, m_23,
					m_31, m_32, m_33);
}
//\----------------------------------------------------------------------------------
//\ Scale Functionality 
//\----------------------------------------------------------------------------------
void Matrix3::Scale(const Vector3& a_v3)
{
	m_11 = a_v3.x;		m_12 = 0.0f;	m_13 = 0.0f;
	m_21 = 0.0f;		m_22 = a_v3.y;	m_23 = 0.0f;
	m_31 = 0.0f;		m_32 = 0.0f;	m_33 = a_v3.z;
}
void Matrix3::Scale(float a_fScalar)
{
	Scale(Vector3(a_fScalar, a_fScalar, a_fScalar));
}
//\----------------------------------------------------------------------------------
//\ General Matrix Functions 
//\----------------------------------------------------------------------------------
void Matrix3::Identity()
{
	m_11 = 1.0f;	m_12 = 0.0f;	m_13 = 0.0f;
	m_21 = 0.0f;	m_22 = 1.0f;	m_23 = 0.0f;
	m_31 = 0.0f;	m_32 = 0.0f;	m_33 = 1.0f;
}

//\====================================================================================================
//\ ROTATION
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ ROTATION AROUND X AXIS --- PITCH 
//\----------------------------------------------------------------------------------
void Matrix3::RotateX (float a_angle) 
{
	const float co = std::cos(a_angle); // When we pass in a_angle, it needs to be in radians not dgrees
	const float si = std::sin(a_angle);

	// We rotate around the X axis so X does not change
	m_11 = 1.0; m_12 = 0.f; m_13 = 0.f;
	m_21 = 0.f; m_22 = co;	m_23 = si;
	m_31 = 0.f; m_32 = -si;	m_33 = co;
}
void RotateX(Matrix3& a_m3, float a_angle)
{
	a_m3.RotateX(a_angle);
}
//\----------------------------------------------------------------------------------
//\ ROTATION AROUND Y AXIS --- YAW 
//\----------------------------------------------------------------------------------
void Matrix3::RotateY(float a_angle)
{
	const float co = std::cos(a_angle); 
	const float si = std::sin(a_angle);

	// We rotate around the Y axis so Y does not change
	m_11 = co; m_12 = 0.f; m_13 = si;
	m_21 = 0.f; m_22 = 1.f;	m_23 = 0.f;
	m_31 = -si; m_32 = 0.f;	m_33 = co;
}
void RotateY(Matrix3& a_m3, float a_angle)
{
	a_m3.RotateY(a_angle);
}
//\----------------------------------------------------------------------------------
//\ ROTATION AROUND Z AXIS --- ROLL 
//\----------------------------------------------------------------------------------
void Matrix3::RotateZ(float a_angle)
{
	const float co = std::cos(a_angle); 
	const float si = std::sin(a_angle);

	// We rotate around the Z axis so Z does not change
	m_11 = co; m_12 = -si; m_13 = 0.f;
	m_21 = si; m_22 = co;	m_23 = 0.f;
	m_31 = 0.f; m_32 = 0.f;	m_33 = 1.f;
}
void RotateZ(Matrix3& a_m3, float a_angle)
{
	a_m3.RotateZ(a_angle);
}

//\====================================================================================================
//\ INVERSION - Matrix 3x3 - 
//\====================================================================================================

//\----------------------------------------------------------------------------------
//\ Determinant - Must be a non-zero value 
//\----------------------------------------------------------------------------------
Vector3 AxB {0,0,0};
float Matrix3::Determinant() const  
{
	/* 
	//LONG HAND WAY TO WORK OUT THE DETERMINANT - INCREASING STACK VARIABLE DEMANDS
	
	// Getting the row vectors
	Vector3 a = Vector3(m_11, m_12, m_13);
	Vector3 b = Vector3(m_21, m_22, m_23);
	Vector3 c = Vector3(m_31, m_32, m_33);

	// Crossing a and b rows then calculating the dot product with remaining row c to return the determinant
	
	Vector3 AxB = Cross(a,b);
	float determinant = Dot(c, AxB);
	return determinant;
	
	A much less "Stack Intensive" aproach - Cross product of row 2 & 3 in matrix
										 - Dot Product of above result with row 1

							Determinant = m_11 * (the result of that cross) + 
									      m_12 * (the result of second cross) +
									      m_13 * (the result of third cross);
	*/
	return (m_11 * (m_22 * m_33 - m_23 * m_32) +
			m_12 * (m_23 * m_31 - m_21 * m_33) +
			m_13 * (m_21 * m_32 - m_22 * m_31));
}	
//\----------------------------------------------------------------------------------
//\ Inverse (Flipping Matrix values accross the diagnol)
//\----------------------------------------------------------------------------------
bool Matrix3::Inverse()
{
	float fDet = Determinant();
	// If the determinat is zero this matrix is singular  matrix and cannot be inverted
	if ( fDet != 0.f)
	{
		Matrix3 cofactor = Matrix3( // Transpose the matrix as in the constructor
			  m_22*m_33 - m_23*m_32, -(m_12*m_33 - m_13*m_32), m_12*m_23 - m_13*m_22,
			-(m_21*m_33 - m_23*m_31), m_11*m_33 - m_13*m_31, -(m_11*m_23 - m_13*m_21),
			  m_21*m_32 - m_22*m_31, -(m_11*m_32 - m_12*m_31), m_11*m_22 - m_12*m_21);
		*this = cofactor * (1.f / fDet);
	}
	return false;
}
#pragma endregion
