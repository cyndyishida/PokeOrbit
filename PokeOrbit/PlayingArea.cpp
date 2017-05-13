/**
* \file PlayingArea.cpp
*
* \author Cyndy Ishida
*/


#include "stdafx.h"
#include <cmath>
#include <sstream>
#include <omp.h>
#include "PlayingArea.h"
#include "PokeStopVisitor.h"
#include "PokemonVisitor.h"
#include"PokeBall.h"
#include "Pokeballs.h"
#include "Character.h"
#include "Charmander.h"
#include "Pikachu.h"
#include "SlowBro.h"
#include "PokeStop.h"
#include  "Emitter.h"


using namespace Gdiplus;
using namespace std;

/// Playing area width in virtual pixels
const static int Width = 1400;

/// Playing area height in virtual pixels
const static int Height = 1100;

/// Radius of the playing read in virtual pixels
const static int Radius = 500;

/// thread - max processors 
const int THREADS = 4;


/**
*  Constructor
*/
CPlayingArea::CPlayingArea() : mEmitter(this)
{
	mEmitter.OnInital();
}


/**
*  Destructor
*/
CPlayingArea::~CPlayingArea()
{
}


/**
* Draw the game area
* \param graphics The GDI+ graphics context to draw on
* \param width Width of the client window
* \param height Height of the client window
*/
void CPlayingArea::OnDraw(Gdiplus::Graphics *graphics, int width, int height)
{
	// Fill the background with black
	SolidBrush brush(Color::Black);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	//
	// Automatic Scaling
	//
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	float scale = min(scaleX, scaleY);
	mScale = scale;
	float radius = Radius;
	float xOffset = width / 2.0f;
	mXOffset = xOffset;
	float yOffset = height / 2.0f;
	mYOffset = yOffset;

	graphics->TranslateTransform(xOffset, yOffset);
	graphics->ScaleTransform(scale, scale);

	// From here on you are drawing virtual pixels...

	//
	// And the circle so you can see how this works...
	//
	Pen pen(Color::Green);
	graphics->DrawArc(&pen, -radius, -radius, radius * 2, radius * 2, 0, 360);

	// draw center character
	auto ash = make_shared<CCharacter>(this);
	ash->SetLocation(0, 0);
	ash->Draw(graphics);




	# pragma omp parallel for num_threads(THREADS) 
	for (auto item : mGamePieces)
	{
		item->Draw(graphics);
	}


    # pragma omp parallel for num_threads(THREADS) 
	for (auto ball : mGameBalls)
	{
		ball->Draw(graphics);
	}

}


/**
 * Adds game item to vector of game pieces
 * \param gamePiece Game piece to add
 */
void CPlayingArea::Add(std::shared_ptr<CGameItem> gamePiece)
{
	mGamePieces.push_back(gamePiece);
}



/**
 * Adds pokeballs to game pieces vector
 * \param gamePiece Pokeball to add
 */
void CPlayingArea::AddBall(std::shared_ptr<CPokeBall> gamePiece)
{
	mGameBalls.push_back(gamePiece);
}



/**
 * Test to see if we clicked on a game piece or nullptr
 * \param x coordinate of playing area
 * \param y coordinate of playing area
 * \returns object or nullptr 
 */
