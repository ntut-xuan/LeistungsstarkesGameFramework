#include "stdafx.h"
#include "GameManager.h"

#include "BallonFactory.h"
#include "TowerFactory.h"

namespace Btd
{
    void GameManager::OnBeginState()
    {
        Vector2 mapSize = {
            static_cast<float>(Map.GetBackground().GetWidth()), static_cast<float>(Map.GetBackground().GetHeight())
        };
        Map.SetStartPosition({
            static_cast<float>(0), mapSize.Y * 0.4F
        });
        Map.SetRoute({
            {mapSize.X * 0.11F, mapSize.Y * 0.4F}, {mapSize.X * 0.11F, mapSize.Y * 0.12F},
            {mapSize.X * 0.3F, mapSize.Y * 0.12F}, {mapSize.X * 0.3F, mapSize.Y * 0.67F},
            {mapSize.X * 0.05F, mapSize.Y * 0.67F}, {mapSize.X * 0.05F, mapSize.Y * 0.85F},
            {mapSize.X * 0.65F, mapSize.Y * 0.85F}, {mapSize.X * 0.65F, mapSize.Y * 0.53F},
            {mapSize.X * 0.45F, mapSize.Y * 0.53F}, {mapSize.X * 0.45F, mapSize.Y * 0.3F},
            {mapSize.X * 0.65F, mapSize.Y * 0.3F}, {mapSize.X * 0.65F, mapSize.Y * 0.06F},
            {mapSize.X * 0.38F, mapSize.Y * 0.06F}, {mapSize.X * 0.38F, mapSize.Y * 0.F},
            {mapSize.X * 0.38F, mapSize.Y * -0.08F},
        });
        Map.SetRounds({
            {{red, 10}, {red, 10}, {blue, 10}},
            {{red, 10}, {red, 10}, {blue, 10}},
            {{red, 10}, {red, 10}, {blue, 10}},
            {{red, 10}, {red, 10}, {blue, 10}}
        });
        BallonFactory::SetRound(Map.GetRounds()[0]);
    }

    void GameManager::OnInit()
    {
        Map.InitRoad();
        Map.InitBackground();
        Map.InitFactoryButton();
        GameFlow = Prepare;
    }

    void GameManager::OnKeyUp(UINT, UINT, UINT)
    {
    }

    void GameManager::OnLButtonDown(UINT nFlags, CPoint point)
    {
        Map.HandleButtonClicked();
        if (!TowerFactory::TowerVector.empty() && TowerFactory::TowerVector.back().IsMovable())
        {
            TowerFactory::TowerVector.back().SetIsMove(false);
            TowerFactory::TowerVector.back().SetActive(true);
        }
    }

    void GameManager::OnLButtonUp(UINT nFlags, CPoint point)
    {
    }

    void GameManager::OnMouseMove(UINT nFlags, CPoint point)
    {
        if (!TowerFactory::TowerVector.empty() && TowerFactory::TowerVector.back().IsMovable())
        {
            TowerFactory::TowerVector.back().SetCenter(GetCursorPosX(), GetCursorPosY());
        }
    }

    void GameManager::OnRButtonDown(UINT nFlags, CPoint point)
    {
    }

    void GameManager::OnRButtonUp(UINT nFlags, CPoint point)
    {
    }

    void GameManager::OnMove()
    {
        Map.UpdateFatoryButton();
        bool RoundRunOut = BallonFactory::UpdateRound(BtdTimer.GetDeltaTime());
        bool isRoundEnd = BallonFactory::BallonVector.empty() && RoundRunOut;

        switch (GameFlow)
        {
        case Prepare:
        case Shoot:
            if (isRoundEnd)
            {
                GameFlow = Win;
            }
            break;
        case Win:
        default: ;
        }
        for (auto& m : TowerFactory::TowerVector)
        {
            m.Update();
        }
        BallonFactory::UpdateBloon();
    }

    void GameManager::OnShow()
    {
        Map.ShowBackground();
        Map.ShowFactoryButton();
        Map.ShowRoad();
        for (auto m : TowerFactory::TowerVector)
        {
            m.TowerShow();
        }
        for (auto& ballon : BallonFactory::BallonVector)
        {
            ballon.ShowBitmap();
        }
    }

    void GameManager::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
    {
        if (nChar == 'A')
        {
            BallonFactory::MakeBallon(red);
        }
    }
}
