
// ChildView.h : interface of the CChildView class
//

#pragma once

#include "PlayingArea.h"
#include <time.h>
#include "Pokeballs.h"
#include "PokeStop.h"

// CChildView window


/**
 * Class that implements the child view
 */
class CChildView : public CWnd
{
	// Construction
public:
	CChildView();

	// Attributes
public:

	// Operations
public:

	// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	/// On paint
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	/// An object that describes our playing area
	CPlayingArea mPlayingArea;

	/// An inventory of playing area pokeballs
	CPokeballs mPokeballs;

	/// true the first time we draw 
	bool mFirstDraw = true;

	long long mLastTime; ///< Last time we read the timer
	double mTimeFreq; ///< Rate the timer updates
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
