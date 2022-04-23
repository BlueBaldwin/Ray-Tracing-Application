///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Matrix4.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				Class that implements a 4 by 4 homogenous matrix in Column major Order 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX4_H
#define MATRIX4_H

//\------------------------
//\ INCLUDES
//\------------------------
#include <future>
#include <iostream>

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
//\------------------------

class Matrix4
{
public:
	//\====================================================================================================
	//\ Member Variables held in unnamed union for accessibility 
	//\====================================================================================================
union 
{
	struct
	{
		float		m[4][4];
	};
	struct
	{
		float		f[16];
	};
	struct 
	{				// Column order
					// (Columns across - Rows Down)	 4th Column
		float		m_11, m_21, m_31, m_41; // X Axis		0
		float		m_12, m_22, m_32, m_42; // Y Axis		0
		float		m_13, m_23, m_33, m_43; // Z Axis		0
		float		m_14, m_24, m_34, m_44; // W Translate	0 or 1 for axis orientation 
	};
};
	//\----------------------------------------------------------------------------------
	//\ Constants 
	//\----------------------------------------------------------------------------------
	static const Matrix4 IDENTITY;
	//\----------------------------------------------------------------------------------
	//\ Constructors
	//\----------------------------------------------------------------------------------
	Matrix4(); // Default
	
	explicit Matrix4(const float* a_mat);
	
	Matrix4(float m11, float m21, float m31, float m41, // Constructor for all 12 float arguments
			float m12, float m22, float m32, float m42,
			float m13, float m23, float m33, float m43,
			float m14, float m24, float m34, float m44
			);
	Matrix4(const Vector4& a_xAxis, const Vector4& a_yAxis, const Vector4& a_zAxis, const Vector4& a_wAxis); // Constructor for four axis Vectors
	Matrix4(const Matrix4& a_m4); // Copy constructor to allow us to easily duplicate a matrix
	//\----------------------------------------------------------------------------------
	//\ Destructor 
	//\----------------------------------------------------------------------------------
	~Matrix4();
	//\----------------------------------------------------------------------------------
	//\ Component Access Operators 
	//\----------------------------------------------------------------------------------
	float&				operator()			(int a_iColumn, int a_iRow);
	float				operator()			(int a_iColumn, int a_iRow) const;
	//\----------------------------------------------------------------------------------
	//\ Column and Row Access 
	//\----------------------------------------------------------------------------------
	void 				SetColumnV3			(int a_iCol, const Vector3& a_vCol);
	Vector3				GetColumnV3			(int a_iCol) const;
	void				SetColumnV4			(int a_iCol, const Vector4& a_vCol);
	Vector4				GetColumnV4			(int a_iCol) const;
//\====================================================================================================
// -- OPERATOR OVERLOADS
//\====================================================================================================
	//\----------------------------------------------------------------------------------
	//\ Eqivalance Operators 
	//\----------------------------------------------------------------------------------
	bool				operator ==			(const Matrix4& a_m4) const;
	bool				operator !=			(const Matrix4& a_m4) const;
	//\----------------------------------------------------------------------------------
	//\ Overload operators for Addition 
	//\----------------------------------------------------------------------------------
	Matrix4				operator +			(const Matrix4& a_m4) const;
	const Matrix4&		operator +=			(const Matrix4& a_m4);
	//\----------------------------------------------------------------------------------
	//\  Overload operators for Subtraction 
	//\----------------------------------------------------------------------------------
	Matrix4				operator -			(const Matrix4& a_m4) const;
	const Matrix4&		operator -=			(const Matrix4& a_m4);
	//\----------------------------------------------------------------------------------
	//\ Overload operators for Multiplication 
	//\----------------------------------------------------------------------------------
	Matrix4				operator *			(const float a_scalar) const;
	const Matrix4&		operator *=			(const float a_scalar);

	Vector4				operator *			(const Vector4& a_v4) const;

	Matrix4				operator *			(const Matrix4& a_m4) const;
	const Matrix4&		operator *=			(const Matrix4& a_m4);
	//\----------------------------------------------------------------------------------
	//\ Overload operators for Output Stream 
	//\----------------------------------------------------------------------------------
	friend std::ostream& operator << (std::ostream& os, const Matrix4& a_m4);
	//\----------------------------------------------------------------------------------

//\====================================================================================================
//\ Additional Matrix Functionality 
//\		Being able to transpose a matrix from column to row order, 
//\ 	scale a matrix and a function to set a matrix back to Identity.
//\====================================================================================================
	//\----------------------------------------------------------------------------------
	//\ Transpose 
	//\----------------------------------------------------------------------------------
	void				Transpose();
	Matrix4				GetTranspose() const;
	//\----------------------------------------------------------------------------------
	//\ Scale 
	//\----------------------------------------------------------------------------------
	void				Scale				(const Vector4& a_v4);
	void				Scale				(const float a_fScalar);
	void				Shear				(float xy, float xz, float yx, float yz, float zx, float zy);
	//Matrix4				GetShear() const;
	//\----------------------------------------------------------------------------------
	//\ Rotation Functions  
	//\----------------------------------------------------------------------------------
	void				RotateX				(float a_angle);
	void				RotateY				(float a_angle);
	void				RotateZ				(float a_angle);
	//\ Friend Functions for Rotation 
	friend void			RotateX				(Matrix4& a_m4, float a_angle);
	friend void			RotateY				(Matrix4& a_m4, float a_angle);
	friend void			RotateZ				(Matrix4& a_m4, float a_angle);
	//\----------------------------------------------------------------------------------
	//\ General Matrix Functions 
	//\----------------------------------------------------------------------------------
	void				Identity();
	//\----------------------------------------------------------------------------------
	//\ Inverse 
	//\----------------------------------------------------------------------------------
	float				Determinant() const;
	Matrix4				Inverse() const;
//\====================================================================================================
//\ Camera Projection Functions 
//\====================================================================================================
	bool				Perspective(float fRadFovY, float fAspectRatio, float fZNear, float fZFar);
	bool				Orthographic(float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar);
	//\----------------------------------------------------------------------------------
	//\ Look at Functions   - Getting the camera to orientate itself to look at a particular point in the world with a given Up vector.
	//	   					  This function will get us thelocal view matrix for the camera so that all objects are relevant to it’s position.
	//\----------------------------------------------------------------------------------
	static Matrix4		LookAt(const Vector3& a_v3EyePos, const Vector3& a_v3Target, const Vector3& a_v3Up);
	//\----------------------------------------------------------------------------------
	//\ Orthonormalization - Gram-Schmidt 
	//\----------------------------------------------------------------------------------
	void				Orthonormalise();
};
#endif
































