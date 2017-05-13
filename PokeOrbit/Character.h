/**
* \file Character.h
*
* \author Cyndy Ishida
*
* Class that implements Ash character
*/

#pragma once


#include "GameItem.h"


/**
* Class that describes main character
*/
class CCharacter : public CGameItem
{
public:
	/// default contstructor disabled
	CCharacter() = delete;

	/// default copy constructor disabled
	CCharacter(const CCharacter &) = delete;

	CCharacter(CPlayingArea * playingArea);

	virtual ~CCharacter();

	/** Accept a visitor
	* \param visitor The visitor we accept */
	void Accept(CItemVisitor *visitor) {}
};


