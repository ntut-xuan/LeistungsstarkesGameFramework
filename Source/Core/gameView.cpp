/*
 * gameView.cpp : implementation of the CGameView class
 * Copyright (C) 2002-2012 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * 2012-03-21 V4.7
 *      1. Add SetCapture in CGameView::OnLButtonDown() and RelaseCapture in 
 *         CGameView::OnLButtonUp() so that Mouse Events (OnLButtonUp and OnMouseMove)
 *         will be called even if the cursor is outside of the window.
 * 2012-05-13 V4.8
 *      1. Fix Ctrl-Q display bug. Add Invalidate() at the end of CGameView::OnKillFocus.
 */

#include "stdafx.h"
#include "game.h"

#include "gameDoc.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <direct.h>
#include <string.h>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Game/mygame.h"
#include "gameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameView

IMPLEMENT_DYNCREATE(CGameView, CView)

BEGIN_MESSAGE_MAP(CGameView, CView)
	//{{AFX_MSG_MAP(CGameView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_FILE_PAUSE, OnFilePause)
	ON_UPDATE_COMMAND_UI(ID_FILE_PAUSE, OnUpdateFilePause)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_BUTTON_PAUSE, OnButtonPause)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameView construction/destruction

CGameView::CGameView()
{
	// TODO: add construction code here

}

CGameView::~CGameView()
{
}

BOOL CGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGameView drawing

void CGameView::OnDraw(CDC* pDC)
{
	CGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	static bool first_ondraw = true;
	static bool second_ondraw = false;
	if (first_ondraw) {
		first_ondraw = false;	// The first ondraw does not show the Menu, etc.
		second_ondraw = true;   // So, it is skipped.
		Invalidate();			// Trigger the second ondraw.
		return;
	}
	if (second_ondraw) {		// The second ondraw shows everything. Therefore,
		second_ondraw = false;	//   the initialization progress can be shown.
		game_framework::CGame::Instance()->OnInitStates();
	}
	game_framework::CGame::Instance()->OnDraw();
}

/////////////////////////////////////////////////////////////////////////////
// CGameView printing

BOOL CGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGameView diagnostics

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CView::AssertValid();
}

void CGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameDoc* CGameView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDoc)));
	return (CGameDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGameView message handlers

void CGameView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	game_framework::CGame::Instance()->OnInit();
}

void CGameView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	game_framework::CGame::Instance()->OnLButtonDown(nFlags, point);
	CView::OnLButtonDown(nFlags, point);
}

void CGameView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	game_framework::CGame::Instance()->OnLButtonUp(nFlags, point);
	CView::OnLButtonUp(nFlags, point);
}

void CGameView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	game_framework::CGame::Instance()->OnRButtonDown(nFlags, point);
	CView::OnRButtonDown(nFlags, point);
}

void CGameView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	game_framework::CGame::Instance()->OnRButtonUp(nFlags, point);
	CView::OnRButtonUp(nFlags, point);
}

void CGameView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	game_framework::CGame::Instance()->OnKillFocus();
	Invalidate();
}

void CGameView::OnFilePause() 
{
	// TODO: Add your command handler code here
	game_framework::CGame::Instance()->OnFilePause();
	InvalidateRect(NULL);
}

void CGameView::OnUpdateFilePause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!game_framework::CGame::Instance()->IsRunning());	
}

void CGameView::OnFileNew() 
{
	// TODO: Add your command handler code here
	
}

void CGameView::OnButtonPause() 
{
	// TODO: Add your command handler code here
	OnFilePause();
}

void CGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	game_framework::CGame::Instance()->OnKeyDown(nChar, nRepCnt, nFlags);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGameView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	game_framework::CGame::Instance()->OnKeyUp(nChar, nRepCnt, nFlags);
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGameView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	game_framework::CGame::Instance()->OnMouseMove(nFlags, point);
	CView::OnMouseMove(nFlags, point);
}

void CGameView::OnSetFocus(CWnd* pOldWnd) 
{
	
	// TODO: Add your message handler code here
	game_framework::CGame::Instance()->OnSetFocus();	
	CView::OnSetFocus(pOldWnd);
}
