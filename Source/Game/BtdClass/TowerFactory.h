#pragma once

#include "Cannon.h"
#include "DartMonkey.h"

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
                unique_ptr<Tower> cannon = make_unique<Tower>(Cannon());
                cannon->LoadBitmapByString({"resources/towers/bomb/tower_bomb.bmp"}, RGB(255, 255, 255));
                cannon->SetCenter(GetCursorPosX(), GetCursorPosY());
                cannon->SetIsMove(true);
                cannon->SetShootDeltaTime(3);
                cannon->SetActive(false);
                TowerVector.push_back(move(cannon));
                break;
            }
            default:
                break;
            }
        }
    private: 
    };
}
