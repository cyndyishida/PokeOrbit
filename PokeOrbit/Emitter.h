/**
* \file Emitter.h
*
* \author Cyndy Ishida
*
* Class that implements an emission.
*/

#pragma once

#include <memory>

class CPlayingArea;
class CGameItem;
class CPokeStop;


/**
* Class that describes an emitter that will
* push game items to playing area
*/
class CEmitter {
public:
	/// default contructor disabled 
	CEmitter() = delete;

	/// default copy constructor disabled
	CEmitter(const CEmitter &) = delete;

	CEmitter(CPlayingArea *playarea);

	virtual ~CEmitter();

	/// Add Pikachu to playing area
	void AddPikachu();

	/// Add Charmander to playing area
	void AddCharmander();

	/// Add Slow Bro to playing area
	void AddSlowBro();

	/// Add PokeStop to playing area
	void AddPokeStop();

	/// Takes in elapsed and does appropriate emissions
	void TakeElapsed(double elapsed);

	/// Emits initial pokemon and pokestop
	void OnInital();

	/// Returns true if PokeStop life is up
	bool DeletePokeStop(std::shared_ptr<CGameItem> pokeStop);

private:
	/// The playing area the emitter is contained in
	CPlayingArea *mPlayingArea;

	double mPokestopTime = 0;	///< PokeStop time since last emit

	double mPokemonTime = 0;	///< Pokemon time since last emit

	double mElapsed = 0;	///< Elapsed time

	int mTemp = 0;		///< temp value used to determine random pokemon
};


