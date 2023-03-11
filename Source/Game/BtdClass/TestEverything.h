#pragma once
#include "BallonFactory.h"
#include "DartMonkey.h"
#include "Throwable.h"


namespace Btd
{
    enum UnitTestState
    {
        ThrowableMove,
        DartMonkeyShoot,
        BalloonFactoryTest,
        BalloonMoveTest,
        BalloonVectorMoveTest,
    };

    class TestEverything
    {
    private:
        UnitTestState _unitTestState = ThrowableMove;
        Throwable _throwable;
        DartMonkey _dartMonkey;
        BallonFactory _balloonFactory;
        Ballon _balloon;
        vector<Ballon> BALLOONS;

    public:

        void UnitInit();
        void UnitTest();
        void UnitShow();
    };
}
