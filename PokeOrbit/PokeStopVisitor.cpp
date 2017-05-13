/**
 * \file PokeStopVisitor.cpp
 *
 * \author Cyndy Ishida
 */

#include "stdafx.h"
#include "PokeStopVisitor.h"
#include "PokeStop.h"


/**
 * Constructor
 * \param playArea The playing area this visitor is a member of
 */
 CPokeStopVisitor::CPokeStopVisitor(CPlayingArea * playArea) : CItemVisitor(playArea)
 {
 }


/**
 * Destructor
 */
CPokeStopVisitor::~CPokeStopVisitor()
{
}


/**
 * Visit a PokeStop
 * \param pokestop PokeStop we are visiting
 */
void CPokeStopVisitor::VisitPokeStop(CPokeStop *pokestop)
{
	mStopBool = true;
	
	if (pokestop->WasClicked() ) {
		pokestop->PokeStopLoad();
	}
}
