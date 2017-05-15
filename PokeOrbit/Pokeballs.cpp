#include "stdafx.h"
#include <memory>
#include <algorithm>
#include "PokeBall.h"
#include "Pokeballs.h"
#include "DoubleBufferDC.h"



/// the left edge of screen to add/remove pokeballs
const signed int XLocation = -700;

/// the top edge location to add/remove pokeballs
const signed int YLocation = -500;

/// the multiple of which the pokeballs should be spaced between each other
const signed int Incrementer = 75;



/// number of processors 
const int THREADS = 4;


using namespace Gdiplus;
using namespace std;



/**
 * Constructor
 */
CPokeballs::CPokeballs()
{
}


/**
 * Destructor
 */
CPokeballs::~CPokeballs()
{
}


/**
 * Add pokeballs to inventory
 */
void CPokeballs::AddPokeballs()
{
	if (mNumBalls <= 13) 
	{
		#pragma omp parallel for num_threads(THREADS) reduction(+ : mNumBalls)
		for (int i = 0; i < 3; i++)
		{
			if (mNumBalls > 13)
			{
				break;
			}
			mNumBalls += 1;
		}
	}
}

/**
 * Remove pokeballs from inventory
 * \param pokeball Pokeball to remove
 */
void CPokeballs::RemovePokeballs(std::shared_ptr<CPokeBall> pokeball)
{
}


/**
 * Draw correct number of pokeballs 
 * \param graphics The graphics context to draw on
 */
void CPokeballs::DrawNumBalls(Gdiplus::Graphics  *graphics)
{
	#pragma omp parallel for num_threads(THREADS)
 	for (int i = 0; i < mNumBalls; i++)
	{
		auto pokeball = make_shared<CPokeBall>(&mPlayingArea);
		pokeball->SetLocation(XLocation, YLocation + (i * Incrementer));
		pokeball->Draw(graphics);
		mPokeballs.push_back(pokeball);
	}
}


/**
 * Decrement pokeballs
 */
void CPokeballs::Decrement()
{
	if (mNumBalls > 0)
	{
		mNumBalls -= 1;

		auto pokeToDelete = mPokeballs.end() - 1;
		mPokeballs.erase(pokeToDelete);
	}
}





