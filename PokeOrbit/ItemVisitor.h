/**
* \file ItemVisitor.h
*
* \author Jenn Proos
*
* Class that implements an item visitor
*/


#pragma once

#include "PlayingArea.h"

// Forward reference
class CCharmander;
class CPikachu;
class CSlowBro;
class CPokeStop;
class CPokeBall;
class CPokeBalls;


/**
* Item visitor base class
*/
class CItemVisitor
{
public:
	/// default contstructor disabled
	CItemVisitor() = delete;

	/// default copy constructor disabled
	CItemVisitor(const CItemVisitor &) = delete;

	virtual ~CItemVisitor();

	/** Visit a CCharmander object
	* \param charmander Charmander we are visiting */
	virtual void VisitCharmander(CCharmander *charmander) {}

	/** Visit a CPikachu object
	* \param pikachu Pikachu we are visiting */
	virtual void VisitPikachu(CPikachu *pikachu) {}

	/** Visit a CSlowBro object
	* \param slowbro Slow Bro we are visiting */
	virtual void VisitSlowBro(CSlowBro *slowbro) {}

	/** Visit a CPokeStop object
	* \param pokestop Pokestop we are visiting */
	virtual void VisitPokeStop(CPokeStop *pokestop) {}

	/** Visit a CPokeBall object
	* \param pokeball Pokeball we are visiting */
	virtual void VisitPokeball(CPokeBall *pokeball) {}

	/// Get the playing area this item is in
	/// \returns playing area pointer 
	CPlayingArea* GetArea() { return mPlayingArea; }

protected:
	CItemVisitor(CPlayingArea *playarea);

private:
	/// The playing area this visitor is a member of
	CPlayingArea *mPlayingArea;
};

