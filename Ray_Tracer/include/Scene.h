///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Scene.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				The scene class acts as an object holder for all primative objects in the world space.
//						After the rays have been fired into the scene this class will handle all ray intersection
//						testing and return the nearest passing intersection details.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SCENE_H

//\------------------------
//\ INCLUDES
//\------------------------
#include <vector>
#include "MathLib.h"
#include "IntersectionResponse.h"
//\------------------------

class Primitive;
class Camera;
class Light;

class Scene
{
public:
	// Default constructors / destructor
	Scene();
	~Scene();

	// Functions for adding/removing objects into/from the scene - accepting a pointer to primitive object
	void AddObject(const Primitive* a_object);
	void RemoveObject(const Primitive* a_object);


	void AddLight(const Light* a_light);
	void RemoveLight(const Light* a_light);

	Ray GetScreenRay(const Vector2& a_screenSpacePos) const;
	Vector3 CastRay(const const Ray& a_ray, int a_bounces, float currentIr = 1.0f) const;
	// Intersection testing - returning true if an intersection occurs from the cameras ray and stored in the Intersection Response variable that is passed in by reference
	bool IntersectTest(const Ray& a_ray, IntersectResponse& a_intersectResponse) const;

	void SetCamera(Camera* a_pCamera) { m_pCamera = a_pCamera; }

private: 
	std::vector<const Primitive*> m_objects;
	std::vector<const Light* > m_lights;
	Camera* m_pCamera;
};
#endif