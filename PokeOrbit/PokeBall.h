/**
* \file PokeBall.h
*
* \author Cyndy Ishida
*
* Class that implements a pokeball
*/


#pragma once

#include "GameItem.h"


/**
*  Class PokeBall, derived from CGameItem
*/
class CPokeBall :
	public CGameItem
{
public:
	/// Default constructor (disabled)
	CPokeBall() = delete;

	/// Copy Constructor (disabled)
	CPokeBall(const CPokeBall &) = delete;

	CPokeBall(CPlayingArea * playingArea);

	virtual ~CPokeBall();

	/** Handle updates for animation
	* \param elapsed The time since the last update
	* \param x X coordinate of pokeball
	* \param y Y coordinate of pokeball */
	void Update(double elapsed, double x, double y);

	/** Set the pokeball coordinates
	* \param virtualX The virtual X coordinate
	* \param virtualY The virtual Y coordinate */
	void SetCoordinates(double virtualX, double virtualY);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override;

private:

	/// X coordinate of click
	double mClickX;

	/// Y coordinate of click
	double mClickY;
};

