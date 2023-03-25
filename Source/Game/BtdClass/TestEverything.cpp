#include "stdafx.h"
#include "TestEverything.h"

#include "TowerFactory.h"

namespace Btd
{
    void TestEverything::UnitInit()
    {
        switch (_unitTestState)
        {
        case ThrowableMove:
            _throwable.LoadEmptyBitmap(100, 100);
            _throwable.SetTopLeft(0, 0);
            _throwable.SetSpeed(2);
            _throwable.SetMoveDirection(1, 1);
        // break;
        case DartMonkeyShoot:
            _dartMonkey.LoadBitmapByString({"Resources/towers/monkey/tower_monkey_1.bmp"},RGB(0, 0, 0));
            _dartMonkey.SetTopLeft(100, 100);
            _dartMonkey.SetShootDeltaTime(1);
        case BloonMoveTest:
            _balloon.LoadEmptyBitmap(30, 30);
            _balloon.SetTopLeft(10, 10);
            _balloon.SetActive(false);
            _balloon.SetNowRouteTarget(0);
            _balloon.Setspeed(3);
        case BloonVectorMoveTest:
            BLOONS.push_back(_balloon);
        case NailMachineShoot:
            _nailMachine.SetThrowablePath({"resources/towers/nail/nail.bmp"});
            _nailMachine.LoadBitmapByString({"Resources/towers/nail/tower_nail.bmp"},RGB(0, 0, 0));
            _nailMachine.SetTopLeft(500, 500);
            _nailMachine.SetShootDeltaTime(1);
        case BloonPop:
            _cannon.LoadBitmapByString({"resources/towers/bomb/tower_bomb.bmp"}, RGB(255, 255, 255));
            _cannon.SetTopLeft(500, 500);
            _cannon.SetShootDeltaTime(3);
            _ice.LoadBitmapByString({"resources/towers/ice/tower_ice.bmp"}, RGB(0, 0, 0));
            _ice.SetTopLeft(350, 300);
            _ice.SetShootDeltaTime(3);
            TowerFactory::MakeTower(bomb);
            TowerFactory::TowerVector[0]->SetIsMove(false);
            TowerFactory::TowerVector[0]->SetTopLeft(200, 220);
            TowerFactory::TowerVector[0]->SetShootDeltaTime(3);
            TowerFactory::TowerVector[0]->SetActive(true);
            _balloonFactory.MakeBloon(Layer::yellow);
            BloonFactory::BloonVector[0].SetTopLeft(190, 70);
            _balloonFactory.MakeBloon(Layer::blue);
            BloonFactory::BloonVector[1].SetTopLeft(210, 80);
            _balloonFactory.MakeBloon(Layer::black);
            BloonFactory::BloonVector[2].SetTopLeft(400, 400);
            break;

        default:
            break;
        }
    }

    void TestEverything::UnitTest()
    {
        switch (_unitTestState)
        {
        case ThrowableMove:
            _throwable.Move();
            if (_throwable.GetTop() > 10)
            {
                _unitTestState = BloonMoveTest;
            }
            break;
        case DartMonkeyShoot:
            _dartMonkey.Update();
        //shoot test
            break;
        case BloonMoveTest:
            _balloon.Move({{500, 500}});
            if (_balloon.GetTop() > 30)
            {
                _unitTestState = BloonVectorMoveTest;
            }
            break;
        case BloonVectorMoveTest:
            BLOONS[0].Move({{500, 500}});
            if (BLOONS[0].GetLeft() > 100)
            {
                _unitTestState = BloonFactoryTest;
            }
            break;
        case BloonFactoryTest:
            if (_balloonFactory.BloonVector.size() < 10)
            {
                _balloonFactory.MakeBloon(Layer::red);
            }
            for (auto& bloon : _balloonFactory.BloonVector)
            {
                bloon.Move({{500, 500}});
            }
            if (_balloonFactory.BloonVector.size() > 5)
            {
                _unitTestState = NailMachineShoot;
            }

            break;
        case TowerFocus:
            _dartMonkey.Update();
            for (auto& bloon : _balloonFactory.BloonVector)
            {
                bloon.Update();
            }
            break;
        case NailMachineShoot:
            _nailMachine.Update();
            for (auto& bloon : _balloonFactory.BloonVector)
            {
                bloon.Update();
            }
            BloonFactory::handlePopBalloon();
            break;
        case BloonPop:
            for (int i=0; i<(int)TowerFactory::TowerVector.size(); i++)
            {
                TowerFactory::TowerVector[i]->Update();
            }
            BloonFactory::handlePopBalloon();
            break;
        default: ;
        }
    }

    void TestEverything::UnitShow()
    {
        switch (_unitTestState)
        {
        case ThrowableMove:
            _throwable.ShowBitmap();
            break;
        case DartMonkeyShoot:
            break;
        case BloonMoveTest:
            _balloon.ShowBitmap();
            break;
        case BloonVectorMoveTest:
            BLOONS[0].ShowBitmap();
            break;
        case BloonFactoryTest:
            for (auto& bloon : _balloonFactory.BloonVector)
            {
                bloon.ShowBitmap();
            }

            break;
        case TowerFocus:
            _dartMonkey.TowerShow();
            for (auto& bloon : _balloonFactory.BloonVector)
            {
                bloon.ShowBitmap();
            }
            break;
        case NailMachineShoot:
            _nailMachine.TowerShow();
            for (auto& bloon : _balloonFactory.BloonVector)
            {
                bloon.ShowBitmap();
            }
            break;
        case BloonPop:
            for (auto&& tower : TowerFactory::TowerVector)
            {
                tower->TowerShow();
                TRACE("%.2f %.2f\n", tower->GetCenter().X, tower->GetCenter().Y);
            }
            _cannon.TowerShow();
            _ice.TowerShow();
            for (auto b : BloonFactory::BloonVector)
            {
                b.ShowBitmap();
            }
            break;
        default:
            break;
        }
    }
}
