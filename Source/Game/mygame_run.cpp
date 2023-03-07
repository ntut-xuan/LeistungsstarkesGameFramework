#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <string>

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

vector<string> generatePath (string initPath)
{
	vector<string> path;
	for (int i=1; i<=8; i++)
	{
		string tmpPath = initPath + std::to_string(i) + ".bmp";
		path.push_back(tmpPath);
	}
	return  path;
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({ "resources/map.bmp" });
	background.SetTopLeft(0, 0);
	// test.LoadBitmapByString({"resources/towers/monkey/tower_monkey_1.bmp", "resources/towers/monkey/tower_monkey_3.bmp"}, RGB(0, 0, 0));
	test.LoadBitmapByString({{generatePath("resources/towers/monkey/tower_monkey_")}}, RGB(0, 0, 0));
    UnitInit();
	map.InitRoad();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_F1)
	{
		int index = (test.GetFrameIndexOfBitmap() + 1) % 8;
		test.SetFrameIndexOfBitmap(index);
	}
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
	test.SetCenter(p.x, p.y);
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
	map.ShowRoad();
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
