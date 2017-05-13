/**
* \file OrbitItem.h
*
* \author Cyndy Ishida
*
* Class that implements an orbitting item
*/


#pragma once

#include <math.h>
#include "GameItem.h"
#include "ItemVisitor.h"


/**
* Class that describes an orbitting item
*/
class COrbitItem :
	public CGameItem
{
public:
	/// default contstructor disabled
	COrbitItem() = delete;

	/// default copy constructor disabled
	COrbitItem(const COrbitItem &) = delete;

	virtual ~COrbitItem();

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	void Update(double elapsed);

	/** The speed of the orbitting item
	* \returns Rotation speed of item */
	virtual double GetSpeed() { return mRotationSpeed; }

	/** Set orbit item rotation speed
	* \param rotation Rotation */
	void SetRotation(double rotation) { mRotationSpeed = rotation; }

	/** Set orbit item radius
	* \param radius Radius */
	void SetRadius(double radius) { mRadius = radius; }

protected:
	//COrbitItem(CPlayingArea *playingarea, const std::wstring &filename);
	COrbitItem(CPlayingArea *playingarea);

private:
	/// Pokemon radius from the center of the circle
	double mRadius;

	/// Pokemon speed in the X direction
	double mSpeedX;

	/// Pokemon speed in the Y direction
	double mSpeedY;

	/// Pokemon speed around the center of the play area
	double mRotationSpeed;
};
