/**
* \file Pikachu.h
*
* \author Cyndy Ishida
*
* Class that implements a Pikachu
*/


#pragma once
#include "GameItem.h"
#include "Pokemon.h"


/**
* Class that describes a Pikachu Pokemon
*/
class CPikachu :
	public CPokemon
{
public:
	/// default constructor disabled 
	CPikachu() = delete;

	/// default copy constructor disabled 
	CPikachu(const CPikachu &) = delete;

	CPikachu(CPlayingArea * playingArea);

	virtual ~CPikachu();

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitPikachu(this); }

	/* Get Pikachu speed */
	double GetSpeed();
};



