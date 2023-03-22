#pragma once

#include "GameObject.h"


namespace Btd
{
    class BtdTimer final : public GameObject
    {
    public:
        BtdTimer() = default;
        ~BtdTimer() override = default;
        int GetDeltaTime();
    };
}
