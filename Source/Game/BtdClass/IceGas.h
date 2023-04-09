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
        void SetRealCenter(Vector2 center);
        void SetRange(int range);
    private:
        Vector2 _realCenter;
        int _range;
    };
}
