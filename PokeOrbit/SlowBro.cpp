/**
 * \file SlowBro.cpp
 *
 * \author Cyndy Ishida , Jenn Proos
 */


#include "stdafx.h"
#include "SlowBro.h"


using namespace Gdiplus;
using namespace std;

/// Slow Bro image name 
const wstring SlowBroImageName = L"slowbro.png";

/// Slow Bro rotation speed
const double SlowBroRotationSpeed = 4;


/**
 * Constructor
 * \param playingArea The playing are this Slow Bro is a member of
 */
CSlowBro::CSlowBro(CPlayingArea * playingArea) : CPokemon(playingArea)
{
	SetImage(SlowBroImageName);
}


/** Destructor */
CSlowBro::~CSlowBro()
{
}


/**
* Gets the slow bro speed
* \returns
*/
double CSlowBro::GetSpeed()
{
	return SlowBroRotationSpeed;
}