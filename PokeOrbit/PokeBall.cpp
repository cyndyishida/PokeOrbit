/**
* \file PokeBall.cpp
*
* \author Cyndy Ishida
*/


#include "stdafx.h"
#include <string>
#include "PokeBall.h"
#include "ItemVisitor.h"


using namespace Gdiplus;
using namespace std;

/// Pokeball image name 
const wstring PokeballImageName = L"pokeball.png";

/**
* Constructor
* \param playingArea Playing area this pokeball is a member of
*/
CPokeBall::CPokeBall(CPlayingArea *playingArea) : CGameItem(playingArea)
{
	SetImage(PokeballImageName);
}

/**
* Destructor
*/
CPokeBall::~CPokeBall()
{
}


/**
 * Update animation based on elapsed
 * \param elapsed Time elapsed since program start
 * \param x X location of pokeball
 * \param y Y location of pokeball
 */
void CPokeBall::Update(double elapsed, double x, double y)
{
	double xX = GetX();
	double yY = GetY();

	xX = (xX + CGameItem::GetVirtualX() * elapsed);
	yY = (yY + CGameItem::GetVirtualY() * elapsed);

	SetLocation(xX ,yY);
	
}


/**
 * Set virtual coordinates
 * \param virtualX virtual X coordinate of pokeball
 * \param virtualY virtual Y coordinate of pokeball
 */
void CPokeBall::SetCoordinates(double virtualX, double virtualY)
{

	CGameItem::SetVirtualX(virtualX);

	CGameItem::SetVirtualY(virtualY);

}


/**
 * Accepts a visitor
 * \param visitor The visitor we are accepting
 */
void CPokeBall::Accept(CItemVisitor *visitor)
{ 
	visitor->VisitPokeball(this); 
}