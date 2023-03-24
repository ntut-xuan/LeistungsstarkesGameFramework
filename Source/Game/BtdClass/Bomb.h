#pragma once
#include "Throwable.h"

namespace Btd
{
    class Bomb : public Throwable
    {
    public:
        Bomb();
        void DetectHitBalloon ();
        
    };
}

