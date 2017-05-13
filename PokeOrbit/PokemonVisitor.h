/**
* \file PokemonVisitor.h
*
* \author Jenn Proos
*
* Class that implements a Pokemon visitor
*/

#pragma once

#include "ItemVisitor.h"


/**
* Class that describes a pokemon visitor
*/
class CPokemonVisitor :
	public CItemVisitor
{
public:
	/// default contstructor disabled
	CPokemonVisitor() = delete;

	/// default copy constructor disabled
	CPokemonVisitor(const CItemVisitor &) = delete;

	CPokemonVisitor(CPlayingArea *playArea);

	virtual ~CPokemonVisitor();

	/** Visit a CPokeball object
	* \param pokeball Pokeball we are visiting */
	void VisitPokeball(CPokeBall *pokeball);

	/** Visit a CCharmander object
	* \param charmander Charmander we are visiting */
	void VisitCharmander(CCharmander * charmander);

	/** Visit a CPikachu object
	* \param pikachu Pikachu we are visiting */
	void VisitPikachu(CPikachu * pikachu);

	/** Visit a CSlowBro object
	* \param slowbro Slow Bro we are visiting */
	void VisitSlowBro(CSlowBro * slowbro);

	/** Get the Pikachu count
	* \returns Number of caught Pikachus */
	int GetPikachuScore() const { return mPikachuScore; }

	/** Get the Charmander count
	* \returns Number of caught Charmanders */
	int GetCharmanderScore() const { return mCharmanderScore; }

	/** Get the Slow Bro count
	* \returns Number of caught Slow Bros */
	int GetSlowBroScore() const { return mSlowBroScore; }

private:
	/// Pikachu counter
	int mPikachuScore = 0;

	/// Charmander counter
	int mCharmanderScore = 0;

	/// Slow Bro counter
	int mSlowBroScore = 0;
};
