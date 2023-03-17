#include "stdafx.h"
#include "GameManager.h"

#include "TowerFactory.h"

void GameManager::OnBeginState()
{
    Btd::Vector2 mapSize = {
        static_cast<float>(map.GetBackground().GetWidth()), static_cast<float>(map.GetBackground().GetHeight())
    };
    map.SetStartPosition({
        static_cast<float>(0), mapSize.Y * 0.4F
    });
    map.SetRoute({
        {mapSize.X * 0.11F, mapSize.Y * 0.4F}, {mapSize.X * 0.11F, mapSize.Y * 0.12F},
        {mapSize.X * 0.3F, mapSize.Y * 0.12F}, {mapSize.X * 0.3F, mapSize.Y * 0.67F},
        {mapSize.X * 0.05F, mapSize.Y * 0.67F}, {mapSize.X * 0.05F, mapSize.Y * 0.85F},
        {mapSize.X * 0.65F, mapSize.Y * 0.85F}, {mapSize.X * 0.65F, mapSize.Y * 0.53F},
        {mapSize.X * 0.45F, mapSize.Y * 0.53F}, {mapSize.X * 0.45F, mapSize.Y * 0.3F},
        {mapSize.X * 0.65F, mapSize.Y * 0.3F}, {mapSize.X * 0.65F, mapSize.Y * 0.06F},
        {mapSize.X * 0.38F, mapSize.Y * 0.06F}, {mapSize.X * 0.38F, mapSize.Y * 0.F},
        {mapSize.X * 0.38F, mapSize.Y * -0.08F},
    });
}

void GameManager::OnInit()
{
    map.InitRoad();
    map.InitBackground();
    map.InitFactoryButton();
}

void GameManager::OnKeyUp(UINT, UINT, UINT)
{
}

void GameManager::OnLButtonDown(UINT nFlags, CPoint point)
{
    map.HandleButtonClicked();
    if (!Btd::TowerFactory::TowerVector.empty() && Btd::TowerFactory::TowerVector.back().IsMovable())
    {
        Btd::TowerFactory::TowerVector.back().SetIsMove(false);
        Btd::TowerFactory::TowerVector.back().SetActive(true);
    }
}

void GameManager::OnLButtonUp(UINT nFlags, CPoint point)
{
}

void GameManager::OnMouseMove(UINT nFlags, CPoint point)
{
    if (!Btd::TowerFactory::TowerVector.empty() && Btd::TowerFactory::TowerVector.back().IsMovable())
    {
        Btd::TowerFactory::TowerVector.back().SetCenter(Btd::GetCursorPosX(), Btd::GetCursorPosY());
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
    map.UpdateFatoryButton();
}

void GameManager::OnShow()
{
    map.ShowBackground();
    map.ShowFactoryButton();
    map.ShowRoad();
    if (!Btd::TowerFactory::TowerVector.empty())
    {
        for (auto m : Btd::TowerFactory::TowerVector)
        {
            m.ShowBitmap();
        }
    }
}

void GameManager::OnKeyDown(UINT, UINT, UINT)
{
}
