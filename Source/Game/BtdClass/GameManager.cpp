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
            {{Layer::red, 1000}, {Layer::red, 1000}, {Layer::blue, 1000}},
            {{Layer::red, 1000}, {Layer::red, 1000}, {Layer::blue, 1000}},
            {{Layer::red, 1000}, {Layer::red, 1000}, {Layer::blue, 1000}},
            {{Layer::red, 1000}, {Layer::red, 1000}, {Layer::blue, 1000}}
        });
        BallonFactory::SetNextRound(Map.GetRounds()[round]);
    }

    void GameManager::OnInit()
    {
        Map.InitRoad();
        Map.InitBackground();
        Map.InitFactoryButton();
        GameFlow = Prepare;
        startButton.LoadBitmapByString({"resources/start_button.bmp"});
        startButton.SetTopLeft(742, 620);
        db.GetRoutes();
    }

    void GameManager::OnKeyUp(UINT, UINT, UINT)
    {
    }

    void GameManager::OnLButtonDown(UINT nFlags, CPoint point)
    {
        Map.HandleButtonClicked();
        if (!TowerFactory::TowerVector.empty() && TowerFactory::TowerVector.back()->IsMovable())
        {
            TowerFactory::TowerVector.back()->SetIsMove(false);
            TowerFactory::TowerVector.back()->SetActive(true);
        }
        switch (GameFlow)
        {
        case Prepare:
            {
                POINT p;
                GetCursorPos(&p);
                HWND hwnd = FindWindowA(nullptr, "Game");
                ScreenToClient(hwnd, &p);

                if (isPointInBmp(p, startButton))
                {
                    GameFlow = Shoot;
                }
                break;
            }
        default:
            break;
        }
    }

    void GameManager::OnLButtonUp(UINT nFlags, CPoint point)
    {
    }

    void GameManager::OnMouseMove(UINT nFlags, CPoint point)
    {
        if (!TowerFactory::TowerVector.empty() && TowerFactory::TowerVector.back()->IsMovable())
        {
            TowerFactory::TowerVector.back()->SetCenter(GetCursorPosX(), GetCursorPosY());
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

        switch (GameFlow)
        {
        case Prepare:
            break;

        case Shoot:
            {
                bool RoundRunOut = BallonFactory::UpdateRound(BtdTimer.GetDeltaTime());
                bool isRoundEnd = BallonFactory::BallonVector.empty() && RoundRunOut;
                if (isRoundEnd)
                {
                    GameFlow = Win;
                }
                break;
            }
        case Win:
            round++;
            if (round >= static_cast<int>(Map.GetRounds().size()))
            {
                GameFlow = GameEnd;
            }
            else
            {
                BallonFactory::SetNextRound(Map.GetRounds()[round]);
                GameFlow = Prepare;
                //todo gold ++
            }

            break;
        case GameEnd:

            break;
        default: ;
        }
        for (auto& m : TowerFactory::TowerVector)
        {
            m->Update();
        }
        BallonFactory::UpdateBloon();
    }

    void GameManager::OnShow()
    {
        Map.ShowBackground();
        Map.ShowFactoryButton();
        Map.ShowRoad();
        for (int i=0; i<(int)TowerFactory::TowerVector.size(); i++)
        {
            TowerFactory::TowerVector[i]->TowerShow();
        }
        for (auto& ballon : BallonFactory::BallonVector)
        {
            ballon.ShowBitmap();
        }
        switch (GameFlow)
        {
        case Prepare:
            startButton.ShowBitmap();
            break;
        default:
            break;
        }
    }

    void GameManager::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
    {
        if (nChar == 'A')
        {
            BallonFactory::MakeBallon(Layer::red);
        }
    }
}
