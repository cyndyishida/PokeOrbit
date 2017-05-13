/**
 * \file 
 .cpp
 *
 * \author Cyndy Ishida
 */


#include "stdafx.h"
#include "Character.h"



using namespace Gdiplus;
using namespace std;

/// Character image name 
const wstring CharacterImageName = L"ash.png";

/// max speed in the x direction
const static double MaxSpeedX = 0;

/// max speed in the y direction 
const static double MaxSpeedY = 0;


/**
* Constructor
* \param playingArea Playing area this character is a member of
*/
CCharacter::CCharacter(CPlayingArea *playingArea) : CGameItem(playingArea)
{
	SetImage(CharacterImageName);
}


/**
 * Destructor
 */
CCharacter::~CCharacter()
{
}

