#pragma once

#include "Cannon.h"
#include "DartMonkey.h"
#include "IceTower.h"

namespace Btd
{
    class TowerFactory
    {
    public:
        TowerFactory() {};
        ~TowerFactory() {};
        static vector<unique_ptr<Tower>> TowerVector;
        static void MakeTower (Attribute attribute)
        {
            switch (attribute)
            {
            case dart:
            {
                unique_ptr<Tower> dartMonkey = make_unique<Tower>(DartMonkey());
                dartMonkey->LoadBitmapByString({"resources/towers/monkey/tower_monkey_1.bmp"}, RGB(0, 0, 0));
                dartMonkey->SetCenter(GetCursorPosX(), GetCursorPosY());
                dartMonkey->SetIsMove(true);
                dartMonkey->SetShootDeltaTime(3);
                dartMonkey->SetActive(false);
                TowerVector.push_back(move(dartMonkey));
                break;
            }
            case bomb:
            {
                unique_ptr<Cannon> cannon = make_unique<Cannon>(Cannon());
                cannon->LoadBitmapByString({"resources/towers/bomb/tower_bomb.bmp"}, RGB(255, 255, 255));
                cannon->SetCenter(GetCursorPosX(), GetCursorPosY());
                cannon->SetIsMove(true);
                cannon->SetShootDeltaTime(3);
                cannon->SetActive(false);
                TowerVector.push_back(std::move(cannon));
                break;
            }
            case ice:
            {
                unique_ptr<IceTower> ice = make_unique<IceTower>(IceTower());
                ice->LoadBitmapByString({"resources/towers/ice/tower_ice.bmp"}, RGB(0, 0, 0));
                ice->SetCenter(GetCursorPosX(), GetCursorPosY());
                ice->SetIsMove(true);
                ice->SetShootDeltaTime(3);
                ice->SetActive(false);
                TowerVector.push_back(std::move(ice));
            }
            default:
                break;
            }
        }
    private: 
    };
}
