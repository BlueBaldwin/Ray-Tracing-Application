///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//	File:				Random.cpp
//	Author:				Scott Baldwin
//	Last Edited:		20-05-21
//	Brief:				Static functions and variables for random number generation, used for anti-aliasing
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//\------------------------
//\ INCLUDES
//\------------------------
#include "Random.h"

#include <algorithm>
//\------------------------

static int rand_seed = 0xB16B00B5;			// Default value for the seed
// Values set to glibc (used by GCC)
static const int rand_mod = 0x80000000;		// Set rand mod value 2^31
static const int rand_a = 1103515245;		// Set LCG A value
static const int rand_c = 12345;			// Set LCG C Value
static const int rand_L = 0x3FFFFFFF;		// Set LCG L (or Bitmask ) value


int Random::GetSeed()
{
	return rand_seed;
}
void Random::SetSeed(const int& a_seed)
{
	rand_seed = a_seed;
}
int Random::RandMax()
{
	return rand_L;
}
int Random::RandInt()
{
	rand_seed = (rand_seed * rand_a + rand_c) % rand_mod;	// Calculate seed value
	return rand_seed & rand_L;								// & with L to keep value in bit range
}
int Random::RandomRange(const int& min, const int& max)
{
	return RandInt() % max + min;
}
float Random::RandomFloat()
{
	return static_cast<float>(RandInt()) / static_cast<float>(RandMax());
}

float Random::RandomRange(const float& min, const float& max)
{
	return min + ((max - min) * RandomFloat());
}
