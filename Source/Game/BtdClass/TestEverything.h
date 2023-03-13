#pragma once
#include "BallonFactory.h"
#include "DartMonkey.h"
#include "NailMachine.h"
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
        TowerFocus,
        NailMachineShoot,
    };

    class TestEverything
    {
    private:
        UnitTestState _unitTestState = ThrowableMove;
        Throwable _throwable;
        DartMonkey _dartMonkey;
        NailMachine _nailMachine;
        BallonFactory _balloonFactory;
        Ballon _balloon;
        vector<Ballon> BALLOONS;

    public:
        void UnitInit();
        void UnitTest();
        void UnitShow();
    };
}
