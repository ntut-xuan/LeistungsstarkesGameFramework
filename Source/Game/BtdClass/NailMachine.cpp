#include "stdafx.h"
#include "NailMachine.h"

#include "BallonFactory.h"

namespace Btd
{
    void NailMachine::Update()
    {
        UpdateThrowable();

        if (!BallonFactory::BallonVector.empty() && GetShootTimeCounter() > GetShootDeltaTime())
        {
            Ballon target = focus();
            //todo check in attack range
            Vector2 target1 = {static_cast<float>(target.GetLeft()), static_cast<float>(target.GetTop())};
            Shoot(target1);
            Shoot(Spin45(target1));
            Shoot(Spin90(target1));
            Shoot(Spin90(Spin45(target1)));
            target1.X *= -1;
            target1.Y *= -1;
            Shoot(target1);
            Shoot(Spin45(target1));
            Shoot(Spin90(target1));
            Shoot(Spin90(Spin45(target1)));
        }
        else
        {
            SetShootTimeCounter(GetShootTimeCounter() + delayCount / 100.F);
        }
    }
}
