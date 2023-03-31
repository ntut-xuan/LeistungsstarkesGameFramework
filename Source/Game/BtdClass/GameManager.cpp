#include "stdafx.h"
#include "GameManager.h"

#include "BloonFactory.h"
#include "TowerFactory.h"

namespace Btd
{
    void GameManager::OnBeginState()
    {
        Vector2 mapSize = {
            static_cast<float>(Map.GetBackground().GetWidth()),
            static_cast<float>(Map.GetBackground().GetHeight())
        };
        Map.SetStartPosition({static_cast<float>(0), mapSize.Y * 0.5F});
        Map.SetRoute({
            {mapSize.X * 0.14F, mapSize.Y * 0.5F},
            {mapSize.X * 0.14F, mapSize.Y * 0.22F},
            {mapSize.X * 0.32F, mapSize.Y * 0.22F},
            {mapSize.X * 0.32F, mapSize.Y * 0.72F},
            {mapSize.X * 0.07F, mapSize.Y * 0.72F},
            {mapSize.X * 0.07F, mapSize.Y * 0.90F},
            {mapSize.X * 0.67F, mapSize.Y * 0.90F},
            {mapSize.X * 0.67F, mapSize.Y * 0.63F},
            {mapSize.X * 0.47F, mapSize.Y * 0.63F},
            {mapSize.X * 0.47F, mapSize.Y * 0.4F},
            {mapSize.X * 0.67F, mapSize.Y * 0.4F},
            {mapSize.X * 0.67F, mapSize.Y * 0.13F},
            {mapSize.X * 0.40F, mapSize.Y * 0.13F},
            {mapSize.X * 0.40F, mapSize.Y * -0.18F},
        });
        BloonFactory::SetNextRound(Map.GetRounds()[round]);
        IsLose = false;
    }

    void GameManager::OnInit()
    {
        Map.InitRoad();
        Map.InitBackground();
        Map.InitFactoryButton();
        GameFlow = Prepare;
        startButton.LoadBitmapByString({"resources/start_button.bmp"});
        startButton.SetTopLeft(742, 620);
        db.LoadRounds();
        Map.SetRounds(db.GetRounds());
        life = Map.InitLives;
        money = Map.InitMoney;
    }

    void GameManager::OnKeyUp(UINT, UINT, UINT)
    {
    }

    void GameManager::OnLButtonDown(UINT nFlags, CPoint point)
    {
        Map.HandleButtonClicked();
        if (!TowerFactory::TowerVector.empty() &&
            TowerFactory::TowerVector.back()->IsMovable())
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
        if (!TowerFactory::TowerVector.empty() &&
            TowerFactory::TowerVector.back()->IsMovable())
        {
            TowerFactory::TowerVector.back()->SetCenter(GetCursorPosX(),
                                                        GetCursorPosY());
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
                bool RoundRunOut = BloonFactory::UpdateRound(BtdTimer.GetDeltaTime());
                bool isRoundEnd = BloonFactory::BloonVector.empty() && RoundRunOut;
                if (isRoundEnd)
                {
                    GameFlow = Win;
                }
                life -= BloonFactory::subLifeByGoalBloon();
                if (life <= 0)
                {
                    GameFlow = GameEnd;
                    IsLose = true;
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
                BloonFactory::SetNextRound(Map.GetRounds()[round]);
                GameFlow = Prepare;
                money += 100;
                // todo gold ++
            }

            break;
        case GameEnd:
            // todo print win or lose and can restart
            if (IsLose)
            {
                // todo print lose
            }
            else
            {
                // todo print win
            }

            break;
        default: ;
        }
        for (auto& m : TowerFactory::TowerVector)
        {
            m->Update();
        }
        BloonFactory::UpdateBloon();
    }

    void GameManager::OnShow()
    {
        Map.ShowBackground();
        Map.ShowFactoryButton();
        Map.ShowRoad();
        for (int i = 0; i < static_cast<int>(TowerFactory::TowerVector.size()); i++)
        {
            TowerFactory::TowerVector[i]->TowerShow();
        }
        for (auto& bloon : BloonFactory::BloonVector)
        {
            bloon.ShowBitmap();
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
            BloonFactory::MakeBloon(Layer::red);
        }
        if (nChar == 'S')
        {
            BloonFactory::MakeBloon(Layer::blue);
        }
        if (nChar == 'D')
        {
            BloonFactory::MakeBloon(Layer::green);
        }
        if (nChar == 'F')
        {
            BloonFactory::MakeBloon(Layer::yellow);
        }
        if (nChar == 'Z')
        {
            BloonFactory::MakeBloon(Layer::black);
        }
        if (nChar == 'X')
        {
            BloonFactory::MakeBloon(Layer::white);
        }
    }
} // namespace Btd
