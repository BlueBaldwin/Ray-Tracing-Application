///////////////////////////////////////////////////////////////////////////////////////////////////////
//\====================================================================================================
//\ CAMERA CLASS
//\====================================================================================================
//\	File:				Camera.h
//\	Author:				Scott Baldwin
//\	Last Edited:		20-05-21
//\	Brief:				Basic camera object that will allow us to see the projection matrix, manipulate the position of the camera 
//						and functionality to get the camera to look at a particular location. 
//						Providing the functionality for a scene to be transformed from it’s 3D representation to a 2D surface.
//\
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMERA_H
#define CAMERA_H

//\------------------------
//\ INCLUDES
//\------------------------
#include "Vector3.h"
//\------------------------

#pragma once
#include <MathLib.h>

class Camera
{
public:
	//\====================================================================================================
	//\ Constrcutors / Access Functions
	//\====================================================================================================
	//\----------------------------------------------------------------------------------
	//\ Constructor / Destructor 
	//\----------------------------------------------------------------------------------
	Camera();
	~Camera();
	//\----------------------------------------------------------------------------------
	//\ Set/Get the position of the camera in the world 
	//\----------------------------------------------------------------------------------
	void Setposition(Vector3 a_v3Pos);
	Vector3 GetPosition();

	//\====================================================================================================
	//	Perspective and Orthographic Functions
	// 
	// 	Projection Matrices	- Further reading: http://www.songho.ca/opengl/gl_projectionmatrix.html
	//\====================================================================================================
	//\----------------------------------------------------------------------------------
	//\ Set perspective projection -- the size of an object depending on their distance  
	//\----------------------------------------------------------------------------------
	void SetPerspective(float a_fieldOfView, float a_aspectRatio, float a_near, float a_far);
	//\----------------------------------------------------------------------------------
	//\ Orthographic projection - no size change as objects are further away 
	//\----------------------------------------------------------------------------------
	void SetOrthographic(float a_left, float a_right, float a_top, float a_bottom, float a_near, float a_far);

	//\----------------------------------------------------------------------------------
	//\ Look at a point in the world with the camera's local up direction set to the second direction 
	//\----------------------------------------------------------------------------------
	void LookAt(const Vector3& a_v3Target, const Vector3& a_v3Up);
	//\----------------------------------------------------------------------------------
	//\ Cast a ray from a screen position out into the world space of the camera 
	//\----------------------------------------------------------------------------------
	Ray CastRay(Vector2 a_screenspaceCoord);
	//\----------------------------------------------------------------------------------
	//\ Get camera pos/rot matrix 
	//\----------------------------------------------------------------------------------
	Matrix4 GetTransform() { return m_Transform; }
	//\----------------------------------------------------------------------------------
	//\ Get Projection Matrix
	//\----------------------------------------------------------------------------------
	Matrix4 GetProjectionMatrix() {return m_projectionMatrix; }
private:
	Matrix4 m_projectionMatrix;
	Matrix4 m_Transform;
	float m_aspectRatio;
	float m_fov;
	float m_zNear;
	float m_zFar;
};
#endif