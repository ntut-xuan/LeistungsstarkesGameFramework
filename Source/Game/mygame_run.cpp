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
    map.SetStartPosition({
        static_cast<float>(map.GetBackground().GetWidth()), static_cast<float>(map.GetBackground().GetHeight()) / 2
    });
}

void CGameStateRun::OnMove() // 移動遊戲元素
{
    UnitTest();
}

vector<string> GeneratePath(string initPath)
{
    vector<string> path;
    for (int i = 1; i <= 8; i++)
    {
        string tmpPath = initPath + std::to_string(i) + ".bmp";
        path.push_back(tmpPath);
    }
    return path;
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
    monkey.LoadBitmapByString({{GeneratePath("resources/towers/monkey/tower_monkey_")}}, RGB(0, 0, 0));
    UnitInit();
    map.InitRoad();
    map.InitBackground();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar == VK_F1)
    {
        int index = (monkey.GetFrameIndexOfBitmap() + 1) % 8;
        monkey.SetFrameIndexOfBitmap(index);
    }
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    if (monkey.IsMovable())
    {
        monkey.SetNotMove();
    }
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    if (monkey.IsMovable())
    {
        POINT p;
        GetCursorPos(&p);
        HWND hwnd = FindWindowA(nullptr, "Game");
        ScreenToClient(hwnd, &p);
        monkey.SetCenter(p.x, p.y);
    }
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
    map.ShowBackground();
    map.ShowRoad();
    monkey.ShowBitmap();
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
        BALLOON_FACTORY.UpdateBloon();

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
