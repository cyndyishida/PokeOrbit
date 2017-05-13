/**
* \file Emitter.cpp
*
* \author Cyndy Ishida
*/

#include "stdafx.h"
#include <memory>
#include <stdlib.h>   
#include "Emitter.h"
#include "PlayingArea.h"

#include "Pokemon.h"
#include "PokeStop.h"
#include "Pikachu.h"
#include "Charmander.h"
#include "SlowBro.h"


using namespace std;


/**
 * Constructor 
 * \param PlayingArea The playing area this emitter is a member of
 */
CEmitter::CEmitter(CPlayingArea *PlayingArea) : mPlayingArea(PlayingArea)
{
}


/**
 * Destructor
 */
CEmitter::~CEmitter()
{
}


/**
 * Adds Pikachu to playing area
 */
void CEmitter::AddPikachu()
{
	auto poke = make_shared<CPikachu>(mPlayingArea);
	int x = rand() % 250 + 50;
	int y = rand() % 250 + 50;
	double rot = rand() % 1 + 0.25;
	poke->SetLocation(x, y);
	poke->SetRadius(sqrt(x * x + y * y));
	poke->SetRotation(rot);
	mPlayingArea->Add(poke);
	mPokemonTime = mElapsed;

}


/**
 * Adds Charmander to playing area
 */
void CEmitter::AddCharmander()
{
	auto poke = make_shared<CCharmander>(mPlayingArea);
	int x = rand() % 250 + 50;
	int y = rand() % 250 + 50;
	double rot = rand() % 1 + 0.25;
	poke->SetLocation(x, y);
	poke->SetRadius(sqrt(x * x + y * y));
	poke->SetRotation(rot);
	mPlayingArea->Add(poke);
	mPokemonTime = mElapsed;


}


/**
 * Adds Slow Bro to playing area
 */
void CEmitter::AddSlowBro()
{
	auto poke = make_shared<CSlowBro>(mPlayingArea);
	int x = rand() % 250 + 50;
	int y = rand() % 250 + 50;
	double rot = rand() % 1 + 0.25;
	poke->SetLocation(x, y);
	poke->SetRadius(sqrt(x * x + y * y));
	poke->SetRotation(rot);
	mPlayingArea->Add(poke);
	mPokemonTime = mElapsed;
}


/**
 * Adds Poke Stop to playing area
 */
void CEmitter::AddPokeStop()
{
	auto pokeStop = make_shared<CPokeStop>(mPlayingArea);
	int x = rand() % 250 + 50;
	int y = rand() % 250 + 50;
	double rot = rand() % 1 + 0.25;
	pokeStop->SetLocation(x, y);
	pokeStop->SetRadius(sqrt(x * x + y * y));
	pokeStop->SetRotation(rot);
	pokeStop->SetTime(mElapsed);
	mPlayingArea->Add(pokeStop);
	mPokestopTime = mElapsed;

}


/**
 * Emits game items based on elapsed time
 * \param elapsed Elapsed time since program start
 */
void CEmitter::TakeElapsed(double elapsed)
{
	mElapsed += elapsed;

	double pokeTimeDiff = mElapsed - mPokemonTime;
	double stopTimeDiff = mElapsed - mPokestopTime;

	if (pokeTimeDiff >= 3)
	{
		mTemp = rand() % 7;

		if (mTemp == 0)
		{

			AddPikachu();
		}
		if (mTemp == 1)
		{
			AddCharmander();
		}
		if (mTemp == 2)
		{
			AddSlowBro();

		}

	}

	if (stopTimeDiff > 10)
	{
		AddPokeStop();
	}


}



/**
 * Emits initial Pokemon and Pokestop
 */
void CEmitter::OnInital()
{
	srand((int)time(NULL));
	mTemp = rand() % 3;

	if (mTemp == 0)
	{
		AddPikachu();

	}
	else if (mTemp == 1)
	{
		AddSlowBro();

	}
	else if (mTemp == 2)
	{
		AddCharmander();

	}

	AddPokeStop();
}


/**
 * Checks if Pokestop should be delete
 * \param pokeStop Pokestop to check
 * \returns True if it's time to delete the PokeStop
 */
bool CEmitter::DeletePokeStop(shared_ptr<CGameItem> pokeStop)
{
	if ((mElapsed - pokeStop->GetTime()) >= 60 && typeid(*pokeStop) == typeid(CPokeStop) ) 
	{
		return true;
	}
	return false;
}