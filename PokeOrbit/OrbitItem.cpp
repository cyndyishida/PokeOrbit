/**
 * \file OrbitItem.cpp
 *
 * \author Cyndy Ishida
 */


#include "stdafx.h"
#include "OrbitItem.h"


/**
 * Constructor
 * \param playingArea The playing area this orbitting item is a member of
 */
COrbitItem::COrbitItem(CPlayingArea *playingArea) : CGameItem(playingArea)
{

}


/**
 * Destructor
 */
COrbitItem::~COrbitItem()
{
}


/**
 * Updates orbitting item
 * \param elapsed Elapsed time since program start
 */
void COrbitItem::Update(double elapsed)
{
	double a = GetSpeed() * elapsed;

	double sn = sin(a);
	double cs = cos(a);

	double newX = cs * GetX() + sn * GetY();
	double newY = -sn * GetX() + cs * GetY();

	SetLocation(newX, newY);
}