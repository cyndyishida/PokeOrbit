/**
* \file PlayingArea.h
*
* \author Cyndy Ishida
*
* Class that describes the playing area
*/

#pragma once

#include <vector>
#include <memory>
#include "Emitter.h"

class CGameItem;
class CPokeBall;
class CItemVisitor;

/**
* Class that describes the playing area
*/
class CPlayingArea
{
public:
	CPlayingArea();

	virtual ~CPlayingArea();

	void OnDraw(Gdiplus::Graphics *graphics, int width, int height);

	std::shared_ptr<CGameItem> HitTest(int x, int y);

	void Add(std::shared_ptr<CGameItem> gamePiece);

	void AddBall(std::shared_ptr<CPokeBall> gamePiece);

	void Delete(std::shared_ptr<CGameItem> gamePiece);

	void DeleteBall(std::shared_ptr<CPokeBall> ball);

	void Update(double elapsed);

	bool Click(double pointX, double pointY);

	void ScoreKeeper(Gdiplus::Graphics * graphics);

	/** Get virtual X coordinate
	* \returns X virtual coordinate */
	double GetVirtualX() { return mVirtualX; }

	/** Get virtual Y coordinate
	* \returns Y virtual coordinate */
	double GetVirtualY() { return mVirtualY; }

	void SetCoordinates(std::shared_ptr<CPokeBall> pokeball);

	bool CheckStops(double x, double y);

	/** Get state of adding 
	* \returns boolean Current state*/
	bool GetAddState()
	{
		bool current = false;
		if (mAddState)
		{
			current = true;
			mAddState = false;
		}

		return current;
	}

	/** Update game time
	* \param seconds Elapsed time since program start 
	* \returns mGameTime game time*/
	void UpdateTime(double seconds) { mGameTime = seconds; }

	/** Get the game time
	* \returns mGameTime in seconds */
	double GetTime() { return (mGameTime * 1000); }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	void Accept(CItemVisitor *visitor);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	void AcceptPokeBalls(CItemVisitor *visitor);

	/** iterator that iterates over the game pieces*/
	class Iter
	{
	public:
		/** Constructor
		* \param playingArea the playing area
		* \param pos Position in collection
		*/
		Iter(CPlayingArea *playingArea, int pos) : mPlayingArea(playingArea), mPos(pos) {}

		/** Test for end of the iterator
		* \param &other iterator
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CGameItem> operator *() const { return mPlayingArea->mGamePieces[mPos]; }

		/** Increment the iterator
		* \returns Reference to this iterator */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}

	private:
		CPlayingArea *mPlayingArea;   ///< playingarea we are iterating over
		int mPos;       ///< Position in the collection
	};


	/** Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, mGamePieces.size()); }

private:
	/// inventory 
	std::vector<std::shared_ptr<CGameItem>> mGamePieces;

	/// pokeball inventory 
	std::vector<std::shared_ptr<CPokeBall>> mGameBalls;

	/// boolean to know when to add, then draw in childview
	bool mAddState = false;

	///  system time of game
	double mGameTime;

	/// scale
	double mScale;

	/// X offset
	double mXOffset;

	/// Y offset
	double mYOffset;

	/// virtual X coordinate
	double mVirtualX;

	/// virtual Y coordinate 
	double mVirtualY;

	/// Number of captured Pikachus
	int mPikachuCaptured = 0;

	/// Number of captured Charmanders
	int mCharmanderCaptured = 0;

	/// Number of captured Slow Bros
	int mSlowBroCaptured = 0;

	/// the emitter class of the function. 
	CEmitter mEmitter;
};