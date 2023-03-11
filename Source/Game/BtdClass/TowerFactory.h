#pragma once

#include "DartMonkey.h"

namespace Btd
{
    class TowerFactory
    {
    public:
        TowerFactory() = default;
        ~TowerFactory();
        static vector<Tower> TowerVector;
        static void MakeTower (Attribute attribute)
        {
            switch (attribute)
            {
            case dart:
                DartMonkey dartMonkey;
                dartMonkey.LoadBitmapByString({"resources/towers/monkey/tower_monkey_1.bmp"}, RGB(0, 0, 0));
                dartMonkey.SetCenter(GetCursorPosX(), GetCursorPosY());
                dartMonkey.SetIsMove(true);
                TowerVector.push_back(dartMonkey);
            }
        }
    private: 
    };
}
