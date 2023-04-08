#pragma once
#include "Throwable.h"
#include "BloonFactory.h"

namespace Btd
{
    class IceGas : public Throwable
    {
    public:
        IceGas();
        ~IceGas() =default;
        void DetectHitBalloon() override;
    };
}
