/**
 * \file PokeStop.cpp
 *
 * \author Cyndy Ishida
 */


#include "stdafx.h"
#include <string>
#include "PokeStop.h"


using namespace Gdiplus;
using namespace std;

/// Pokestop Pre-click image color
//const wstring PokestopPreImageName(L"images/pokestop.png");
const wstring PokeStopReady = L"pokestop.png";

/// Pokestop post click image color
const wstring PokeStopUsed = L"pokestop-used.png";

/// max speed in the x direction
const static double MaxSpeedX = 100;

/// max speed in the y direction 
const static double MaxSpeedY = 50;

/// How much we offset drawing the PokeStop to the left of the center
const int OffsetLeft = 64;

/// How much we offset drawing the Pokestop above the center
const int OffsetDown = 32;


/**
 * Constructor
 * \param playingArea The playing area this orbitting item is a member of
 */
CPokeStop::CPokeStop(CPlayingArea *playingArea) : COrbitItem(playingArea)
{
	SetImage(PokeStopReady);

	LoadImage(mReadyPokeStop, PokeStopReady);
	LoadImage(mUsedPokeStop, PokeStopUsed);

}

/**
* Destructor
*/
CPokeStop::~CPokeStop()
{
}


/**
 * Loads images
 * \param image The image we are loading
 * \param name The name of the image
 */
void CPokeStop::LoadImage(std::unique_ptr<Gdiplus::Bitmap> &image, std::wstring name)
{
	wstring filename = ImagesDirectory + name;
	image = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (image->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}


/**
 * Draw this PokeStop
 * \param graphics The graphics context to draw on
 */
void CPokeStop::Draw(Gdiplus::Graphics *graphics)
{
	CGameItem::Draw(graphics);

		if (mState == Ready)
		{
			int wid = mReadyPokeStop->GetWidth();
			int hit = mReadyPokeStop->GetHeight();

			graphics->DrawImage(mReadyPokeStop.get(), (int)(GetX() - OffsetLeft), (int)(GetY() + OffsetDown - hit), wid, hit);
			mCanClick = true;
		}
		if (mState == Loading)
		{
			int wid = mUsedPokeStop->GetWidth();
			int hit = mUsedPokeStop->GetHeight();

			graphics->DrawImage(mUsedPokeStop.get(), (int)(GetX() - OffsetLeft), (int)(GetY() + OffsetDown - hit), wid, hit);

			mCanClick = false;
		}

}


/**
 * Check to see if pokestop was clicked on  
 * \param x X location of click
 * \param y Y location of click
 * \returns True if hit
 */
bool CPokeStop::HitTest(int x, int y)
{
	if (mCanClick == true)
	{
		if (abs((int)GetX() - (int)x) < 40 && abs((int)GetY() - (int)y) < 40)
		{
			mState = Loading;
			return true;
		}
		else
		{
			mState = Ready;
		}
	}

	return false;
}


/**
 * Changes PokeStop state to loading
 */
void CPokeStop::PokeStopLoad()
{
	mState = Loading;
}


/**
 * Changes PokeStop state to ready and reset click time
 */
void CPokeStop::ReadyPokeStop()
{
	mState = Ready;
	mPokeStopClick = 0;
}


/**
 * Update animation based on elapsed time
 * \param elapsed Time elapsed since program start
 */
void CPokeStop::Update(double elapsed)
{
	COrbitItem::Update(elapsed);

	mPokeStopClick += elapsed;

	if ((int)mPokeStopClick >= 15)
	{
		ReadyPokeStop();
	}
}