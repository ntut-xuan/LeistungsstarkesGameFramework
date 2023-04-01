#include "stdafx.h"
#include "NailMachine.h"

#include "BloonFactory.h"

namespace Btd
{
    NailMachine::NailMachine()
    {
        _range = 300;
        ThrowablePath = {"resources/towers/nail/nail.bmp"};
    }

    void NailMachine::Update()
    {
        RangeCircle.SetCenter((int)GetCenter().X - (_range - 100),
            (int)GetCenter().Y - (_range - 100));
        if (_isActive)
        {
            UpdateThrowable();

            if (!BloonFactory::BloonVector.empty() && GetShootTimeCounter() > GetShootDeltaTime())
            {
                Bloon targetBloon = focus();
                Vector2 direction = {1, 0};
                for (int i = 0; i < 8; i++)
                {
                    Vector2 target = {
                        GetCenter().X + direction.X,
                        GetCenter().Y + direction.Y
                    };
                    Shoot(target);
                    direction = Spin45(direction);
                }
            }
            else
            {
                SetShootTimeCounter(GetShootTimeCounter() + deltaTime / 100.F);
            }
        }
    }

    void NailMachine::PushThrowablePool()
    {
        shared_ptr<Throwable> nail = make_shared<Throwable>(Throwable());
        nail->LoadBitmapByString(ThrowablePath, RGB(255, 255, 255));
        nail->SetSpeed(5);
        throwablePool.push(nail);
    }
}
