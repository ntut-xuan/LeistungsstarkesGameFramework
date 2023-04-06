#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <string>

#include "config.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "BtdClass/TowerFactory.h"

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
    gm.OnBeginState();
    gameOverCounter = 0;
}

void CGameStateRun::OnMove() // 移動遊戲元素
{
    gm.OnMove();
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
    gm.OnInit();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    gm.OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    gm.OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnLButtonDown(nFlags, point);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnLButtonUp(nFlags, point);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnMouseMove(nFlags, point);
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnRButtonDown(nFlags, point);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnRButtonUp(nFlags, point);
}

void ShowGameStatusUI(int round, int lives, int money)
{
    CDC* pDC = CDDraw::GetBackCDC();
    CTextDraw::ChangeFontLog(pDC, 27, "Courier New", RGB(255, 255, 255), 620);
    CTextDraw::Print(pDC, 749, 25, "Round:   " + to_string(round + 1));
    CTextDraw::Print(pDC, 749, 61, "Money: " + to_string(money));
    CTextDraw::Print(pDC, 749, 97, "Lives:  " + to_string(lives));

    CTextDraw::ChangeFontLog(pDC, 24, "Courier New", RGB(255, 255, 255), 620);
    CTextDraw::Print(pDC, 749, 152, "Build Towers");
    CTextDraw::Print(pDC, 749, 152, "____________");

    CDDraw::ReleaseBackCDC();
}

void GameOver(int size)
{
    //size 150
    int screenCenterX = SIZE_X / 2;
    int screenCenterY = SIZE_Y / 2;
    int textLeft =screenCenterX -static_cast<int>(2.5*size);
    int textTop = screenCenterY - size;
    int delta = size / 30;
    auto cdc = CDDraw::GetBackCDC();
    CTextDraw::ChangeFontLog(cdc, size, "微軟正黑體",RGB(255, 255, 255), 800);
    CTextDraw::Print(cdc, textLeft+delta, textTop+delta, "game  over");
    CTextDraw::Print(cdc, textLeft-delta, textTop+delta, "game  over");
    CTextDraw::Print(cdc, textLeft+delta, textTop-delta, "game  over");
    CTextDraw::Print(cdc, textLeft-delta, textTop-delta, "game  over");

    CTextDraw::ChangeFontLog(cdc, size, "微軟正黑體",RGB(0, 0, 0), 800);
    CTextDraw::Print(cdc, textLeft, textTop, "game  over");
    CDDraw::ReleaseBackCDC();
}

void CGameStateRun::OnShow()
{
    gm.OnShow();
    ShowGameStatusUI(gm.GetRound(), gm.GetLive(), gm.GetMoney());
    if (gm.GetLose())
    {
        GameOver(gameOverCounter++);
        if (gameOverCounter >= 180)
        {
            GotoGameState(GAME_STATE_INIT);
        }
    }
}
