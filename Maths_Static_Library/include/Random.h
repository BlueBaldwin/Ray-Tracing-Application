///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Random.h
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				Static functions and variables for random number generation, used for anti-aliasing
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RANDOM_H
#define RANDOM_H

//================================================================================================
// Class that implements a random number generator
// Using the following metrics:
//					seed = (a*seed + c) & m;
//					randomInt = seed & L;
// LINK = https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
//================================================================================================

namespace Random
{
	// Gets the current seed
	int				GetSeed();
	// Plants the seed
	void			SetSeed(const int& iSeed);
	// Sets the MAX integer
	int				RandMax();

	// Random integer number generator
	int				RandInt();
	int				RandomRange(const int& iMin, const int& iMax);
	// Random float number generator from 0.0f to 1.0f
	float			RandomFloat();
	float			RandomRange(const float& fx0, const float& fx1);
};

#endif