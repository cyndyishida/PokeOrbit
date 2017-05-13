/**
 * \file PokeStopVisitor.h
 *
 * \author Jenn Proos
 *
 * Class that implements a pokestop visitor
 */

#include "ItemVisitor.h"

#pragma once


/**
 * Class that describes a pokestop visitor
 */
class CPokeStopVisitor : public CItemVisitor
{
public:
	/// default constructor (disabled)
	CPokeStopVisitor() = delete;

	/// copy constructor (disabled)
	CPokeStopVisitor(const CPokeStopVisitor &) = delete;

	CPokeStopVisitor(CPlayingArea *playArea);

	virtual ~CPokeStopVisitor();

	/** Visit a CPokeStop object
	* \param pokestop Pokestop we are visiting */
	void VisitPokeStop(CPokeStop *pokestop);

	/** Get pokestop status
	* \returns Boolean true if loading */
	bool GetStopBool() { return mStopBool; };

private:
	/// Initialize pokestop boolean to false
	bool mStopBool = false;
};


