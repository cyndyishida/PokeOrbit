/**
* \file Pokeballs.h
*
* \author Cyndy Ishida
*
* Class that keeps track of pokeballs inventory
*/

#pragma once

#include <vector>
#include <memory>
#include "PlayingArea.h"

class CPokeBall;

/**
* Class that describes pokeballs inventory
*/
class CPokeballs
{
public:
	CPokeballs();

	virtual ~CPokeballs();

	/// Adds pokeballs to inventory 
	void AddPokeballs();

	/// Removes pokeballs from inventory
	/// \param pokeball The pokeball to remove 
	void RemovePokeballs(std::shared_ptr<CPokeBall> pokeball);

	/// Draws correct number of pokeballs
	/// \param graphics The graphics used to draw pokeballs
	void DrawNumBalls(Gdiplus::Graphics *graphics);

	/** The number of pokeballs currently in the inventory
	* \returns mNumBalls current total pokeballs in inventory */
	int GetNumBalls() { return mNumBalls; };

	/// Decrements appropriate number of pokeballs
	void Decrement();

private:
	/// Pokeballs count
	int mNumBalls = 0;

	/// an object that decribes our playing area
	CPlayingArea mPlayingArea;

	/// collection of our pokeballs
	std::vector<std::shared_ptr<CPokeBall>> mPokeballs;
};
