#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "BtdClass/GameObject.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "BtdClass/BtdUtil.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g) : CGameState(g)
{
}

void CGameStateInit::InitSelectedMaps()
{
    vector<string> backgroundBmps[3] = {
        {"resources/map/easy/map.bmp"},
        {"resources/map/medium/map.bmp"},
        {"resources/map/hard/map.bmp"}
    };
    for (int i = 0; i < 3; i++)
    {
        auto m = make_shared<Btd::Map>(Btd::Map());
        m->InitBackground(static_cast<Btd::MapType::MapType>(i));
        m->InitRoad(static_cast<Btd::MapType::MapType>(i));
        selectedMaps.push_back(m);
    }
}

void CGameStateInit::OnInit()
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(0, "Ninja kiwi!"); // 一開始的loading進度為0%
    //
    // 開始載入資料
    //
    //Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
    //
    startButton.LoadBitmapByString({"resources/start_button.bmp"});
    startButton.SetTopLeft(742, 620);
    _mapButton[0].LoadBitmapByString({"resources/easy.bmp", "resources/play.bmp"});
    _mapButton[1].LoadBitmapByString({"resources/medium.bmp", "resources/play.bmp"});
    _mapButton[2].LoadBitmapByString({"resources/hard.bmp", "resources/play.bmp"});
    _mapButton[0].SetCenter(210, 325);
    _mapButton[1].SetCenter(390, 325);
    _mapButton[2].SetCenter(570, 325);
    InitSelectedMaps();
    map = make_shared<Btd::Map>(Btd::Map());
    map = selectedMaps[0];
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}


void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    for (int i = 0; i < 3; i++)
    {
        if (IsCursorInObj(static_cast<Btd::GameObject>(_mapButton[i])))
        {
            _mapButton[i].SetClicked(true);
            map->SetRoutesByMap(static_cast<Btd::MapType::MapType>(i));
            Btd::GameManager::map = map;
            GotoGameState(GAME_STATE_RUN);
        }
    }
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
    for (int i = 0; i < 3; i++)
    {
        if (IsCursorInObj(static_cast<Btd::GameObject>(_mapButton[i])))
        {
            map = selectedMaps[i];
        }
    }
}

void showInfoText()
{
    CDC* pDC = CDDraw::GetBackCDC();
    CTextDraw::ChangeFontLog(pDC, 27, "Courier New", RGB(255, 255, 255), 620);
    CTextDraw::Print(pDC, 749, 25, "Round:   1");
    CTextDraw::Print(pDC, 749, 61, "Money: 650");
    CTextDraw::Print(pDC, 749, 97, "Lives:  40");

    CTextDraw::ChangeFontLog(pDC, 24, "Courier New", RGB(255, 255, 255), 620);
    CTextDraw::Print(pDC, 749, 152, "Build Towers");
    CTextDraw::Print(pDC, 749, 152, "____________");

    CDDraw::ReleaseBackCDC();
}

void CGameStateInit::OnShow()
{
    map->ShowBackground();
    map->ShowRoad();
    startButton.ShowBitmap();
    for (int i = 0; i < 3; i++)
    {
        _mapButton[i].ShowBitmap();
    }
    showInfoText();
}
