///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//\	File:				Camera.cpp
//\	Author:				Scott Baldwin
//\	Last Edited:		20-05-21
//\	Brief:				Basic camera object that will allow us to see the projection matrix, manipulate the position of the camera 
//						and functionality to get the camera to look at a particular location. 
//						Providing the functionality for a scene to be transformed from it’s 3D representation to a 2D surface.
//\
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include "Camera.h"
//\------------------------

//\====================================================================================================
//\ Constrcutors / Access Functions
//\====================================================================================================
Camera::Camera() : m_aspectRatio(0.f), m_fov(0.f), m_zNear(0.f), m_zFar(0.f)
{
m_projectionMatrix = Matrix4::IDENTITY;
	m_Transform = Matrix4::IDENTITY;
}
Camera::~Camera()
{
}

void Camera::Setposition(Vector3 a_v3Pos)
{
	m_Transform.SetColumnV3(3, a_v3Pos);
}

Vector3 Camera::GetPosition()
{
	Vector4 pos = m_Transform.GetColumnV3(3);
	return Vector3(pos.x, pos.y, pos.z);
}
//\====================================================================================================
//	Perspective and Orthographic Functions - 
//\====================================================================================================
void Camera::SetPerspective(float a_fieldOfView, float a_aspectRatio, float a_near, float a_far)
{
	m_aspectRatio = a_aspectRatio;
	m_fov = a_fieldOfView * MathLib::DEG2RAD;
	m_zNear = a_near;
	m_zFar = a_far;
	m_projectionMatrix.Perspective(m_fov, a_aspectRatio, a_near, a_far);
}
void Camera::SetOrthographic(float a_left, float a_right, float a_top, float a_bottom, float a_near, float a_far)
{
	m_aspectRatio = (a_right - a_left) / (a_bottom - a_top);
	m_zNear = a_near;
	m_zFar = a_far;
	m_projectionMatrix.Orthographic(a_left, a_right, a_top, a_bottom, a_near, a_far);
}

void Camera::LookAt(const Vector3& a_v3Target, const Vector3& a_v3Up)
{
	Matrix4 viewMatrix = Matrix4::LookAt(GetPosition(), a_v3Target, a_v3Up);
	m_Transform = viewMatrix.Inverse();
}

Ray Camera::CastRay(Vector2 a_screenspaceCoord)
{
	// Get Projection View Matrix
	Matrix4 projViewMatrix = m_projectionMatrix * m_Transform.Inverse();
	//Invert to transform screen coordination into world Space
	Matrix4 invPV = projViewMatrix.Inverse();
	// Multiply screen coordinates by inverse projection matrix to get position on near plane
	Vector4 nearProjSpaceCoords = invPV * Vector4(a_screenspaceCoord.x, a_screenspaceCoord.y, -1.f, 1.f);
	// We need to handle the perspective divide to get the coordinate on the near place
	nearProjSpaceCoords = nearProjSpaceCoords * (1.f / nearProjSpaceCoords.w);
	Vector3 v3Near = Vector3(nearProjSpaceCoords.x, nearProjSpaceCoords.y, nearProjSpaceCoords.z);
	// Subtract the camera position from near plane location to get the direction of the ray.
	Vector3 v3Projected = v3Near - GetPosition();
	v3Projected.Normalize();
	// Create ray starting from camera position with projection
	Ray cameraRay(GetPosition(), v3Projected);

	return cameraRay;
}
