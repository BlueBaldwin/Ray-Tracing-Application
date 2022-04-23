///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				MathLib.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MATHLIB_H
#define MATHLIB_H


namespace MathLib
{
	const float PI = 3.14159265359f;
	const float DEG2RAD = PI / 180.f;
	const float RAD2DEG = 180.f * PI;
}

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Ray.h"
#include "Random.h"

#endif