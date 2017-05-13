/**
* \file Charmander.h
*
* \author Cyndy Ishida
*
* Class that implements a Charmander
*/


#pragma once
#include "GameItem.h"
#include "Pokemon.h"


/**
* Class that describes a Charmander Pokemon
*/
class CCharmander :
	public CPokemon
{
public:
	/// default contructor disabled 
	CCharmander() = delete;

	/// default copy constructor disabled
	CCharmander(const CCharmander &) = delete;

	CCharmander(CPlayingArea *playingArea);

	virtual ~CCharmander();

	/* Get Charmander speed */
	double GetSpeed();

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitCharmander(this); }
};