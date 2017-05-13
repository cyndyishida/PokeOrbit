/**
* \file GameItem.h
*
* \author Cyndy Ishida
*
* Class that implements a game item
*/


#pragma once

#include <memory>
#include <string>
#include "PlayingArea.h"

class CItemVisitor;
class CPlayingArea;

/**
* Base class called game item that gets derived from with other classes
*/
class CGameItem
{
public:
	/// default constructor (disabled)
	CGameItem() = delete;

	CGameItem(const CGameItem &) = delete;

	virtual ~CGameItem();

	virtual void SetImage(const std::wstring & file);

	virtual void Draw(Gdiplus::Graphics * graphics);

	/** the speed setting will be different for  this so need to know for this item type.*/
	//virtual bool IsPokeBall() { return false; };

	/** The X location of the item
	* \returns X location in pixels */
	double GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels */
	double GetY() const { return mY; }

	/** The R location of the item
	* \returns R location in pixels */
	double GetR() const { return mR; }

	/** Test this item to see if it has been clicked on
	* \param x X location on the playing area to test
	* \param y Y location on the playing area to test
	* \returns true if clicked on */
	virtual bool HitTest(int x, int y) { return false; };

	/// Determines if item is Pokeball
	virtual bool IsPokemon() { return false; };

	/// Handle updates for animation
	/// \param elapsed The time since the last update 
	virtual void Update(double elapsed) {}

	/// Get the playing area this game item is in
	/// \returns Playing Area pointer
	CPlayingArea *GetPlayingArea() { return mPlayingArea; }

	/** Set the item location
	* \param x X location 
	* \param y Y location */
	void SetLocation(double x, double y) { mX = x; mY = y; }

	/// returns height of item image
	int GetItemHeight() { return mItemImage->GetHeight(); }

	/// returns weight of item image
	int GetItemWidth() { return mItemImage->GetWidth(); }

	/** The directory where the images are stored */
	static const std::wstring ImagesDirectory;

	/** Set game item virtual X coordinate
	* \param x X coordinate */
	virtual void SetVirtualX(double x) { mVirtualX = x; }

	/** Set game item virtual Y coordinate
	* \param y Y coordinate */
	virtual void SetVirtualY(double y) { mVirtualY = y; }

	/** The virtual X location of the item
	* \returns virtual X location */
	virtual double GetVirtualX() { return mVirtualX; }

	/** The virtual Y location of the item
	* \returns virtual Y location */
	virtual double GetVirtualY() { return mVirtualY; }

	/** Set the rotation speed of the item
	* \param rotation The rotation speed of the game item */
	virtual void SetRotation(double rotation) {}

	/** Set the radius from the center
	* \param radius The radius from the center of the game item */
	void SetRadius(double radius) { mR = radius; }

	/// Get the game system time 
	virtual double GetTime() { return 0; }

	/** See if the pokestop is ready to be deleted
	* \param item The PokeStop to be checked
	* \returns Boolean True if ready to be deleted */
	bool DeletePokeStop(std::shared_ptr<CGameItem> item) { return false; }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) {};

protected:
	// CGameItem(CPlayingArea * playingArea, const std::wstring &filename);
	CGameItem(CPlayingArea *playingArea);

private:
	/// the playing area this item is contained in.
	CPlayingArea *mPlayingArea;

	/// item location in the playing area
	double mX = 0;	///< X location for the center of the item
	double mY = 0;	///< Y location for the center of the item.
	double mR = 0;  ///< R radius from the center of the area.

	/// image object for the game item to use
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

	/// speed in the X Direction
	double mSpeedX;

	/// speed in the y direction 
	double mSpeedY;

	/// The file for this item
	std::wstring mFile;

	/// virtual x coordinate
	double mVirtualX;

	/// virtual y coordinate
	double mVirtualY;
};
