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
            Ballon targetBallon = focus();
            //todo check in attack range
            Vector2 direction = {1, 0};
            for (int i = 0; i < 8; i++)
            {
                Vector2 target = {
                    static_cast<float>(GetLeft()) + direction.X,
                    static_cast<float>(GetTop()) + direction.Y
                };
                Shoot(target);
                direction = Spin45(direction);
            }
        }
        else
        {
            SetShootTimeCounter(GetShootTimeCounter() + delayCount / 100.F);
        }
    }
}
