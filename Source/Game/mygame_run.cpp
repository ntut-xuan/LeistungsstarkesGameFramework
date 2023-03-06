#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove() // 移動遊戲元素
{
    UnitTest();
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({ "resources/map.bmp" });
	background.SetTopLeft(0, 0);
	test.LoadBitmapByString({"resources/tower_monkey.bmp"}, RGB(255, 255, 255));
    UnitInit();
	initRoad();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
	POINT p;
	GetCursorPos(&p);
	HWND hwnd = FindWindowA(NULL, "Game");
	ScreenToClient(hwnd, &p);
	test.SetTopLeft(p.x, p.y);
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	for (int i = 0; i < 15; i++) {
		road[i].ShowBitmap();
	}
	test.ShowBitmap();
    UnitShow();
}

void CGameStateRun::UnitInit()
{
    switch (UNIT_TEST_STATE)
    {
    case throwable:
        THROWABLE.LoadEmptyBitmap(100, 100);
        THROWABLE.SetTopLeft(0, 0);
        THROWABLE.SetSpeed(2);
        THROWABLE.SetMoveDirection(1, 1);
    // break;
    case dart:
    // break;
    default:
        break;
    }
}

void CGameStateRun::UnitTest()
{
    switch (UNIT_TEST_STATE)
    {
    case throwable:
        THROWABLE.Move();
        break;
    case dart:
        break;
    default: ;
    }
}

void CGameStateRun::UnitShow()
{
    switch (UNIT_TEST_STATE)
    {
    case throwable:
        THROWABLE.ShowBitmap();
        break;
    case dart:
        break;
    default:
        break;
    }
}

void CGameStateRun::initRoad()
{
	char buff[100];
	string roadFileName;
	vector<Btd::Vector2> location{{0, 320}, {105, 124}, {170, 124},
									{285, 190}, {285, 390}, {43, 510},
									{43, 575}, {110, 636}, {620, 426},
									{429, 428}, {429, 249}, {496, 249},
									{622, 46}, {368, 48}, {368, 0}};
	for (int i = 0; i < 15; i++) {
		Btd::GameObject tmpRoad;
		sprintf(buff, "resources/roads/road_%d.bmp", i+1);
		tmpRoad.LoadBitmapByString({ buff });
		tmpRoad.SetTopLeft((int)location[i].X, (int)location[i].Y);
		tmpRoad.SetTag("road");
		road.push_back(tmpRoad);
	}
}
