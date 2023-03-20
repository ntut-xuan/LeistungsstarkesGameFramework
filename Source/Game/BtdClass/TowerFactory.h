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
        static vector<Tower*> TowerVector;
        static void MakeTower (Attribute attribute)
        {
            switch (attribute)
            {
            case dart:
            {
                DartMonkey *dartMonkey = new DartMonkey();
                dartMonkey->LoadBitmapByString({"resources/towers/monkey/tower_monkey_1.bmp"}, RGB(0, 0, 0));
                dartMonkey->SetCenter(GetCursorPosX(), GetCursorPosY());
                dartMonkey->SetIsMove(true);
                dartMonkey->SetShootDeltaTime(3);
                dartMonkey->SetActive(false);
                TowerVector.push_back(dartMonkey);
                break;
            }
            case bomb:
            {
                Tower *cannon = new Cannon();
                cannon->LoadBitmapByString({"resources/towers/bomb/tower_bomb.bmp"}, RGB(255, 255, 255));
                cannon->SetCenter(GetCursorPosX(), GetCursorPosY());
                cannon->SetIsMove(true);
                cannon->SetShootDeltaTime(3);
                cannon->SetActive(false);
                TowerVector.push_back(cannon);
                break;
            }
            default:
                break;
            }
        }
    private: 
    };
}
