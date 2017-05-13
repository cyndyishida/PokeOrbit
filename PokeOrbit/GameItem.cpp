/**
 * \file GameItem.cpp
 *
 * \author Cyndy Ishida
 */


#include "stdafx.h"
#include "GameItem.h"
#include "PlayingArea.h"


using namespace Gdiplus;
using namespace std;

/// The directory containing the file images
const std::wstring CGameItem::ImagesDirectory = L"images/";

/// How much we offset drawing the game item to the left of the center
const int OffsetLeft = 64;

/// How much we offset drawing the game item above the center
const int OffsetDown = 32;


/**
 * Constructor
 * \param playingArea The playing area this item is a member of
 */
CGameItem::CGameItem(CPlayingArea *playingArea) : mPlayingArea(playingArea)
{
	mVirtualX = playingArea->GetVirtualX();
	mVirtualY = playingArea->GetVirtualY();
}


/**
* Destructor
*/
CGameItem::~CGameItem()
{
}


/**
  * Set the image tile to draw
  * \param file The base filename. Blank files are allowed
  */
void CGameItem::SetImage(const std::wstring &file)
{
	if (!file.empty())
	{
		wstring filename = ImagesDirectory + file;
		mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
		//mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(file.c_str()));
		if (mItemImage->GetLastStatus() != Ok)
		{
			wstring msg(L"Failed to open ");
			msg += filename;
			//msg += file;
			AfxMessageBox(msg.c_str());
			return;
		}
	}
	else
	{
		mItemImage.release();
	}

	mFile = file;
}


/**
  * Draw our game item
  * \param graphics The graphics context to draw on
  */
void CGameItem::Draw(Gdiplus::Graphics * graphics)
{
	if (mItemImage != nullptr) 
	{
		int wid = mItemImage->GetWidth();
		int hit = mItemImage->GetHeight();

		graphics->DrawImage(mItemImage.get(),(int)( mX - OffsetLeft), (int)(mY + OffsetDown - hit), wid, hit);
	}
}
