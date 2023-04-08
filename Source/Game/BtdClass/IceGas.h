#pragma once
#include "Throwable.h"
#include "BloonFactory.h"

namespace Btd
{
    class IceGas : public Throwable
    {
    public:
        IceGas();
        void DetectHitBalloon() override;
    };
}
