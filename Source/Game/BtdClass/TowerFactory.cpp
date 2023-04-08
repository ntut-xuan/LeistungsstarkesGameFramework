#include "stdafx.h"
#include "TowerFactory.h"

void Btd::TowerFactory::MakeTower(TowerType attribute)
{
    switch (attribute)
    {
    case dart:
        {
            shared_ptr<DartMonkey> dartMonkey = make_shared<DartMonkey>(DartMonkey());
            dartMonkey->LoadBitmapByString({"resources/towers/monkey/tower_monkey_1.bmp", "resources/towers/monkey/tower_monkey_2.bmp"
                                               , "resources/towers/monkey/tower_monkey_3.bmp", "resources/towers/monkey/tower_monkey_4.bmp", "resources/towers/monkey/tower_monkey_5.bmp"
                                               , "resources/towers/monkey/tower_monkey_6.bmp", "resources/towers/monkey/tower_monkey_7.bmp", "resources/towers/monkey/tower_monkey_8.bmp"}, RGB(0, 0, 0));
            dartMonkey->SetCenter(GetCursorPosX(), GetCursorPosY());
            dartMonkey->SetIsMove(true);
            dartMonkey->SetShootDeltaTime(3);
            dartMonkey->SetActive(false);
            dartMonkey->SetFrameIndexOfBitmap(6);
            dartMonkey->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            dartMonkey->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            TowerVector.push_back(dartMonkey);
            break;
        }
    case bomb:
        {
            shared_ptr<Cannon> cannon = make_shared<Cannon>(Cannon());
            cannon->LoadBitmapByString({"resources/towers/bomb/tower_bomb_1.bmp", "resources/towers/bomb/tower_bomb_2.bmp"
                                           , "resources/towers/bomb/tower_bomb_3.bmp", "resources/towers/bomb/tower_bomb_4.bmp", "resources/towers/bomb/tower_bomb_5.bmp"
                                           , "resources/towers/bomb/tower_bomb_6.bmp", "resources/towers/bomb/tower_bomb_7.bmp", "resources/towers/bomb/tower_bomb_8.bmp"}, RGB(255, 255, 255));
            cannon->SetCenter(GetCursorPosX(), GetCursorPosY());
            cannon->SetIsMove(true);
            cannon->SetShootDeltaTime(3);
            cannon->SetActive(false);
            cannon->SetFrameIndexOfBitmap(6);
            cannon->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            cannon->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
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
            nailMachine->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            nailMachine->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
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
            ice->SetShootDeltaTime(3);
            ice->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            ice->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            TowerVector.push_back(ice);
        }
    default:
        break;
    }
}

void Btd::TowerFactory::HandleTowerClicked()
{
    for (int i=0; i<(int)TowerVector.size(); i++)
    {
        if (TowerVector[i]->IsCursorFocus())
        {
            TowerVector[i]->SetClicked(true);
        }
        else
        {
            TowerVector[i]->SetClicked(false);
        }
    }
}
