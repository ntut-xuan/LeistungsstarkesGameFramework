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
    background.LoadBitmapByString({"resources/map.bmp"});
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
    HWND hwnd = FindWindowA(nullptr, "Game");
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
    for (int i = 0; i < 15; i++)
    {
        road[i].ShowBitmap();
    }
    test.ShowBitmap();
    UnitShow();
}

void CGameStateRun::UnitInit()
{
    switch (UNIT_TEST_STATE)
    {
    case Throwable:
        THROWABLE.LoadEmptyBitmap(100, 100);
        THROWABLE.SetTopLeft(0, 0);
        THROWABLE.SetSpeed(2);
        THROWABLE.SetMoveDirection(1, 1);
    // break;
    case DartMonkey:
        DART_MONKEY.LoadEmptyBitmap(50, 50);
        DART_MONKEY.SetTopLeft(100, 100);
    // DARTMONKEY.SetThrowableName("dart");
    // break;
    case BalloonMove:
        BALLOON.LoadEmptyBitmap(30, 30);
        BALLOON.SetTopLeft(10, 10);
        BALLOON.SetActive(false);
        BALLOON.SetNowRouteTarget(0);
        BALLOON.Setspeed(3);
    case BalloonVectorMove:
        BALLOONS.push_back(BALLOON);
    default:
        break;
    }
}

void CGameStateRun::UnitTest()
{
    switch (UNIT_TEST_STATE)
    {
    case Throwable:
        THROWABLE.Move();
        if (THROWABLE.GetTop() > 10)
        {
            UNIT_TEST_STATE = BalloonMove;
        }
        break;
    case DartMonkey:
        //shoot test
        break;
    case BalloonMove:

        BALLOON.Move({{500, 500}});
        if (BALLOON.GetTop() > 30)
        {
            UNIT_TEST_STATE = BalloonVectorMove;
        }
        break;
    case BalloonVectorMove:


        BALLOONS[0].Move({{500, 500}});
        if (BALLOONS[0].GetLeft() > 100)
        {
            UNIT_TEST_STATE = BalloonFactory;
        }
        break;
    case BalloonFactory:
        if (BALLOON_FACTORY.BallonVector.size() < 10)
        {
            BALLOON_FACTORY.MakeBallon("a");
        }
        for (auto& ballon : BALLOON_FACTORY.BallonVector)
        {
            ballon.Move({{500, 500}});
        }

        break;
    default: ;
    }
}

void CGameStateRun::UnitShow()
{
    switch (UNIT_TEST_STATE)
    {
    case Throwable:
        THROWABLE.ShowBitmap();
        break;
    case DartMonkey:
        DART_MONKEY.ShowBitmap();
        break;
    case BalloonMove:
        BALLOON.ShowBitmap();
        break;
    case BalloonVectorMove:
        BALLOONS[0].ShowBitmap();
        break;
    case BalloonFactory:
        for (auto& ballon : BALLOON_FACTORY.BallonVector)
        {
            ballon.ShowBitmap();
        }

        break;
    default:
        break;
    }
}

void CGameStateRun::initRoad()
{
    char buff[100];
    string roadFileName;
    vector<Btd::Vector2> location{
        {0, 320}, {105, 124}, {170, 124},
        {285, 190}, {285, 390}, {43, 510},
        {43, 575}, {110, 636}, {620, 426},
        {429, 428}, {429, 249}, {496, 249},
        {622, 46}, {368, 48}, {368, 0}
    };
    for (int i = 0; i < 15; i++)
    {
        Btd::GameObject tmpRoad;
        sprintf(buff, "resources/roads/road_%d.bmp", i + 1);
        tmpRoad.LoadBitmapByString({buff});
        tmpRoad.SetTopLeft(static_cast<int>(location[i].X), static_cast<int>(location[i].Y));
        tmpRoad.SetTag("road");
        road.push_back(tmpRoad);
    }
}
