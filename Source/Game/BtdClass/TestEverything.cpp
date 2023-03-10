#include "stdafx.h"
#include "TestEverything.h"

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
            _dartMonkey.LoadEmptyBitmap(50, 50);
            _dartMonkey.SetTopLeft(100, 100);
            _dartMonkey.SetShootDeltaTime(1);
        // DARTMONKEY.SetThrowableName("dart");
        // break;
        case BalloonMoveTest:
            _balloon.LoadEmptyBitmap(30, 30);
            _balloon.SetTopLeft(10, 10);
            _balloon.SetActive(false);
            _balloon.SetNowRouteTarget(0);
            _balloon.Setspeed(3);
        case BalloonVectorMoveTest:
            BALLOONS.push_back(_balloon);
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
            _dartMonkey.Update();
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
                _balloonFactory.MakeBallon("a");
            }
            for (auto& ballon : _balloonFactory.BallonVector)
            {
                ballon.Move({{500, 500}});
            }
            if (_balloonFactory.BallonVector.size() > 5)
            {
                _unitTestState = DartMonkeyShoot;
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
            _dartMonkey.TowerShow();
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
        default:
            break;
        }
    }
}
