/**
* \file SlowBro.h
*
* \author Jenn Proos
*
* Class that implements a Slow Bro
*/

#pragma once
#include "GameItem.h"
#include "Pokemon.h"


/**
* Class that describes a Slow Bro Pokemon
*/
class CSlowBro :
	public CPokemon
{
public:
	/// default contructor disabled 
	CSlowBro() = delete;

	/// default copy constructor disabled
	CSlowBro(const CSlowBro &) = delete;

	CSlowBro(CPlayingArea *playingArea);

	virtual ~CSlowBro();

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitSlowBro(this); }

	/* Get Slow Bro speed */
	double GetSpeed();
};
