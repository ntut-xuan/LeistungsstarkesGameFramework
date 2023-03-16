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
        case BalloonMoveTest:
            _balloon.LoadEmptyBitmap(30, 30);
            _balloon.SetTopLeft(10, 10);
            _balloon.SetActive(false);
            _balloon.SetNowRouteTarget(0);
            _balloon.Setspeed(3);
        case BalloonVectorMoveTest:
            BALLOONS.push_back(_balloon);
        case BallonPop:
            TowerFactory::MakeTower(dart);
            TowerFactory::TowerVector[0].SetIsMove(false);
            TowerFactory::TowerVector[0].SetTopLeft(200, 200);
            TowerFactory::TowerVector[0].SetShootDeltaTime(1);
            _balloonFactory.MakeBallon(yelllow);
            BallonFactory::BallonVector[0].SetTopLeft(100, 400);
            _balloonFactory.MakeBallon(blue);
            BallonFactory::BallonVector[1].SetTopLeft(600, 400);
            _balloonFactory.MakeBallon(black);
            BallonFactory::BallonVector[2].SetTopLeft(400, 400);
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
                _unitTestState = BalloonMoveTest;
            }
            break;
        case DartMonkeyShoot:
        //shoot test
            break;
        case BalloonMoveTest:
            _balloon.Move({{500, 500}});
            if (_balloon.GetTop() > 30)
            {
                _unitTestState = BalloonVectorMoveTest;
            }
            break;
        case BalloonVectorMoveTest:
            BALLOONS[0].Move({{500, 500}});
            if (BALLOONS[0].GetLeft() > 100)
            {
                _unitTestState = BalloonFactoryTest;
            }
            break;
        case BalloonFactoryTest:
            if (_balloonFactory.BallonVector.size() < 10)
            {
                _balloonFactory.MakeBallon(red);
            }
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.Move({{500, 500}});
            }
            if (_balloonFactory.BallonVector.size() > 5)
            {
                _unitTestState = NailMachineShoot;
            }

            break;
        case BallonPop:
            TowerFactory::TowerVector[0].Update();
            for (int i=0; i<(int)TowerFactory::TowerVector.size(); i++)
            {
                TowerFactory::TowerVector[i].Update();
            }
            BallonFactory::handlePopBalloon();
            break;
        case TowerFocus:
            _dartMonkey.Update();
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.Update();
            }
            break;
        case NailMachineShoot:
            _nailMachine.Update();
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.Update();
            }


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
        case BalloonMoveTest:
            _balloon.ShowBitmap();
            break;
        case BalloonVectorMoveTest:
            BALLOONS[0].ShowBitmap();
            break;
        case BalloonFactoryTest:
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.ShowBitmap();
            }

            break;
        case BallonPop:
            for (Tower tower : TowerFactory::TowerVector)
            {
                tower.TowerShow();
            }
            for (auto b : BallonFactory::BallonVector)
            {
                b.ShowBitmap();
            }
            break;
            
        case TowerFocus:
            _dartMonkey.TowerShow();
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.ShowBitmap();
            }

            break;
        case NailMachineShoot:
            _nailMachine.TowerShow();
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.ShowBitmap();
            }
            break;
        default:
            break;
        }
    }
}
