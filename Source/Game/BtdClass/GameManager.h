#pragma once
#include "BtdTimer.h"
#include "map.h"
#include "Tower.h"

namespace Btd
{
    class GameManager
    {
    private:

    public:
        void OnBeginState(); // 設定每次重玩所需的變數
        void OnInit(); // 遊戲的初值及圖形設定
        void OnKeyDown(UINT, UINT, UINT);
        void OnKeyUp(UINT, UINT, UINT);
        void OnLButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
        void OnLButtonUp(UINT nFlags, CPoint point); // 處理滑鼠的動作
        void OnMouseMove(UINT nFlags, CPoint point); // 處理滑鼠的動作 
        void OnRButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
        void OnRButtonUp(UINT nFlags, CPoint point); // 處理滑鼠的動作
        void OnMove(); // 移動遊戲元素
        void OnShow(); // 顯示這個狀態的遊戲畫面

        Map Map;
        GameFlow GameFlow;
        BtdTimer BtdTimer;
        int round = 0;
        game_framework::CMovingBitmap startButton;
    };
}
