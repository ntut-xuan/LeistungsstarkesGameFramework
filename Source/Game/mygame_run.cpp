#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <string>

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

void CGameStateRun::OnShow()
{
    gm.OnShow();
    
    if(gm.GetLose())
    {
        auto cdc =  CDDraw::GetBackCDC();
        CTextDraw::ChangeFontLog(cdc ,150,"微軟正黑體",RGB(255,255,255),800);
        CTextDraw::Print(cdc,95,205,"gameover");
        CTextDraw::ChangeFontLog(cdc ,150,"微軟正黑體",RGB(255,255,255),800);
        CTextDraw::Print(cdc,105,195,"gameover");
        CTextDraw::ChangeFontLog(cdc ,150,"微軟正黑體",RGB(255,255,255),800);
        CTextDraw::Print(cdc,95,195,"gameover");
        CTextDraw::ChangeFontLog(cdc ,150,"微軟正黑體",RGB(255,255,255),800);
        CTextDraw::Print(cdc,105,205,"gameover");
        CTextDraw::ChangeFontLog(cdc ,150,"微軟正黑體",RGB(0,0,0),800);
        CTextDraw::Print(cdc,100,200,"gameover");
        CDDraw::ReleaseBackCDC();
    }
}
