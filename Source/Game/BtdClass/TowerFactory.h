#pragma once

#include "Cannon.h"
#include "DartMonkey.h"
#include "IceTower.h"
#include "NailMachine.h"

namespace Btd
{
    class TowerFactory
    {
    public:
        TowerFactory() {};
        ~TowerFactory() {};
        static vector<shared_ptr<Tower>> TowerVector;
        static void MakeTower (Attribute attribute)
        {
            switch (attribute)
            {
            case dart:
            {
                shared_ptr<DartMonkey> dartMonkey = make_shared<DartMonkey>(DartMonkey());
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
                shared_ptr<Cannon> cannon = make_shared<Cannon>(Cannon());
                cannon->LoadBitmapByString({"resources/towers/bomb/tower_bomb.bmp"}, RGB(255, 255, 255));
                cannon->SetCenter(GetCursorPosX(), GetCursorPosY());
                cannon->SetIsMove(true);
                cannon->SetShootDeltaTime(3);
                cannon->SetActive(false);
                TowerVector.push_back(cannon);
                break;
            }
            case nail:
            {
                shared_ptr<NailMachine> nailMachine = make_shared<NailMachine>(NailMachine());
                nailMachine->LoadBitmapByString({"resources/towers/nail/tower_nail.bmp"}, RGB(0, 0, 0));
                nailMachine->SetCenter(GetCursorPosX(), GetCursorPosY());
                nailMachine->SetIsMove(true);
                nailMachine->SetShootDeltaTime(3);
                nailMachine->SetActive(false);
                TowerVector.push_back(nailMachine);
                break;
            }
            case ice:
            {
                shared_ptr<IceTower> ice = make_shared<IceTower>(IceTower());
                ice->LoadBitmapByString({"resources/towers/ice/tower_ice.bmp"}, RGB(0, 0, 0));
                ice->SetCenter(GetCursorPosX(), GetCursorPosY());
                ice->SetIsMove(true);
                ice->SetShootDeltaTime(3);
                ice->SetActive(false);
                TowerVector.push_back(ice);
            }
            default:
                break;
            }
        }
    private: 
    };
}
