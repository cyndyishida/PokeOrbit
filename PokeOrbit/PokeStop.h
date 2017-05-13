/**
 * \file PokeStop.h
 *
 * \author Cyndy Ishida
 *
 * Class that implements a PokeStop
 */


#pragma once

#include <memory>
#include <string>
#include "OrbitItem.h"


/**
 * Class CPokeStop Derived from CGameItem
 */
class CPokeStop :
	public COrbitItem
{
public:
	CPokeStop(CPlayingArea *playingArea);

	/// default constructor (disabled)
	CPokeStop()= delete;

	/// copy constructor (disabled)
	CPokeStop(const CPokeStop &) = delete;
	
	virtual ~CPokeStop();

	/** Draw this pokestop
	* \param graphics The graphics context to draw on */
	virtual void Draw(Gdiplus::Graphics * graphics);

	/** Test this pokestop to see if it has been clicked on
	* \param x X location of the playing area to test
	* \param y Y location of the playing area to test */
	bool HitTest(int x, int y) override;

	void PokeStopLoad();

	void Update(double elapsed);

	void ReadyPokeStop();

	/// The possible pokestop states
	enum States {Ready, Loading};

	void LoadImage(std::unique_ptr<Gdiplus::Bitmap> &image, std::wstring name);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitPokeStop(this); }

	/** Set game system time
	* \param time System time */
	void SetTime(double time) { mTime = time; }

	/** Get the game system time
	* \returns mTime System time */
	double GetTime() { return mTime; }
	
	/** Check to see if pokestop was clicked
	* \returns Boolean true if clicked */
	bool WasClicked() { return mClicked; };

private:
	/// The initial pokestop state
	States mState = Ready;

	/// The file string
	std::wstring mFile;

	/// The ready pokestop 
	std::unique_ptr<Gdiplus::Bitmap> mReadyPokeStop;

	/// The used pokestop
	std::unique_ptr<Gdiplus::Bitmap> mUsedPokeStop;

	/// Initialize pokestop clickable to true
	bool mCanClick = true;
	
	/// Game system time
	double mTime= 0 ;

	/// Initialize pokestop click to false
	bool mClicked = false;

	/// Time since last pokestop click
	double mPokeStopClick = 0;

	/// PokeStop life since emission
	double mPokeStopLife = 0;
};

