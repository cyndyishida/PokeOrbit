/**
* \file Pokemon.h
*
* \author Jenn Proos
*
* Base class for a Pokemon
*/

#pragma once

#include "OrbitItem.h"

/**
* Base class for a Pokemon
*/
class CPokemon : public COrbitItem
{
public:
	/// Default constructor (disabled)
	CPokemon() = delete;

	/// Copy constructor (disabled)
	CPokemon(const CPokemon &) = delete;

	virtual ~CPokemon();

	/** Checks to see if item is Pokemon
	* \returns true */
	bool IsPokemon() { return true; }

protected:
	CPokemon(CPlayingArea *playingarea);
};

