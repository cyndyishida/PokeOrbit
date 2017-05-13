/**
 * \file Charmander.cpp
 *
 * \author Cyndy Ishida
 */


#include "stdafx.h"
#include "Charmander.h"


using namespace Gdiplus;
using namespace std;

/// Charamander image name 
const wstring CharmanderImageName = L"charmander.png";

/// Charmander rotation speed
const double CharmanderRotationSpeed = 1;


/**
 * Constructor
 * \param playingArea Playing area this charmander is a member of
 */
CCharmander::CCharmander(CPlayingArea * playingArea) : CPokemon(playingArea)
{
	SetImage(CharmanderImageName);
}



/**
 * Destructor
 */
CCharmander::~CCharmander()
{
}


/**
 * Get Charmander speed
 * \returns Charmander speed
 */
double CCharmander::GetSpeed()
{
	return CharmanderRotationSpeed;
}