///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Matrix3.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				Class that implements a 3 by 3 homogenous matrix in Column major Order 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX3_H
#define MATRIX3_H

//\------------------------
//\ INCLUDES
//\------------------------
#include <iostream>

#include "Vector2.h"
#include "Vector3.h"
//\------------------------

class Matrix3
{
private:
	//\----------------------------------------------------------------------------------
	//\ Member variables held in unnamed union for accessibility 
	//\		Items in a union share the same memory 
	//\		E.g. m[0][0] == m_11 == m_xAxis.x 
	//\		m[2][2] == m_m_33 == m_zAxis.z 
	//\----------------------------------------------------------------------------------
	union
	{
		float m[3][3];
		struct
		{
			float m_11, m_21, m_31;		// Column 1 -> x axis
			float m_12, m_22, m_32;		// Column 2 -> y axis
			float m_13, m_23, m_33;		// Column 3 -> z axis
		};
		struct
		{
			Vector3 m_xAxis;
			Vector3 m_yAxis;
			Vector3 m_zAxis;
		};
	};
public:
	//\----------------------------------------------------------------------------------
	//\ Constants 
	//\----------------------------------------------------------------------------------
	static const Matrix3 IDENTITY;
	//\----------------------------------------------------------------------------------
	//\ Constructors 
	//\----------------------------------------------------------------------------------
	Matrix3(); //default constructor
	Matrix3(const float* a_mat); // float pointer to an array of floats
	Matrix3(float a_m11, float a_m21, float a_m31, // constructors for taking all nine float arguments
			float a_m12, float a_m22, float a_m32,
			float a_m13, float a_m23, float a_m33);
	Matrix3(const Vector3& a_xAxis, const Vector3& a_yAxis, const Vector3& a_zAxis); // constructor for three axis vectors
	Matrix3(const Matrix3& a_m3); // copy constructor to allow us to easily duplicate a matrix.
	//\----------------------------------------------------------------------------------
	//\ Destructor 
	//\----------------------------------------------------------------------------------
	~Matrix3();
	//\----------------------------------------------------------------------------------
	//\ Component Access Operators 
	//\----------------------------------------------------------------------------------
	float&				operator()			(int a_iColumn, int a_iRow);
	float				operator()			(int a_iColumn, int a_iRow) const;
	//\----------------------------------------------------------------------------------
	//\ Column and Row Access 
	//\----------------------------------------------------------------------------------
	void				SetColumn			(int a_iCol, const Vector3& a_vCol);
	Vector3				GetColumn			(int a_iCol) const;
	//\----------------------------------------------------------------------------------
//\====================================================================================================
// -- OPERATOR OVERLOADS
//\====================================================================================================
	//\----------------------------------------------------------------------------------
	//\ Eqivalance Operators 
	//\----------------------------------------------------------------------------------
	bool				operator ==			(const Matrix3& a_m3) const;
	bool				operator !=			(const Matrix3& a_m3) const;
	//\----------------------------------------------------------------------------------
	//\ Overload operators for Addition 
	//\----------------------------------------------------------------------------------
	Matrix3				operator +			(const Matrix3& a_m3) const;
	const Matrix3&		operator +=			(const Matrix3& a_m3);
	//\----------------------------------------------------------------------------------
	//\  Overload operators for Subtraction 
	//\----------------------------------------------------------------------------------
	Matrix3				operator -			(const Matrix3& a_m3) const;
	const Matrix3&		operator -=			(const Matrix3& a_m3);
	//\----------------------------------------------------------------------------------
	//\ Overload operators for Multiplication 
	//\----------------------------------------------------------------------------------
	Matrix3				operator *			(const float a_scalar) const;
	const Matrix3&		operator *=			(const float a_scalar);

	Vector3				operator *			(const Vector3& a_v3) const;

	Matrix3				operator *			(const Matrix3& a_m3) const;
	const Matrix3&		operator *=			(const Matrix3& a_m3);
	//\----------------------------------------------------------------------------------
	//\ Overload operators for Output Stream 
	//\----------------------------------------------------------------------------------
	friend std::ostream& operator << (std::ostream& os, const Matrix3& a_m3);
	//\----------------------------------------------------------------------------------
	
	//\----------------------------------------------------------------------------------
	//\ Additional Matrix Functionality 
	//\		Being able to transpose a matrix from column to row order, 
	//\ 	scale a matrix and a function to set a matrix back to Identity.
	//\----------------------------------------------------------------------------------
	//\ Transpose 
	//\----------------------------------------------------------------------------------
	void				Transpose();
	Matrix3				GetTranspose() const;
	//\----------------------------------------------------------------------------------
	//\ Scale 
	//\----------------------------------------------------------------------------------
	void				Scale(const float a_scalar);
	void				Scale(const Vector3& a_v3);
	//\----------------------------------------------------------------------------------
	//\ Rotation Functions  
	//\----------------------------------------------------------------------------------
	void				RotateX				(float a_angle);
	void				RotateY				(float a_angle);
	void				RotateZ				(float a_angle);
	//\ Friend Functions for Rotation 
	friend void			RotateX				(Matrix3& a_m3, float a_angle);
	friend void			RotateY				(Matrix3& a_m3, float a_angle);
	friend void			RotateZ				(Matrix3& a_m3, float a_angle);
	//\----------------------------------------------------------------------------------
	//\ Identity 
	//\----------------------------------------------------------------------------------
	void				Identity();
	//\----------------------------------------------------------------------------------
	//\ Determinant 
	//\----------------------------------------------------------------------------------
	float				Determinant()const;
	//\----------------------------------------------------------------------------------
	//\ Inverse 
	//\----------------------------------------------------------------------------------
	bool				Inverse();
	Matrix3				GetInverse()const;
	//\----------------------------------------------------------------------------------
};

#endif