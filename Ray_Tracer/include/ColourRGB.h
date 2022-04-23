///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				ColourRGB.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				Transforming values from world space ( -1 -> 1 ) into  colour data space ( 0 -> 1)
//						Setting RGB values into workable Vector3 values. 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef COLOURRGB_H

//\------------------------
//\ INCLUDES
//\------------------------
#include <iostream>
#include "Vector3.h"
#include "Ray.h"
//\------------------------

//\----------------------------------------------------------------------------------
//\ Set up Colour RGB to be an allias for Vector 3 
//\----------------------------------------------------------------------------------
using ColourRGB = Vector3;

void WriteColourRGB(std::ostream& a_ostream, ColourRGB a_colour);
//\----------------------------------------------------------------------------------
//\ Function to transform ray from world space direction to colour value 
//\		Direction is in space -1 > 1, colour data in space 0 -> 1	
//\----------------------------------------------------------------------------------
ColourRGB RayToColour(const Ray& a_ray);
#endif // !COLOURRGB_H