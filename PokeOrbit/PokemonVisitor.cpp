/**
 * \file PokemonVisitor.cpp
 *
 * \author Cyndy Ishida
 */


#include "stdafx.h"
#include "PokemonVisitor.h"
#include "GameItem.h"
#include "PokeBall.h"


/**
 * Constructor
 * \param playArea The playing area this item visitor is a member of
 */
CPokemonVisitor::CPokemonVisitor(CPlayingArea * playArea) : CItemVisitor(playArea)
{
}


/**
 * Destructor
 */
CPokemonVisitor::~CPokemonVisitor()
{
}


/**
 * Pokeball visit
 * \param pokeball Pokeball we are visiting
 */
void CPokemonVisitor::VisitPokeball(CPokeBall * pokeball)
{

	double xCoordinate = pokeball->GetX();
	double yCoordinate = pokeball->GetY();


	for (auto i = CItemVisitor::GetArea()->begin(); i != CItemVisitor::GetArea()->end(); ++i)
	{
		if ((*i)->IsPokemon())
		{
			if (abs((int)(*i)->GetX() - (int)xCoordinate) < 50 && abs((int)(*i)->GetY() - (int)yCoordinate) < 50)
			(*i)->Accept(this);
		}
	}
}


/**
 * Visit charmander
 * \param charmander Charmander we visit
 */
void CPokemonVisitor::VisitCharmander(CCharmander *charmander) 
{
	mCharmanderScore++;
}


/**
 * Visit pikachu
 * \param pikachu Pikachu we visit
 */
void CPokemonVisitor::VisitPikachu(CPikachu *pikachu)
{
	mPikachuScore++;
}



/**
 * Visit slow bro
 * \param slowbro Slow Bro we visit
 */
void CPokemonVisitor::VisitSlowBro(CSlowBro *slowbro)
{
	mSlowBroScore++;
}