std::shared_ptr<CGameItem> CPlayingArea::HitTest(int x, int y)
{
	for (auto i = mGamePieces.rbegin(); i != mGamePieces.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return nullptr;
}



/**
 * Deletes a game piece from vector of game pieces
 * \param gamePiece Game piece to delete
 */
void CPlayingArea::Delete(std::shared_ptr<CGameItem> gamePiece)
{
	auto toDelete = find(mGamePieces.begin(), mGamePieces.end(), gamePiece);
	if (toDelete != mGamePieces.end())
	{
		mGamePieces.erase(toDelete);
	}
}



/**
 * Deletes pokeball from poke balls inventory
 * \param ball Pokeball to delete
 */
void CPlayingArea::DeleteBall(std::shared_ptr<CPokeBall> ball)
{
	auto toDelete = find(mGameBalls.begin(), mGameBalls.end(), ball);
	if (toDelete != mGameBalls.end())
	{
		mGameBalls.erase(toDelete);
	}
}



/**
 * Update animation based on elapsed time
 * \param elapsed Time elapsed since program start 
 */
void CPlayingArea::Update(double elapsed)
{

	UpdateTime(elapsed);

    mEmitter.TakeElapsed(elapsed);

	// deals with deleting the pokestop once it has expired.

	shared_ptr<CGameItem> expiredStop= nullptr;

	for (auto piece : mGamePieces)
	{
		piece->Update(elapsed);

			if (  mEmitter.DeletePokeStop(piece))
			{
				expiredStop = piece;
			}
	}

	Delete(expiredStop);

	shared_ptr<CPokeBall> toDeleteForRadius = nullptr;    // for the radius end 
	shared_ptr<CPokeBall> toDeleteForCollision = nullptr;  // for the collison end 
	shared_ptr<CGameItem> toDeleteItem = nullptr;		// for the game piece collection

	// iterate over balls to 1 check if clicked out, get the balls in right direction & erase
	
	for (auto ball : mGameBalls)
	{
		ball->Update(elapsed, mVirtualX, mVirtualY);

		double xCoordinate = ball->GetX();
		double yCoordinate = ball->GetY();


		 //for every ball check to see if it's collided with another piece so we can increment it.
				for (auto piece : mGamePieces)
				{
					if ( piece->IsPokemon() &&  abs((int)piece->GetX() - (int)xCoordinate) < 50  && abs((int)piece->GetY() - (int)yCoordinate) < 50 )
					{
						toDeleteItem = piece;
							
						// both cases require the deletion of the pokeball
						toDeleteForCollision = ball;
					}
						
				}
		if (sqrt(xCoordinate*xCoordinate + yCoordinate * yCoordinate) > Radius)
		{
			toDeleteForRadius = ball;
		}
	}

	// create visitor object for visitor incrementation
	CPokemonVisitor visitor(this);
	AcceptPokeBalls(&visitor);

	// calls the visitor function to increment the score 
	mCharmanderCaptured += visitor.GetCharmanderScore();
	mPikachuCaptured += visitor.GetPikachuScore();
	mSlowBroCaptured += visitor.GetSlowBroScore();

	// deletes the balls with collisions
	Delete(toDeleteItem);
	DeleteBall(toDeleteForRadius);
	DeleteBall (toDeleteForCollision);
}


/**
 * Click
 * \param pointX 
 * \param pointY 
 * \returns 
 */
bool CPlayingArea::Click(double pointX, double pointY)
{
	bool current = true;

	double virtualX = (pointX - mXOffset) / mScale;
	mVirtualX = virtualX;
	double virtualY = (pointY - mYOffset) / mScale;
	mVirtualY = virtualY;

	//create visitor object
	CPokeStopVisitor visitor(this);
	Accept(&visitor);

	for (auto piece : mGamePieces)
	{
		if (visitor.GetStopBool() && piece->HitTest((int)((pointX - mXOffset) / mScale),(int)( (pointY - mYOffset) / mScale) ))
		{
			current = false;

		}
	}

	// test to see if they clicked outside of circle
	if (sqrt(virtualX * virtualX + virtualY * virtualY) > Radius )
	{
		current = false;
	}

	return current;
}


/**
 * Accepts visitor
 * \param visitor 
 */
void CPlayingArea::Accept(CItemVisitor *visitor)
{
	for (auto piece : mGamePieces)
	{
		piece->Accept(visitor);
	}
}


/**
 * 
 * \param visitor 
 */
void CPlayingArea::AcceptPokeBalls(CItemVisitor *visitor)
{
	for (auto piece : mGameBalls)
	{
		piece->Accept(visitor);
	}
}


/** draws the number of pokemon user has captured 
 * 
 * \param graphics 
 */
void CPlayingArea::ScoreKeeper(Gdiplus::Graphics *graphics)
{
	// converting int to a wchar to use for drawing number of pokes captured


	if (mPikachuCaptured > 0)
	{
		auto pikachuScore = make_shared<CPikachu>(this);
		pikachuScore->SetLocation(700, -330);
		pikachuScore->Draw(graphics);
		
		// displaying an arial 16 pixel text
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, 16);
		
		SolidBrush white(Color::White);

		int old = mPikachuCaptured;
		wstringstream str;
		str << old << ends;

		RectF textSize;
		graphics->MeasureString(str.str().c_str(), -1, &font, PointF(0, 0), &textSize);
		graphics->DrawString(str.str().c_str(),	// string to draw
			-1,		// String length, -1 means it figures it out on its own
			&font,	// the font to use
			PointF(750, -330),		// where to draw (top left corner)
			&white);		// the brush to draw the text with.
	}


	if (mCharmanderCaptured > 0)
	{
		auto charmanderScore = make_shared<CCharmander>(this);
		charmanderScore->SetLocation(700, -175);
		charmanderScore->Draw(graphics);

		// displaying an arial 16 pixel text
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, 16);

		SolidBrush white(Color::White);


		int old = mCharmanderCaptured;
		wstringstream str;
		str << old << ends;

		RectF textSize;
		graphics->MeasureString(str.str().c_str(), -1, &font, PointF(0, 0), &textSize);

		graphics->DrawString(str.str().c_str(),	// string to draw
			-1,		// String length, -1 means it figures it out on its own
			&font,	// the font to use
			PointF(750, -175),		// where to draw (top left corner)
			&white);		// the brush to draw the text with.
	}



	if (mSlowBroCaptured > 0)
	{
		auto slowBrowScore = make_shared<CSlowBro>(this);
		slowBrowScore->SetLocation(700, -470);
		slowBrowScore->Draw(graphics);

		
		// displaying an arial 16 pixel text
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, 16);

		SolidBrush white(Color::White);


		int old = mSlowBroCaptured;
		wstringstream str;
		str << old << ends;

		RectF textSize;
		graphics->MeasureString(str.str().c_str(), -1, &font, PointF(0, 0), &textSize);

		graphics->DrawString(str.str().c_str(),	// string to draw
			-1,		// String length, -1 means it figures it out on its own
			&font,	// the font to use
			PointF(750, -470),		// where to draw (top left corner)
			&white);		// the brush to draw the text with.
	}
}


/**
 * Sets pokeball coordinates
 * \param pokeball 
 */
void CPlayingArea::SetCoordinates(std::shared_ptr<CPokeBall> pokeball) 
{
	pokeball->SetCoordinates(mVirtualX, mVirtualY);
}







/**
 * 
 * \param x 
 * \param y 
 * \returns 
 */
 bool CPlayingArea::CheckStops(double x, double y) 
{
	 bool current = false;

	 // iterate over my items if its a pokestop
	 // and its clicked on, add to the pokemon
	 for (auto item : mGamePieces)
	 {
		 if (item->HitTest((int)((x - mXOffset) / mScale), (int)((y - mYOffset) / mScale)))
		 {			 
			 current = true;
		 }
	 }
	 return current;
}