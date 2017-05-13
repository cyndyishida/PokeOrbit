
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"

#include "TeamProject1.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include "PlayingArea.h"
#include "PokeBall.h"
#include "Pokeballs.h"
#include "Character.h"
#include "Charmander.h"
#include "Pikachu.h"
#include "SlowBro.h"
#include "PokeStop.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace Gdiplus;
using namespace std;


/// number for time setter to kill pokeball in milliseconds
const int LifeOfPokeBall = 60000 ;

/// number for the time setter to revalidate the pokestop
const int ChangeStateTime = 15000;

/// frame duration in milliseconds 
const int FrameDuration = 30;


// 42 milliseconds on a timer for invalidate() 
// refreshes 24 frames re second 



// CChildView


/**
 * Constructor
 */
CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}


/**
 * Destructor
 */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()






// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}






void CChildView::OnPaint()
{
	CPaintDC paintDC(this); // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);

	CRect rect;
	GetClientRect(&rect);



	mPlayingArea.OnDraw(&graphics, rect.Width(), rect.Height());



	if (mFirstDraw)
	{
		mFirstDraw = false;

		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);

		mPokeballs.AddPokeballs();

	}

	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;


	if (mPlayingArea.GetAddState()) 
	{ 
		mPokeballs.AddPokeballs();
	}


	mPlayingArea.Update(elapsed);
	mPokeballs.DrawNumBalls(&graphics);
	mPlayingArea.ScoreKeeper(&graphics);
}





/**
* Erase the background
*
* This is disabled to eliminate flicker
* \param pDC Device context
* \returns FALSE
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}



/**
* Handle timer events
* \param nIDEvent The timer event ID
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{

	Invalidate();
	CWnd::OnTimer(nIDEvent);
}




/**
 * 
 * \param nFlags 
 * \param point 
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{	
	if (mPlayingArea.Click(point.x, point.y))
	{

		if (mPokeballs.GetNumBalls() > 0)
		{	
			auto pokeball = make_shared<CPokeBall>(&mPlayingArea);
			
			mPlayingArea.SetCoordinates(pokeball);
			pokeball->SetLocation(0, 0);
			mPlayingArea.AddBall(pokeball);
			mPokeballs.Decrement();
			Invalidate();
		}
	}

	/// testing to see if weve hit pokestop to add pokeballs 
	if (mPlayingArea.CheckStops(point.x, point.y))
	{
		mPokeballs.AddPokeballs();
	}

}


