///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Scene.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				The scene class acts as an object holder for all primative objects in the world space.
//						After the rays have been fired into the scene this class will handle all ray intersection
//						testing and return the nearest passing intersection details.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include "Scene.h "
#include "Primitive.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
//\------------------------

Scene::Scene() : m_pCamera(nullptr)
{
	m_objects.clear();
	m_lights.clear();
}

Scene::~Scene()
{
	m_pCamera = nullptr;
	m_objects.clear();
	m_lights.clear();
}

//\----------------------------------------------------------------------------------
//\ Adding and Removing objects
//\----------------------------------------------------------------------------------
// Adding objects to the vector
void Scene::AddObject(const Primitive* a_object)
{
	m_objects.push_back(a_object);
}

// Removing objects by looping (iter) over the objects in the scene to test if it matches the objects we are looking for
// Erasing it and carrying on looping - Just in case the object was added multiple times
void Scene::RemoveObject(const Primitive* a_object)
{
	for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		if (*iter == a_object)			// we have located the object
		{
			iter = m_objects.erase(iter);	// Delete the object from the vector
		}
	}
}

void Scene::AddLight(const Light* a_light)
{
	m_lights.push_back(a_light);
}

void Scene::RemoveLight(const Light* a_light)
{
	for (auto iter = m_lights.begin(); iter != m_lights.end(); ++iter)
	{
		if (*iter == a_light)				// We have located the light
		{
			iter = m_lights.erase(iter);		// Remove the light from the vector
		}
	}
}

//\----------------------------------------------------------------------------------
//\ Getters and setters
//\----------------------------------------------------------------------------------
Ray Scene::GetScreenRay(const Vector2& a_screenSpacePos) const 
{
	// Create a Ray with origin at the camera and direction into the near plane offset
	return m_pCamera->CastRay(a_screenSpacePos);
}

Vector3 Scene::CastRay(const Ray& a_ray, int a_bounces, float currentIr) const
{
	if (a_bounces <= 0)							// Number of bounces remaining for ray (prevents calling function recursively forever)
	{
		return ColourRGB(0.f, 0.f, 0.f);		//Number of bounces exceeded return colour of black - no reflection due to attenuation
	}

	IntersectResponse ir;


	if (IntersectTest(a_ray, ir))				//If true an intersection has occured
	{
		// Calculate lighting 
		ir.currentRefInd = currentIr;
		Vector3 rayColour = Vector3(0.f, 0.f, 0.f);
		// For all the lights in the scene sum the effects the lights have on the object
		for (auto lightIter = m_lights.begin(); lightIter != m_lights.end(); ++lightIter)
		{
			// Test to see if in shadow -- cast ray from intersection toward light
			Ray shadowRay = Ray(ir.HitPos, -(*lightIter)->GetDirectionToLight(ir.HitPos), 0.001f);
			IntersectResponse sr;
			
			float shadowValue = (!IntersectTest(shadowRay, sr));
			if (shadowValue < 1.f)
			{
				shadowValue += sr.material->GetTransparency();
			}	// Call HitTest on the shadow ray to see if we have an occluder

			rayColour += (*lightIter)->calculateLighting(ir, m_pCamera->GetPosition()) * shadowValue;
			// If the material that we have hit is transparent and refractive we need to calculate the refraction vector 
			// and create a new ray to project into the scene
			Ray refractRay;
			ColourRGB refractionColour = ColourRGB(0.f, 0.f, 0.f);
			if (ir.material->CalcRefraction(a_ray, ir, refractRay))
			{
				refractionColour = CastRay(refractRay, a_bounces - 1, ir.material->GetRefractiveIndex()) * ir.material->GetTransparency();
			}

			ColourRGB reflectColour = ColourRGB(0.f, 0.f, 0.f);
			Ray bounceRay;
			if (ir.material->CalcReflection(a_ray, ir, bounceRay))
			{
				// Call intersect test function to accumlate colour of pixel with bounce ray
				reflectColour = CastRay(bounceRay, a_bounces - 1, ir.material->GetRefractiveIndex()) * ir.material->GetReflective();
			}
			// If the material is reflective and transparent we need to calculate the ratio of each reflective and refractive colours
			// Use schlicks approximation to calculate fresnel term for object
			if (ir.material->GetReflective() > 0.f && ir.material->GetTransparency() > 0.f)
			{
				float reflectance = ir.material->Schlick(a_ray, ir);
				rayColour += refractionColour * reflectance + refractionColour * (1.f - reflectance);
			}
			else
			{
				rayColour += refractionColour + refractionColour;
			}
		}
		return rayColour;
	}
	else
	{
		Vector3 rayToColour = RayToColour(a_ray);
		//Use Lerp to get a colour between white and blue based on the vertical value of the rayColour
		rayToColour = Lerp(Vector3(1.f, 1.f, 1.f), Vector3(0.4f, 0.7f, 1.f), rayToColour.y);
		return rayToColour;
	}
}
//\----------------------------------------------------------------------------------
//\ -- Intersection test -  - Looping through all the objects in the world and tracking the successful 
//							  intesections and their distance from the camera
//\----------------------------------------------------------------------------------

bool Scene::IntersectTest(const Ray& a_ray, IntersectResponse& a_intersectResponse) const
{
	//Set the current hit distance to be very far away
	float intersectDistance = a_ray.MaxDistance();
	bool intersectionOccured = false;
	IntersectResponse objectIntersection;

	// For each object in the world test to see if the ray intersects the object
	for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		const Primitive* object = (*iter);											// Get a pointer to the primitive object
		if (object->IntersectTest(a_ray, objectIntersection))						// Perform intersection test on each object
		{
			// Intesection occured
			if (objectIntersection.distance > a_ray.MinLength())
			{
				intersectionOccured = true;
				if (objectIntersection.distance < intersectDistance)				// is the intersection closer than previous intersection
				{
					intersectDistance = objectIntersection.distance;				// Store the new distance to the intesection 
					a_intersectResponse = objectIntersection;
				}
			}
		}
	}
	return intersectionOccured;
}
