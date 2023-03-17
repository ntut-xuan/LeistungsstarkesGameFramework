#pragma once
#include "BallonFactory.h"
#include "DartMonkey.h"
#include "NailMachine.h"
#include "Throwable.h"
#include "Cannon.h"


namespace Btd
{
    enum UnitTestState
    {
        ThrowableMove,
        DartMonkeyShoot,
        BalloonFactoryTest,
        BalloonMoveTest,
        BalloonVectorMoveTest,
        BallonPop,
        TowerFocus,
        NailMachineShoot,
    };

    class TestEverything
    {
    private:
        UnitTestState _unitTestState = DartMonkeyShoot;
        Throwable _throwable;
        DartMonkey _dartMonkey;
        NailMachine _nailMachine;
        Cannon _cannon;
        BallonFactory _balloonFactory;
        Ballon _balloon;
        vector<Ballon> BALLOONS;

    public:
        void UnitInit();
        void UnitTest();
        void UnitShow();
        void SetState(UnitTestState state) {_unitTestState = state;};
    };
}
