/*
 * MainFrm.cpp : implementation of the CMainFrame class
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
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
 * History:
 *	 2004-03-04 V4.1
 *      1. Support OPEN_AS_FULLSCREEN flag.
 *		2. Enable WS_MAXIMIZEBOX.
 *      3. Override WindowProc() to process WS_MAXIMIZEBOX correctly and
 *            to disable WM_SYSCOMMANDs (except for SC_CLOSE) in full
 *            screen mode.
 */

#include "stdafx.h"
#include "game.h"

#include "MainFrm.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <direct.h>
#include <string.h>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Game/config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_TOGGLE_FULLSCREEN, OnToggleFullscreen)
	ON_WM_PAINT()
	ON_COMMAND(ID_BUTTON_FULLSCREEN, OnButtonFullscreen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	isFullScreen = OPEN_AS_FULLSCREEN;	
	isToolBarVisible = true;
	isStatusBarVisible = true;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable

	//
	// 確定ToolBar的位置為固定的，以便計算window size
	//
	// m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	// EnableDocking(CBRS_ALIGN_ANY);
	// DockControlBar(&m_wndToolBar);

	//
	// 儲存Menu的pointer
	//
	pMenu = GetMenu();
	//
	

	m_wndToolBar.ShowWindow(SW_HIDE);
	m_wndStatusBar.ShowWindow(SW_SHOW);
	// SetMenu(NULL);

	SetWindowText(_T(GAME_TITLE));

	// 如果是Full Screen的話，隱藏ToolBar, StatusBar, Menu
	//
	if (isFullScreen) {
		m_wndToolBar.ShowWindow(SW_HIDE);
		m_wndStatusBar.ShowWindow(SW_HIDE);
		ModifyStyle(WS_DLGFRAME, 0);
		SetMenu(NULL);
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	//	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
	//		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX;

	cs.cx = SIZE_X; cs.cy = SIZE_Y;
	cs.style = WS_SYSMENU | WS_MINIMIZEBOX;
    cs.x = (::GetSystemMetrics(SM_CXSCREEN) - cs.cx) / 2; 
	cs.y = (::GetSystemMetrics(SM_CYSCREEN) - cs.cy) / 2; 
	//  Set priority level
	AfxGetApp()->SetThreadPriority(THREAD_PRIORITY_HIGHEST);
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::SetFullScreen(bool isFull)
{
	static CRect WindowRect;
	bool FullScreenError = false;
	if (isFull) {
		isFullScreen = true;
		//
		// Store window position
		//

		GetWindowRect(WindowRect);

		if (!game_framework::CDDraw::SetFullScreen(true))
			FullScreenError = true;
		//
		// Store the states of tool bar, and status bar.
		//
		isToolBarVisible = m_wndToolBar.IsWindowVisible();
		isStatusBarVisible = m_wndStatusBar.IsWindowVisible();
		//
		// Make menu, tool bar, and status invisible.
		//
		m_wndToolBar.ShowWindow(SW_HIDE);
		m_wndStatusBar.ShowWindow(SW_HIDE);

		ModifyStyle(WS_DLGFRAME, 0);
		SetMenu(NULL);
	}
	if (!isFull || FullScreenError) {
		isFullScreen = false;
		ShowWindow(SW_NORMAL);
		game_framework::CDDraw::SetFullScreen(false);
		//
		// Recover menu, tool bar, and status bar
		//
		//SetMenu(NULL);
		if (isToolBarVisible)
			m_wndToolBar.ShowWindow(SW_NORMAL);
		m_wndStatusBar.ShowWindow(SW_SHOW);
		SetMenu(pMenu);
		ModifyStyle(0, WS_DLGFRAME);
		//
		// Restore window position
		//
		MoveWindow(WindowRect);
	}
	if (FullScreenError)
		MessageBox("Fullscreen Error (Incorrect Resolution?)");
}

void CMainFrame::OnToggleFullscreen() 
{
	// TODO: Add your command handler code here
	SetFullScreen(!isFullScreen);
}

void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CFrameWnd::OnPaint() for painting messages
	if (isFullScreen)
		return;

	int extra_height=0;
	CRect ClientRect;
	game_framework::CDDraw::GetClientRect(ClientRect);
	CalcWindowRect(&ClientRect, CWnd::adjustBorder);
	CRect ControlRect;
	if(m_wndToolBar.IsWindowVisible()) {
		m_wndToolBar.GetWindowRect(ControlRect);
		extra_height = ControlRect.bottom - ControlRect.top;
	}
	if(m_wndStatusBar.IsWindowVisible()) {
		m_wndStatusBar.GetWindowRect(ControlRect);
		extra_height += ControlRect.bottom - ControlRect.top;
	}
	extra_height += GetSystemMetrics(SM_CYMENU);
	CRect WindowRect;
	GetWindowRect(WindowRect);

	MoveWindow(WindowRect.left, WindowRect.top, SIZE_X, SIZE_Y + extra_height);
}

void CMainFrame::OnButtonFullscreen() 
{
	// TODO: Add your command handler code here
	SetFullScreen(!isFullScreen);
}


LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_SYSCOMMAND)
	{
		wParam &= 0xFFF0;
		if (!IsIconic()) {
			//
			// non-iconic
			//
			if (isFullScreen) {
				//
				// If fullscreen, disable all SYSCOMMANDs except for SC_CLOSE
				//
				if (wParam != SC_CLOSE)
					return 0;
			} else {
				//
				// If non-fullscreen, process SC_MAXIMIZE and leave the
				//		other SYSCOMMANDs to base class.
				//
				if (wParam == SC_MAXIMIZE)
				{
					SetFullScreen(true);
					return 0;
				}
			}
		} else {
			//
			// If Iconic, disable SC_MAXIMIZE.
			//
			if (wParam == SC_MAXIMIZE)
				return 0;
		}
	} else if (message == WM_POWERBROADCAST) {
		if (wParam == PBT_APMSUSPEND)
			game_framework::CGame::Instance()->OnSuspend();
		else if (wParam == PBT_APMRESUMECRITICAL || wParam == PBT_APMRESUMESUSPEND)
			game_framework::CGame::Instance()->OnResume();
	}
	return CFrameWnd::WindowProc(message, wParam, lParam);
}
