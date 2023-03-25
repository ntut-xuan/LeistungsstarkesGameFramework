#pragma once
#include "BloonFactory.h"
#include "DartMonkey.h"
#include "NailMachine.h"
#include "Throwable.h"
#include "Cannon.h"
#include "IceTower.h"


namespace Btd
{
    enum UnitTestState
    {
        ThrowableMove,
        DartMonkeyShoot,
        BloonFactoryTest,
        BloonMoveTest,
        BloonVectorMoveTest,
        BloonPop,
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
        IceTower _ice;
        BloonFactory _balloonFactory;
        TowerFactory _towerFactory;
        Bloon _balloon;
        vector<Bloon> BLOONS;

    public:
        TestEverything(TestEverything&&) = default;
        TestEverything() = default;
        void UnitInit();
        void UnitTest();
        void UnitShow();
        void SetState(UnitTestState state) {_unitTestState = state;};
    };
}
