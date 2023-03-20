#pragma once
#include "Tower.h"

namespace Btd
{
    class Cannon : public Tower
    {
    public:
        Cannon()
        {
            _range = 300;
            ThrowablePath = {"resources/towers/bomb/bomb.bmp", "resources/towers/bomb/bomb_1.bmp",
            "resources/towers/bomb/bomb_2.bmp", "resources/towers/bomb/bomb_3.bmp"};
        }
        void PushThrowablePool();
    };
}

