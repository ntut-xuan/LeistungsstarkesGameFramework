#pragma once
#include "Tower.h"

namespace Btd
{
    class IceTower : public Tower
    {
    public:
        IceTower();
        void PushThrowablePool() override;
        void TowerShow() override;
    private:
    };
    
}
