/**
 * \file Pikachu.cpp
 *
 * \author Cyndy Ishida
 */


#include "stdafx.h"
#include "Pikachu.h"

using namespace Gdiplus;
using namespace std;

/// Pikachu image name 
const wstring PikachuImageName = L"pikachu.png";

/// Pikachu rotation speed
const double PikachuRotationSpeed = 3;


/**
 * Constructor
 * \param playingArea Playing area this Pikachu is a member of 
 */
CPikachu::CPikachu(CPlayingArea * playingArea) : CPokemon(playingArea)
{
	SetImage(PikachuImageName);
}


/** Destructor */
CPikachu::~CPikachu()
{
}


/**
* Getter for Pikachu speed
* \returns Pikachu rotation speed
*/
double CPikachu::GetSpeed()
{
	return PikachuRotationSpeed;
}